"""Drop the decompiler's `(int)` casts that integral promotion makes redundant.

usage:
  dropcast.py [path-filter] [--apply] [--show]

Three shapes, each a no-op for the compiler:

* `(int)x` where x is a short, ushort, char, byte or bool lvalue - a local, a parameter, a field reached
  through `this`, `DAT_X::instance`/`DAT_X::ptr` or a chain of named fields. Promotion already makes it an
  int wherever it is used in arithmetic or a comparison.
* `(int)(expr)` where every operand of expr is such an lvalue, an int-typed one, or an int literal, joined
  by + - * / % and brackets only - the expression is already an int.
* `[(uint)x]` / `[(int)x]` as the whole subscript, when x is a narrow *unsigned* lvalue.

`decast.py` only collapses doubled casts; this one needs the types, so it reads every generated header for
the struct fields, the narrow typedefs and the `MACRO_STRUCT_RESOLVER` globals, and the function's own text
for its locals and parameters. A field is typed through its containing struct when the chain can be walked
from its root; otherwise only when every struct that has a field of that name agrees. A pointer field is
never narrow: `byte*` stays a pointer, which an earlier version got wrong. Fix a header type first (in its
own commit) when a cast exists because the generated type is wrong, and run this afterwards.

The casts this drops are code-generation neutral by construction - it was 0 changed instructions over the
ViewportRenderState namespace - but re-measure anyway. It cannot see overloads: a cast that selects between
`f(short)` and `f(int)` would be dropped, which does not occur in the generated code. Dry run unless
--apply; --show prints each cast it would drop. Run test_dropcast.py after changing it.
"""

import glob
import re
import sys

import common

NARROW_SIGNED = {"short", "char", "sbyte", "bool", "undefined2"}
NARROW_UNSIGNED = {"ushort", "uchar", "byte", "undefined1", "BYTE", "WORD", "word"}
INTLIKE = {"int", "long", "BOOL", "BOOLEnum"}
KEYWORDS = {"return", "else", "case", "goto", "do", "new", "delete", "throw", "sizeof", "typedef", "const"}

POSTFIX = re.compile(r"[A-Za-z_]\w*(?:(?:::|\.|->)[A-Za-z_]\w*|\[(?:[^\[\]]|\[(?:[^\[\]]|\[[^\[\]]*\])*\])*\])*")
SUBSCRIPTS = re.compile(r"\[(?:[^\[\]]|\[(?:[^\[\]]|\[[^\[\]]*\])*\])*\]")
MEMBER = re.compile(r"\s+([A-Za-z_][\w:]*\s*\**)\s+([A-Za-z_]\w*)\s*(\[[^;]*\])?;\s*//\s*0x")
STRUCT = re.compile(r"\s*(?:typedef\s+)?(?:struct|class)\s+(\w+)\s*(?::[^{]*)?\{")


class Types(object):
    """Field, typedef and global types, from header texts (all generated headers by default)."""

    def __init__(self, headers=None, globals_=None):
        if headers is None:
            headers = [common.read_text(h) for h in glob.glob("src/OpenSHC/**/*.hpp", recursive=True)]
        if globals_ is None:
            globals_ = [common.read_text(h) for h in glob.glob("src/OpenSHC/Globals/*.hpp")]
        self.signed = set(NARROW_SIGNED)
        self.unsigned = set(NARROW_UNSIGNED)
        self.struct_fields = {}
        self.field_types = {}
        self.globals = {}
        for text in headers:
            for m in re.finditer(r"typedef\s+(short|ushort|unsigned short|char|byte|uchar)\s+(\w+)\s*;", text):
                (self.signed if m.group(1) in ("short", "char") else self.unsigned).add(m.group(2))
            cur = None
            for line in text.splitlines():
                m = STRUCT.match(line)
                if m:
                    cur = m.group(1)
                    self.struct_fields.setdefault(cur, {})
                    continue
                m = MEMBER.match(line)
                if m:
                    t = re.sub(r"\s+", "", m.group(1)).split("::")[-1]
                    if m.group(3):
                        t += "[]"  # an array is not an integer, but its element is: see walk()
                    self.field_types.setdefault(m.group(2), set()).add(t)
                    if cur:
                        self.struct_fields[cur][m.group(2)] = t
        for text in globals_:
            for m in re.finditer(r"MACRO_STRUCT_RESOLVER\(\s*([\w:]+)\s*,[^)]*\)\s*(\w+)\s*;", text):
                self.globals[m.group(2)] = m.group(1).split("::")[-1]

    @property
    def narrow(self):
        return self.signed | self.unsigned


