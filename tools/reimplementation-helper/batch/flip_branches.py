"""Swap if/else arms into the order the original laid them out.

usage:
  flip_branches.py FILE.cpp [--chains]                 list the if/else statements that can be flipped
  flip_branches.py FILE.cpp --find [--min-ratio R]     ... and mark those the original lays out the other way round
  flip_branches.py FILE.cpp --apply LINES [--out F]    flip the ifs starting on LINES (`12,40-44`); `found` = every
                                                       --find hit. Writes FILE in place unless --out is given.

MSVC lays out an if/else with the *then* arm as the fall-through after the test and the else arm at the jump
target. Ghidra prints the jump target first, so a decompiled `if ((x & m) == 0) {A} else {B}` was usually
written `if ((x & m) != 0) {B} else {A}`: the same test, compiled the other way round, moving every block
after it. Flipping every mask test in `renderMap` this way was worth 4 points; flipping `x == 0` tests paid
14 times out of 17, so plain comparisons need measuring one by one (`--out` writes a variant for
quick_styles.py) - and `cmp x, 2; jl` still means the source said `x >= 2`, which flipping does not fix.

A flippable statement is `if (A op B) {..} else {..}` with exactly one comparison (== != < <= > >=) at the top
level of the condition and no && || ?: beside it. Flipping inverts the operator and exchanges the arms, which is
the same program for integers. With `--chains`, the head of an else-if chain is flippable too:
`if (C) {A} else if (D) {B} ...` becomes `if (!C) { if (D) {B} ... } else {A}`, one level deeper.

`--find` compiles the file (quick_diff.py's /FA path), cuts both sides into basic blocks, pairs our blocks with
the original's by register-canonical content, and reports each conditional branch whose fall-through pairs with
the original's jump target and vice versa. The line printed is the one MSVC attributes the branch to, which for
an if is the line the statement starts on. Block pairing is a heuristic: confirm every flip by measuring.
"""

import difflib
import os
import re
import sys

import common

COMPARE = {"==": "!=", "!=": "==", "<": ">=", ">=": "<", ">": "<=", "<=": ">"}
JCC = {"je", "jne", "jl", "jle", "jg", "jge", "jb", "jbe", "ja", "jae", "js", "jns", "jp", "jnp", "jo", "jno"}


# ---------------------------------------------------------------- source side

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


def block_end(s, ob):
    d = 0
    for i in range(ob, len(s)):
        if s[i] == "{":
            d += 1
        elif s[i] == "}":
            d -= 1
            if d == 0:
                return i
    return -1


def top_level_compare(cond):
    """(lhs, op, rhs) when cond is a single comparison with nothing else at its top level, otherwise None."""
    depth = 0
    found = []
    i = 0
    while i < len(cond):
        c = cond[i]
        two = cond[i:i + 2]
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif depth == 0:
            if two in ("&&", "||") or c in "?,":
                return None
            if two in ("<<", ">>", "->"):
                i += 3 if cond[i + 2:i + 3] == "=" else 2
                continue
            if two in ("==", "!=", "<=", ">="):
                found.append((i, two))
                i += 2
                continue
            if c in "<>":
                found.append((i, c))
            elif c == "=" and cond[i - 1:i] not in "=!<>":
                return None  # an assignment
        i += 1
    if len(found) != 1:
        return None
    k, op = found[0]
    return cond[:k].strip(), op, cond[k + len(op):].strip()


def strip_outer(cond):
    cond = cond.strip()
    while cond.startswith("(") and match_paren(cond, 0) == len(cond) - 1:
        cond = cond[1:-1].strip()
    return cond


