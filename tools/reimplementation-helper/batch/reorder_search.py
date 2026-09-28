"""Hill-climb the match % by reordering independent statements.

usage: reorder_search.py CPP-FILE FUNCTION-SUBSTRING [--pairs] [--dry]

MSVC's register allocation is sensitive to the order in which values become
live, so reordering statements that are independent of each other can change it
without changing behaviour.  The search applies one move, rebuilds, measures,
and keeps the move only if reccmp's percentage rises; anything else is reverted.
Put only the one file in cmake/openshc-sources.txt.local first, or each trial
costs a full build.

Moves:
  default   permute whole runs of >=3 mutually independent statements
            (reverse / rotate / counter-rotate) - 3 builds per run
  --pairs   swap every adjacent independent pair - 1 build per pair, much
            slower on a big function but finds things runs cannot

Two statements count as independent when neither contains a call, their
left-hand sides differ, neither left-hand side appears in the other statement,
no plain local written by one is mentioned by the other, and two writes through
the same array base are distinct named fields of the identical element.  That
is deliberately conservative; verify the kept reorder by reading the diff.

Expect a low hit rate - about one move in ten pays, and usually a fraction of a
point.  The exceptions are statements that sit on a boundary, between two calls
or on a loop back-edge, where the order decides what is live in which register:
those have been worth 2 points.  Run it after the structural work, not before.
"""

import json
import re
import subprocess
import sys
from pathlib import Path

import common  # noqa: F401  (chdirs to the repo root)

CPP, FUNC = sys.argv[1], sys.argv[2]
PAIRS = "--pairs" in sys.argv
DRY = "--dry" in sys.argv
ID = re.compile(r"[A-Za-z_]\w*")
CALL = re.compile(r"\bMACRO_CALL\w*\s*\(|\b\w+\s*\([^)]")


def build_and_score():
    r = subprocess.run([sys.executable, "tools/reimplementation-helper/batch/build_quiet.py"],
                       capture_output=True, text=True)
    if "BUILD_OK" not in r.stdout:
        return None
    subprocess.run([sys.executable, "tools/reimplementation-helper/batch/reccmp_report.py", "--run", "pct"],
                   capture_output=True, text=True)
    for e in json.loads(Path("reccmp/dll/diff.json").read_text())["data"]:
        if e["name"].endswith(FUNC):
            return float(e["matching"])
    return None


def statements(lines, lo, hi):
    """(start, end, depth) for each statement in lines[lo:hi] at a single brace depth."""
    out, depth, i = [], 0, lo
    keywords = ("for", "while", "return", "break", "continue", "goto", "case", "default")
    while i < hi:
        s = lines[i].strip()
        d0 = depth
        depth += lines[i].count("{") - lines[i].count("}")
        if s.endswith(";") and d0 == depth and not s.startswith(keywords):
            out.append((i, i + 1, d0))
            i += 1
            continue
        if s and not s.endswith((";", "{", "}")) and d0 == depth:
            j = i
            while j < hi and not lines[j].strip().endswith(";"):
                if "{" in lines[j] or "}" in lines[j]:
                    j = -1
                    break
                j += 1
            if j != -1 and j < hi:
                out.append((i, j + 1, d0))
                i = j + 1
                continue
        i += 1
    return out


def split_assign(text):
    m = re.match(r"\s*([^=;]+?)\s*=(?!=)(.*)", text, re.S)
    return (None, None) if not m else (" ".join(m.group(1).split()), m.group(2))