def element(t):
    """The type an access produces once subscripted: `short[]` and `short*` indexed are a short."""
    if t.endswith("[]"):
        return t[:-2]
    return t[:-1] if t.endswith("*") else t


def local_types(src):
    lt = {}
    for m in re.finditer(r"^\s+((?:unsigned |signed )?[A-Za-z_][\w:]*)\s+([^;=(){}]+);", src, re.M):
        t = m.group(1).split("::")[-1].replace("unsigned short", "ushort")
        if t in KEYWORDS:
            continue
        for name in m.group(2).split(","):
            name = name.strip()
            if name.startswith("*"):
                lt.setdefault(name.lstrip("*"), set()).add(t + "*")
            elif re.match(r"^[A-Za-z_]\w*$", name):
                lt.setdefault(name, set()).add(t)
            elif re.match(r"^[A-Za-z_]\w*\s*\[", name):
                lt.setdefault(name.split("[")[0].strip(), set()).add(t + "[]")
    for m in re.finditer(r"\b((?:unsigned |signed )?[A-Za-z_][\w:]*)\s*(\*?)\s*(?:const\s+)?([A-Za-z_]\w*)\s*=[^=]", src):
        if m.group(1) not in KEYWORDS:
            lt.setdefault(m.group(3), set()).add(m.group(1).split("::")[-1] + m.group(2))
    for m in re.finditer(r"[(,]\s*((?:unsigned |signed )?[A-Za-z_][\w:]*)\s*(\*?)\s*([A-Za-z_]\w*)\s*(?=[,)])", src):
        if m.group(1) not in KEYWORDS:
            lt.setdefault(m.group(3), set()).add(m.group(1).split("::")[-1] + m.group(2))
    return lt


class Function(object):
    """The type environment of one source file: its `this` class and its locals."""

    def __init__(self, src, types):
        self.types = types
        self.locals = local_types(src)
        m = re.search(r"FUNCTION: STRONGHOLDCRUSADER[^\n]*\n[^\n(]*?(\w+)::\w+\(", src)
        self.this = m.group(1) if m else None

    def walk(self, seg, indexed):
        """Types of a member chain resolved from its root, or None. `indexed` says whether the final member
        was subscripted, which turns an array field into its element."""
        if seg[0] == "this" and self.this:
            cur, rest = self.this, seg[1:]
        elif len(seg) >= 2 and seg[1] in ("instance", "ptr"):
            cur, rest = self.types.globals.get(seg[0], re.sub(r"^DAT_", "", seg[0])), seg[2:]
        else:
            return None
        t = None
        for name in rest:
            t = self.types.struct_fields.get(cur, {}).get(name)
            if t is None:
                return None
            cur = element(t).rstrip("*")
        if t is None:
            return None
        return {element(t) if indexed else t}

    def types_of(self, expr):
        """Possible types of a postfix chain such as `this->a.b[i]`."""
        e = re.sub(r"\s*(\.|->|::|\[|\])\s*", r"\1", expr)
        indexed = e.endswith("]")
        e = SUBSCRIPTS.sub("", e)
        seg = re.split(r"::|\.|->", e)
        if len(seg) == 1:
            ts = self.locals.get(seg[0], set())
            return set(element(t) for t in ts) if indexed else ts
        walked = self.walk(seg, indexed)
        if walked:
            return walked
        ts = self.types.field_types.get(seg[-1], set())
        return set(element(t) for t in ts) if indexed else ts

    def narrowness(self, expr):
        ts = self.types_of(expr)
        if not ts:
            return None
        if ts <= self.types.signed:
            return "signed"
        if ts <= self.types.unsigned:
            return "unsigned"
        if ts <= self.types.narrow:
            return "mixed"
        return None

    def is_int(self, expr):
        ts = self.types_of(expr)
        return bool(ts) and ts <= INTLIKE

    def int_expression(self, expr):
        """True when expr is built only from int/narrow operands, int literals and + - * / % ( )."""
        expr = re.sub(r"\s*(\.|->|::|\[|\])\s*", r"\1", expr)
        pos = 0
        while pos < len(expr):
            ch = expr[pos]
            if ch.isspace() or ch in "+-*/%()":
                pos += 1
                continue
            m = re.match(r"0[xX][0-9a-fA-F]+|\d+", expr[pos:])
            if m:
                lit = m.group(0)
                nxt = expr[pos + len(lit):pos + len(lit) + 1]
                if nxt and (nxt.isalnum() or nxt in "_."):
                    return False  # a suffix (U, L) or a float
                if int(lit, 0) > 0x7fffffff:
                    return False
                pos += len(lit)
                continue
            if expr.startswith("(int)", pos):
                pos += 5
                continue
            pm = POSTFIX.match(expr, pos)
            if not pm or expr[pm.end():pm.end() + 1] == "(":
                return False  # not an operand, or a call
            ts = self.types_of(pm.group(0))
            if not ts or not ts <= (self.types.narrow | INTLIKE):
                return False
            pos = pm.end()
        return True