class Site(object):
    """One flippable `if`: positions in the text and its parts."""

    def __init__(self, s, start):
        self.start = start
        self.line = s.count("\n", 0, start) + 1
        self.po = s.index("(", start)
        self.pc = match_paren(s, self.po)
        self.cond = s[self.po + 1:self.pc]
        self.cond_last_line = s.count("\n", 0, self.pc) + 1
        self.compare = top_level_compare(strip_outer(self.cond))
        ws = re.match(r"\s*\{", s[self.pc + 1:])
        self.ok = bool(ws) and self.compare is not None
        if not self.ok:
            return
        self.ob = self.pc + ws.end()
        self.cb = block_end(s, self.ob)
        rest = s[self.cb + 1:]
        el = re.match(r"\s*else\s*\{", rest)
        elif_ = re.match(r"\s*else\s+if\s*\(", rest)
        if el:
            self.kind = "else"
            self.eob = self.cb + el.end()
            self.ecb = block_end(s, self.eob)
        elif elif_:
            self.kind = "chain"
            self.eob = self.cb + 1 + rest.index("if", elif_.start())
            self.ecb = chain_end(s, self.eob)
        else:
            self.ok = False
            return
        lhs, op, rhs = self.compare
        self.label = "mask" if re.search(r"[^&]&[^&]", " " + lhs + " ") and rhs == "0" else \
            ("zero" if rhs == "0" else "compare")

    def inverted(self):
        lhs, op, rhs = self.compare
        return "%s %s %s" % (lhs, COMPARE[op], rhs)


def chain_end(s, k):
    """End (inclusive) of the else-if chain whose first `if` starts at k."""
    while True:
        po = s.index("(", k)
        pc = match_paren(s, po)
        ob = s.index("{", pc)
        cb = block_end(s, ob)
        m = re.match(r"\s*else\s*(if\s*\()?", s[cb + 1:])
        if not m:
            return cb
        if not m.group(1):
            return block_end(s, s.index("{", cb + 1))
        k = cb + 1 + m.start(1)


def sites(s):
    out = []
    for m in re.finditer(r"\bif\s*\(", s):
        if re.search(r"\belse\s*$", s[max(0, m.start() - 20):m.start()]):
            continue  # an else-if link, flipped (if at all) through the head of its chain
        site = Site(s, m.start())
        if site.ok:
            out.append(site)
    return out


def flip(s, site):
    then_ = s[site.ob + 1:site.cb]
    if site.kind == "else":
        other = s[site.eob + 1:site.ecb]
        new = "if (%s) {%s} else {%s}" % (site.inverted(), other, then_)
        return s[:site.start] + new + s[site.ecb + 1:]
    chain = s[site.eob:site.ecb + 1]
    new = "if (%s) {\n%s\n} else {%s}" % (site.inverted(), chain, then_)
    return s[:site.start] + new + s[site.ecb + 1:]


def apply_flips(s, lines, chains):
    """Flip the sites starting on `lines`, innermost first; each flip re-parses, so nested flips stay valid."""
    MARK = "/*FLIP*/"
    todo = [x for x in sites(s) if x.line in lines and (chains or x.kind == "else")]
    for x in sorted(todo, key=lambda x: -x.start):
        s = s[:x.start] + MARK + s[x.start:]
    n = 0
    while MARK in s:
        k = s.rindex(MARK)
        s = s[:k] + s[k + len(MARK):]
        site = Site(s, k)
        s = flip(s, site)
        n += 1
    return s, n


# ---------------------------------------------------------------- finding

