"""Find diff lines that are only a reccmp *symbolization* difference, not a codegen difference.

usage: diff_falsesym.py [--run] [NAME-SUBSTRING]

reccmp compares the symbolized disassembly text, so it renders an operand as `SYMBOL+N (OFFSET)`
whenever the value happens to land inside a known object. A plain integer constant that is large
enough can land inside one by coincidence - and because the two images lay their data out
differently, it lands inside an object in the original and not in ours. The same instruction then
reads as a mismatch:

    -push I<OpenSHC::Map::Buildings::BuildingsState>::instance+424671 (OFFSET)
    +push 0xffffff

Those two lines are the same four bytes. `0xffffff` is opaque white, a colour argument to a text
call, and it sits inside BuildingsState in the original image only. This was the *entire* remaining
gap of `renderDebugDataCurrentPlayerData`: 41 lines, all of them that one constant, scoring 96.0%
for code that is byte-identical to the original.

FALSESYM pairs an orig line carrying a symbol with a recomp line carrying a bare immediate when the
mnemonic and the rest of the operands are identical. It cannot prove the bytes match - it does not
know the object's base address - so confirm each hit by disassembling the original:

    ghidra-mcp disassemble_function <addr>   # or tools/.../orig_asm.py

and checking that the original really is a plain immediate. If it is, the function is finished and
no source change can raise its score; record it rather than chasing it. Beware the reverse mistake
too: a constant that *should* be an address, spelled as a literal in our source, produces the same
diff and is a real bug.

--run re-runs reccmp first (otherwise reccmp/dll/diff.json from the last run is used).
"""

import re
import sys

import common

IMM_RE = re.compile(r"^(0x[0-9a-f]+|\d+)$")
SYM_RE = re.compile(r"[A-Za-z_<>:]")


def op(line):
    return line.split("\t")[0].strip()


def split(line):
    parts = line.split(None, 1)
    return (parts[0], parts[1].strip() if len(parts) > 1 else "")


def hints_for(entry):
    hits = {}
    for hunk in entry.get("diff") or []:
        for block in hunk[1]:
            o = [op(r[1]) for r in block.get("orig", [])]
            r = [op(r[1]) for r in block.get("recomp", [])]
            if not o or len(o) != len(r):
                continue
            for a, b in zip(o, r):
                if a == b:
                    continue
                ma, oa = split(a)
                mb, ob = split(b)
                # same mnemonic, ours a bare immediate, theirs carrying a symbol
                if ma == mb and IMM_RE.match(ob) and SYM_RE.search(oa) and int(ob, 0) >= 0x10000:
                    hits[(a, b)] = hits.get((a, b), 0) + 1
    return sorted(hits.items(), key=lambda kv: -kv[1])


def main():
    args = sys.argv[1:]
    if args and args[0] == "--run":
        common.run_reccmp()
        args = args[1:]
    want = args[0] if args else ""
    byaddr = common.load_diff()
    shown = total = 0
    for f, e, a in common.entries(byaddr):
        if e is None or float(e["matching"]) >= 1 or want not in e["name"]:
            continue
        total += 1
        hits = hints_for(e)
        if not hits:
            continue
        shown += 1
        lines = sum(n for _, n in hits)
        print("### %s %.1f%% norm %.1f%%  (%d line(s) look like symbolization only)"
              % (e["name"], float(e["matching"]) * 100, common.normalized_ratio(e) * 100, lines))
        for (a, b), n in hits[:10]:
            print("  FALSESYM x%-4d orig: %s" % (n, a))
            print("  %14s ours: %s  - confirm the original is a plain immediate" % ("", b))
    if not total:
        print("nothing below 100% in the current list")
    else:
        print("\n%d of %d function(s) below 100%% have a symbolization-only hint" % (shown, total))


if __name__ == "__main__":
    main()
