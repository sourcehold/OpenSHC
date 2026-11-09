"""Put the case bodies of every switch in the order the original compiled them.

usage:
  switch_order.py FILE.cpp                    report each switch: its jump table, and whether the case order agrees
  switch_order.py FILE.cpp --apply [LINE...]  reorder the switches that disagree (only those starting on LINE...)
  switch_order.py FILE.cpp --tables           decode the original's jump tables only: case values per target
  switch_order.py FILE.cpp --order LINE V,V,..  reorder the switch on LINE by hand, listing a value of each group

MSVC emits the case bodies of a switch in source order, so the original's jump table *is* its source order: sort
the targets by address and read off which case values reach each one. Ghidra prints the cases sorted by value,
which on a big switch puts almost every body in the wrong place - every jump into it, every tail merge between
neighbours and every fall-through block moves with it. Restoring the order took `renderGmOverlayBuilding` from
37% to 60% on its own, with no other change.

Each source switch is matched to the table (or tables, when MSVC split a sparse switch) whose case values it
shares. Groups that fall through into the next one move as one unit, and the last group gets a `break;` if it
lacks one, so reordering cannot change behaviour. A group counts as ending in a jump only when its last
*top-level* statement is `break`/`return`/`continue`/`goto`: `if (x) { ...; break; }` still falls through
when x is false. Groups whose values reach no table (a part MSVC dispatched by compares) keep their place
behind the group that precedes them.

Case labels are resolved through the enum values in the generated headers; a label whose name has different
values in different headers is reported and left in place. Re-measure after applying: the order is right by
construction, but which neighbour a shared tail merges into can still move the score either way.
"""

import glob
import re
import struct
import sys

import capstone

import common

CASE_RE = re.compile(r"[ \t]*(?:case\s+(-?[\w:]+|'[^']*')\s*:(?!:)|default\s*:)")
SWITCH_RE = re.compile(r"\bswitch\s*\(")


# ---------------------------------------------------------------- original side

def jump_tables(va):
    """[(jmp address, {target: [values]}, default target)] for every `jmp [r*4 + T]` in the function at va."""
    image = common.original_image()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    o = image.off(va)
    ins = []
    furthest = va
    prev = None
    # the function ends at the first ret/jmp past every forward branch target (same rule as quick_diff.py)
    for x in md.disasm(image.data[o:o + 0x10000], va):
        if prev in ("ret", "jmp") and x.address > furthest:
            break
        if x.mnemonic.startswith("j"):
            try:
                furthest = max(furthest, int(x.op_str, 16))
            except ValueError:
                pass
        ins.append(x)
        prev = x.mnemonic
    tables = []
    for k, x in enumerate(ins):
        if x.mnemonic != "jmp" or "*4 +" not in x.op_str:
            continue
        table = int(x.op_str.split("+")[-1].strip(" ]"), 16)
        limit, btab, bias, default = None, None, 0, None
        for y in reversed(ins[max(0, k - 10):k]):
            if y.mnemonic == "movzx" and "byte ptr" in y.op_str and btab is None and limit is None:
                btab = int(y.op_str.split("+")[-1].strip(" ]"), 16)
            elif y.mnemonic == "ja" and default is None:
                default = int(y.op_str, 16)
            elif y.mnemonic == "cmp" and limit is None:
                try:
                    limit = int(y.op_str.split(",")[1], 0)
                except ValueError:
                    break
            elif limit is not None and y.mnemonic in ("add", "sub", "dec"):
                if y.mnemonic == "dec":
                    bias = 1
                    break
                try:
                    v = int(y.op_str.split(",")[1], 0)
                except ValueError:
                    break
                v = v - (1 << 32) if v >= 1 << 31 else v
                bias = -v if y.mnemonic == "add" else v
                break
        if limit is None:
            continue
        targets = {}
        for v in range(limit + 1):
            idx = image.read(btab + v, 1)[0] if btab else v
            tgt = struct.unpack("<I", image.read(table + idx * 4, 4))[0]
            if tgt != default:
                targets.setdefault(tgt, []).append(v + bias)
        tables.append((x.address, targets, default))
    return tables


# ---------------------------------------------------------------- source side

_enums = None


def enum_values():
    global _enums
    if _enums is None:
        _enums = {}
        for h in glob.glob("src/OpenSHC/**/*.hpp", recursive=True):
            text = common.read_text(h)
            for m in re.finditer(r"^\s+([A-Z][A-Z0-9_]+)\s*=\s*(-?0x[0-9a-fA-F]+|-?\d+)\s*,?", text, re.M):
                _enums.setdefault(m.group(1), set()).add(int(m.group(2), 0))
    return _enums


def label_value(label):
    """The integer a case label stands for, or None (with the reason) when it cannot be resolved."""
    if label.startswith("'"):
        return ord(label[1]) if len(label) == 3 else None, "char"
    if re.match(r"^-?(0x[0-9a-fA-F]+|\d+)$", label):
        return int(label, 0), None
    vals = enum_values().get(label.split("::")[-1])
    if not vals:
        return None, "unknown"
    if len(vals) > 1:
        return None, "ambiguous"
    return next(iter(vals)), None