def independent(a, b):
    if CALL.search(a) or CALL.search(b):
        return False
    la, _ = split_assign(a)
    lb, _ = split_assign(b)
    if la is None or lb is None or la == lb:
        return False
    na, nb = " ".join(a.split()), " ".join(b.split())
    if "[" in la and "[" in lb and la.split("[")[0].strip() == lb.split("[")[0].strip():
        pa, pb = la.rsplit("]", 1), lb.rsplit("]", 1)
        if not (pa[0] == pb[0] and pa[1].startswith(".") and pb[1].startswith(".") and pa[1] != pb[1]):
            return False
    if la in nb or lb in na:
        return False
    for lhs, other in ((la, nb), (lb, na)):
        if ID.fullmatch(lhs) and re.search(r"\b%s\b" % re.escape(lhs), other):
            return False
    for lhs, other_lhs in ((la, lb), (lb, la)):
        if ID.fullmatch(other_lhs) and re.search(r"\b%s\b" % re.escape(other_lhs), lhs):
            return False
    return True


def text_of(lines, entry):
    return "\n".join(lines[entry[0]:entry[1]])


def runs(lines, st):
    out, i = [], 0
    while i < len(st):
        j = i
        while j + 1 < len(st):
            if st[j][1] != st[j + 1][0] or st[j][2] != st[j + 1][2]:
                break
            if not all(independent(text_of(lines, st[k]), text_of(lines, st[j + 1])) for k in range(i, j + 1)):
                break
            j += 1
        if j - i + 1 >= 3:
            out.append((i, j))
        i = j + 1 if j > i else i + 1
    return out


def read():
    return Path(CPP).read_text(encoding="utf-8").split("\n")


def write(ls):
    Path(CPP).write_text("\n".join(ls), encoding="utf-8", newline="")


best = build_and_score()
if best is None:
    sys.exit("baseline build failed")
print("baseline %.2f%%" % (best * 100))

improved, rnd = True, 0
while improved and rnd < 3:
    improved, rnd = False, rnd + 1
    lines = read()
    f = next(i for i, l in enumerate(lines) if "// FUNCTION:" in l)
    st = statements(lines, f, len(lines))
    if PAIRS:
        moves = []
        for k in range(len(st) - 1):
            if st[k][1] == st[k + 1][0] and st[k][2] == st[k + 1][2] \
                    and independent(text_of(lines, st[k]), text_of(lines, st[k + 1])):
                moves.append((st[k][0], st[k][1], st[k + 1][0], st[k + 1][1]))
        print("round %d: %d candidate swaps" % (rnd, len(moves)))
        if DRY:
            break
        for a0, a1, b0, b1 in reversed(moves):
            cur = read()
            write(cur[:a0] + cur[b0:b1] + cur[a0:a1] + cur[b1:])
            sc = build_and_score()
            if sc is not None and sc > best + 1e-9:
                print("  keep swap L%d<->L%d  %.2f -> %.2f" % (a0 + 1, b0 + 1, best * 100, sc * 100))
                best, improved = sc, True
            else:
                write(cur)
    else:
        rs = runs(lines, st)
        print("round %d: %d independent runs (lengths %s)" % (rnd, len(rs), [b - a + 1 for a, b in rs]))
        if DRY:
            break
        for a, b in reversed(rs):
            lines = read()
            st = statements(lines, next(i for i, l in enumerate(lines) if "// FUNCTION:" in l), len(lines))
            if b >= len(st):
                continue
            blocks = [lines[st[k][0]:st[k][1]] for k in range(a, b + 1)]
            lo, hi, n = st[a][0], st[b][1], len(blocks)
            for tag, order in (("reverse", list(reversed(range(n)))),
                               ("rotate", list(range(1, n)) + [0]),
                               ("counter-rotate", [n - 1] + list(range(n - 1)))):
                cur = read()
                shuffled = [line for idx in order for line in blocks[idx]]
                write(cur[:lo] + shuffled + cur[hi:])
                sc = build_and_score()
                if sc is not None and sc > best + 1e-9:
                    print("  keep %s L%d..L%d  %.2f -> %.2f" % (tag, lo + 1, hi, best * 100, sc * 100))
                    best, improved = sc, True
                    break
                write(cur)
print("final %.2f%%" % (best * 100))