def find_flips(path, min_ratio=0.8):
    """[(source line, our branch mnemonic, original block address)] for branches laid out the other way round."""
    sys.argv = [sys.argv[0]]
    import quick_diff as qd
    a, b = qd.streams(os.path.abspath(path))
    if b is None:
        sys.exit("compile failed")
    ca, cb = qd.register_canon(a), qd.register_canon(b)
    oflow, uflow, lines = list(qd.orig_flow), list(qd.our_flow), list(qd.our_lines)

    def blocks(text, starts, target_of):
        bl = []
        for k, t in enumerate(text):
            if k in starts or not bl:
                bl.append({"k0": k, "ins": []})
            bl[-1]["ins"].append(t)
            bl[-1]["k1"] = k
        index = {b_["k0"]: n for n, b_ in enumerate(bl)}
        for b_ in bl:
            k = b_["k1"]
            op = text[k].split(" ")[0]
            b_["cond"] = op in JCC
            b_["fall"] = None if op in ("jmp", "ret") else index.get(k + 1)
            t = target_of(k)
            b_["tgt"] = index.get(t) if t is not None else None
        return bl

    # original: blocks start at branch targets and after branches
    addr_index = {addr: k for k, (addr, t) in enumerate(oflow)}
    ostarts = set(addr_index[t] for addr, t in oflow if t in addr_index)
    ostarts |= set(k + 1 for k, x in enumerate(ca) if x.split(" ")[0] in JCC | {"jmp", "ret"})
    OB = blocks(ca, ostarts, lambda k: addr_index.get(oflow[k][1]))
    # ours: blocks start at labels and after branches
    label_index = {}
    for k, (labels, t) in enumerate(uflow):
        for lab in labels:
            label_index[lab] = k
    ustarts = set(label_index.values()) | set(k + 1 for k, x in enumerate(cb) if x.split(" ")[0] in JCC | {"jmp", "ret"})
    UB = blocks(cb, ustarts, lambda k: label_index.get(uflow[k][1]))

    # a flipped test ends in the inverted jump (jne for je), so compare blocks with the condition left out:
    # otherwise every two-instruction test block scores 0.5 against its counterpart and is never paired
    def shape(ins):
        return ["jcc L" if x.split(" ")[0] in JCC else x for x in ins]

    for b_ in OB + UB:
        b_["shape"] = shape(b_["ins"])
    match = {}
    for n, ub in enumerate(UB):
        if len(ub["ins"]) < 2:
            continue
        pos = n / float(len(UB))
        best, best_score = None, 0
        for m, ob in enumerate(OB):
            if abs(len(ob["ins"]) - len(ub["ins"])) > max(3, len(ub["ins"]) // 2):
                continue
            r = difflib.SequenceMatcher(None, ub["shape"], ob["shape"], autojunk=False).ratio()
            if r < min_ratio:
                continue
            score = r - 0.3 * abs(pos - m / float(len(OB)))
            if score > best_score:
                best, best_score = m, score
        if best is not None:
            match[n] = best

    found = set()
    for n, ub in enumerate(UB):
        if not ub["cond"] or n not in match:
            continue
        ob = OB[match[n]]
        if not ob["cond"]:
            continue
        f = match.get(ub["fall"]) if ub["fall"] is not None else None
        t = match.get(ub["tgt"]) if ub["tgt"] is not None else None
        if f is not None and t is not None and f != t and f == ob["tgt"] and t == ob["fall"]:
            found.add((lines[ub["k1"]], cb[ub["k1"]].split(" ")[0], oflow[ob["k0"]][0]))
    return sorted(found)


# ---------------------------------------------------------------- main

def parse_lines(spec):
    out = set()
    for part in spec.split(","):
        a, _, b = part.partition("-")
        out.update(range(int(a), int(b or a) + 1))
    return out


def main():
    argv = sys.argv[1:]
    if not argv:
        sys.exit(__doc__)
    path = common.repo_relative(argv[0])
    chains = "--chains" in argv
    src = common.read_text(path).replace("\r\n", "\n")
    min_ratio = float(argv[argv.index("--min-ratio") + 1]) if "--min-ratio" in argv else 0.8

    hits = {}
    if "--find" in argv or "found" in argv:
        for line, op, addr in find_flips(path, min_ratio):
            hits.setdefault(line, (op, addr))

    def hit_for(site):
        for ln in range(site.line, site.cond_last_line + 1):
            if ln in hits:
                return hits[ln]
        return None

    all_sites = [x for x in sites(src) if chains or x.kind == "else"]
    if "--apply" not in argv:
        for x in all_sites:
            h = hit_for(x)
            if "--find" in argv and not h:
                continue
            print("%5d  %-7s %-5s if (%s)%s" % (x.line, x.label, x.kind, " ".join(x.cond.split())[:80],
                                                "   <- FLIP (orig %08x)" % h[1] if h else ""))
        if "--find" in argv:
            unplaced = sorted(set(hits) - set(ln for x in all_sites for ln in range(x.line, x.cond_last_line + 1)))
            if unplaced:
                print("branches laid out the other way round with no flippable if on their line: %s"
                      % " ".join(map(str, unplaced)))
        return

    spec = argv[argv.index("--apply") + 1]
    if spec == "found":
        lines = set(x.line for x in all_sites if hit_for(x))
    else:
        lines = parse_lines(spec)
    out, n = apply_flips(src, lines, chains)
    dest = str((common.INVOCATION_DIR / argv[argv.index("--out") + 1]).resolve()) if "--out" in argv else path
    common.write_text(dest, out)
    common.format_file(dest)
    print("flipped %d if statement(s) -> %s" % (n, dest))


if __name__ == "__main__":
    main()