def block_end(s, ob):
    d = 0
    for i in range(ob, len(s)):
        if s[i] == "{":
            d += 1
        elif s[i] == "}":
            d -= 1
            if d == 0:
                return i
    raise ValueError("unbalanced braces")


def match_paren(s, i):
    d = 0
    for k in range(i, len(s)):
        if s[k] == "(":
            d += 1
        elif s[k] == ")":
            d -= 1
            if d == 0:
                return k
    raise ValueError("unbalanced parentheses")


def last_stmt_is_jump(body):
    """Whether the last top-level statement of body is a jump. A trailing if/for/switch block is not, even when
    it ends in a break: the other path still falls through. A bare block (or a case's own braces) is looked into."""
    body = re.sub(r"//[^\n]*", "", body).strip()
    if not body:
        return False
    if body.endswith("}"):
        d = 0
        for i in range(len(body) - 1, -1, -1):
            if body[i] == "}":
                d += 1
            elif body[i] == "{":
                d -= 1
                if d == 0:
                    head = body[:i].rstrip()
                    if head == "" or head.endswith(":") or head.endswith(";") or head.endswith("}"):
                        return last_stmt_is_jump(body[i + 1:-1])
                    return False
        return False
    return bool(re.search(r"(\bbreak|\breturn\b[^;]*|\bcontinue|\bgoto\s+\w+)\s*;$", body))


class Group(object):
    def __init__(self, text):
        self.text = text
        self.labels = []
        self.values = []
        self.default = False
        self.unresolved = []
        pos = 0
        while True:
            m = CASE_RE.match(text, pos)
            if not m:
                break
            if m.group(1) is None:
                self.default = True
                self.labels.append("default")
            else:
                self.labels.append(m.group(1).split("::")[-1])
                v, why = label_value(m.group(1))
                if v is None:
                    self.unresolved.append("%s (%s)" % (m.group(1).split("::")[-1], why))
                else:
                    self.values.append(v)
            pos = m.end()
            while pos < len(text) and text[pos] in " \t\n":
                pos += 1
        self.body = text[pos:]
        self.falls_through = not last_stmt_is_jump(self.body)

    def name(self):
        return self.labels[0] if self.labels else "?"


class Switch(object):
    def __init__(self, src, start):
        self.start = start
        self.line = src.count("\n", 0, start) + 1
        po = src.index("(", start)
        self.ob = src.index("{", match_paren(src, po))
        self.close = block_end(src, self.ob)
        # the groups: split at depth 1 where a run of case labels begins on a fresh line
        bounds = []
        depth = 0
        k = self.ob
        prev_label = False
        while k < self.close:
            c = src[k]
            if c == "{":
                depth += 1
            elif c == "}":
                depth -= 1
                prev_label = False
            elif c == ";":
                prev_label = False
            elif c == "\n" and depth == 1:
                m = CASE_RE.match(src, k + 1)
                if m:
                    if not prev_label:
                        bounds.append(k + 1)
                    prev_label = True
                    k = m.end() - 1
                elif src[k + 1:src.find("\n", k + 1)].strip():
                    prev_label = False
            k += 1
        self.close_line = src.rindex("\n", 0, self.close) + 1
        self.bounds = bounds
        self.groups = [Group(src[b:(bounds[i + 1] if i + 1 < len(bounds) else self.close_line)])
                       for i, b in enumerate(bounds)]

    def units(self):
        """Groups chained by fall-through, which have to stay together and in this order."""
        units, cur = [], []
        for g in self.groups:
            cur.append(g)
            if not g.falls_through:
                units.append(cur)
                cur = []
        if cur:
            units.append(cur)
        return units


def function_span(src):
    m = common.FUNCTION_RE.search(src)
    ob = src.index("{", m.end())
    return ob, block_end(src, ob)


def switches(src):
    ob, cb = function_span(src)
    return [Switch(src, m.start()) for m in SWITCH_RE.finditer(src, ob, cb)]


# ---------------------------------------------------------------- matching

def assign_tables(sws, tables):
    """{switch index: (value -> target, default target, [table addresses])}. A table goes to the switch holding
    most of its case values, so a switch MSVC split into several tables collects all of them. Two switches on
    the same values (the same dispatch written twice, or an 8-way and a 6-way switch over one direction) are
    told apart by how many bodies they have, then by which still lacks a table, then by source order - the
    tables are visited in address order, which is source order."""
    got = {}
    for addr, targets, default in tables:
        vals = set(v for vs in targets.values() for v in vs)
        best, best_score = None, None
        for i, sw in enumerate(sws):
            mine = set(v for g in sw.groups for v in g.values)
            if not mine:
                continue
            bodies = sum(1 for g in sw.groups if g.values)
            score = (len(vals & mine) / float(len(vals | mine)), -abs(len(targets) - bodies),
                     -len(got.get(i, ({}, None, []))[2]), -i)
            if best_score is None or score > best_score:
                best, best_score = i, score
        if best is None or best_score[0] < 0.3:
            continue
        vmap, dflt, addrs = got.setdefault(best, ({}, default, []))
        for tgt, vs in targets.items():
            for v in vs:
                vmap[v] = tgt
        addrs.append(addr)
    return got