def match_paren(s, i):
    d = 0
    for k in range(i, len(s)):
        if s[k] == "(":
            d += 1
        elif s[k] == ")":
            d -= 1
            if d == 0:
                return k
    return -1


def process(src, types, show=False):
    """(new text, number of casts dropped)."""
    fn = Function(src, types)
    out, i, n = [], 0, 0
    pat = re.compile(r"\((int|uint)\)\s*")
    while True:
        m = pat.search(src, i)
        if not m:
            out.append(src[i:])
            break
        start = m.end()
        paren = src[start:start + 1] == "("
        pm = POSTFIX.match(src, start + 1 if paren else start)
        if not pm or (paren and src[pm.end():pm.end() + 1] != ")") or (not paren and src[pm.end():pm.end() + 1] == "("):
            # not a lone lvalue: maybe a whole int expression in brackets
            close = match_paren(src, start) if paren else -1
            if m.group(1) == "int" and close > 0 and fn.int_expression(src[start + 1:close]):
                inner = src[start + 1:close]
                prev = src[:m.start()].rstrip()[-1:]
                nxt = src[close + 1:].lstrip()[:1]
                # an argument or a bracketed operand needs no brackets of its own
                bare = prev in "(," and nxt in ",)"
                if show:
                    print("   E (int)(%s)" % " ".join(inner.split())[:70])
                out.append(src[i:m.start()])
                out.append(inner if bare else "(" + inner + ")")
                i = close + 1
                n += 1
                continue
            out.append(src[i:m.end()])
            i = m.end()
            continue
        expr = pm.group(0)
        end = pm.end() + (1 if paren else 0)
        kind = fn.narrowness(expr)
        prev = src[:m.start()].rstrip()[-1:]
        whole_subscript = prev == "[" and src[end:].lstrip().startswith("]")
        if (m.group(1) == "int" and (kind is not None or fn.is_int(expr))) or \
                (whole_subscript and kind == "unsigned"):
            if show:
                print("   - %s%s" % (m.group(0), expr))
            out.append(src[i:m.start()])
            out.append(expr)
            i = end
            n += 1
        else:
            out.append(src[i:m.end()])
            i = m.end()
    return "".join(out), n


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    path_filter = args[0] if args else ""
    apply_ = "--apply" in sys.argv
    show = "--show" in sys.argv
    types = Types()
    total = 0
    for f in common.list_files():
        if path_filter not in f:
            continue
        old = common.read_text(f).replace("\r\n", "\n")
        if show:
            print(f)
        # repeat: dropping the inner cast of (int)((int)(x)) exposes the outer one
        new, n = process(old, types, show)
        while True:
            new, more = process(new, types, show)
            if not more:
                break
            n += more
        if not n:
            continue
        print("%-52s %d" % (f.rsplit("/", 1)[-1][:-4], n))
        total += n
        if apply_:
            common.write_text(f, new)
            common.format_file(f)
    print("%d redundant cast(s) dropped%s" % (total, "" if apply_ else " (dry run, pass --apply)"))


if __name__ == "__main__":
    main()