def unit_key(unit, vmap, default):
    keys = []
    for g in unit:
        keys += [vmap[v] for v in g.values if v in vmap]
        if g.default and default is not None:
            keys.append(default)
    return min(keys) if keys else None


def proposed_order(sw, vmap, default):
    """The units sorted by original target address; a unit without one follows the unit before it."""
    units = sw.units()
    keyed = []
    last = -1
    for n, u in enumerate(units):
        k = unit_key(u, vmap, default)
        if k is None:
            k = last
        else:
            last = k
        keyed.append((k, n, u))
    return [u for k, n, u in sorted(keyed, key=lambda t: (t[0], t[1]))]


def render(src, sw, units):
    out = []
    for i, u in enumerate(units):
        text = "".join(g.text for g in u)
        if u[-1].falls_through and i + 1 < len(units):
            # only possible for the original last group, moved up: give it the break it leaves out
            indent = re.match(r"[ \t]*", u[-1].text).group(0) + "    "
            text = text.rstrip("\n") + "\n" + indent + "break;\n"
        out.append(text)
    return src[:sw.bounds[0]] + "".join(out) + src[sw.close_line:]


# ---------------------------------------------------------------- main

def describe(u):
    return "+".join(g.name() for g in u)


def main():
    argv = sys.argv[1:]
    if not argv:
        sys.exit(__doc__)
    path = common.repo_relative(argv[0])
    src = common.read_text(path).replace("\r\n", "\n")
    va = common.function_address(src)
    tables = jump_tables(va)

    if "--tables" in argv:
        for addr, targets, default in tables:
            print("### jmp at %08x  default %s" % (addr, "%08x" % default if default else "-"))
            for tgt in sorted(targets):
                vs = targets[tgt]
                print("  %08x  %s" % (tgt, " ".join(str(v) for v in vs) if len(vs) < 16 else "%d values" % len(vs)))
        return

    if "--order" in argv:
        k = argv.index("--order")
        line, order = int(argv[k + 1]), argv[k + 2].split(",")
        sws = [s for s in switches(src) if s.line == line]
        if not sws:
            sys.exit("no switch starts on line %d" % line)
        sw = sws[0]
        units = sw.units()
        out, used = [], set()
        for v in order:
            hit = [u for u in units if any(v == "default" and g.default or v in g.labels or v in map(str, g.values)
                                           for g in u)]
            if not hit:
                sys.exit("no group for %s" % v)
            if id(hit[0]) not in used:
                used.add(id(hit[0]))
                out.append(hit[0])
        out += [u for u in units if id(u) not in used]
        common.write_text(path, render(src, sw, out))
        common.format_file(path)
        print("reordered %d unit(s) of the switch on line %d" % (len(out), line))
        return

    apply_ = "--apply" in argv
    only = set(int(a) for a in argv[1:] if a.isdigit())
    sws = switches(src)
    assigned = assign_tables(sws, tables)
    todo = []
    for i, sw in enumerate(sws):
        units = sw.units()
        unresolved = [x for g in sw.groups for x in g.unresolved]
        head = "line %5d  %2d groups" % (sw.line, len(sw.groups))
        if i not in assigned:
            print("%s  no jump table in the original%s" % (head, "  (unresolved: %s)" % ", ".join(unresolved)
                                                             if unresolved else ""))
            continue
        vmap, default, addrs = assigned[i]
        order = proposed_order(sw, vmap, default)
        ok = [id(u[0]) for u in order] == [id(u[0]) for u in units]
        print("%s  table%s %s  %s" % (head, "s" if len(addrs) > 1 else "", ",".join("%08x" % a for a in addrs),
                                       "in order" if ok else "OUT OF ORDER"))
        chains = [describe(u) for u in units if len(u) > 1]
        if chains:
            print("            falls through: %s" % ", ".join(chains))
        if unresolved:
            print("            unresolved labels stay in place: %s" % ", ".join(unresolved))
        if not ok:
            print("            original order: %s" % " ".join(describe(u) for u in order))
            if not only or sw.line in only:
                todo.append(i)
    if not apply_ or not todo:
        return
    # innermost (latest starting) first: reordering one never moves a switch that starts before it
    for i in sorted(todo, reverse=True):
        sws = switches(src)
        sw = sws[i]
        vmap, default, _ = assign_tables(sws, tables)[i]
        src = render(src, sw, proposed_order(sw, vmap, default))
    common.write_text(path, src)
    common.format_file(path)
    print("reordered %d switch(es); re-measure with quick_diff.py / reccmp_report.py" % len(todo))


if __name__ == "__main__":
    main()
