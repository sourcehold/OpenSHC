"""Report functions whose dispatch form disagrees with the original.

A jump table compiles to `jmp dword ptr [reg*4 + <table>]`. Counting those on each side
of the diff finds the places where the original switched on a value and we wrote an
if/else-if chain, or the other way round. Both directions have been worth several
percent, so it is worth checking before hunting through a diff by hand.

  ours > orig   a switch of ours became a table the original does not have
                -> try an if/else-if chain
  ours < orig   the original has a table we do not
                -> try a switch, or check that every value has its own case label
                   (handing values to `default:` and re-testing them with an if drops
                   them out of the table)

usage:
  scan_dispatch.py [path-filter]
"""

import sys

import common

path_filter = sys.argv[1] if len(sys.argv) > 1 else ""

rows = []
for f, e, a in common.entries(common.load_diff()):
    if e is None or path_filter not in f:
        continue
    orig, recomp = common._asm_lines(e)
    ours = sum(1 for l in recomp if "jmp dword ptr" in l)
    theirs = sum(1 for l in orig if "jmp dword ptr" in l)
    if ours != theirs:
        rows.append((abs(ours - theirs), ours, theirs, float(e["matching"]), e["name"]))

rows.sort(reverse=True)
print("%5s %5s %7s  %s" % ("ours", "orig", "match", "function"))
for _, ours, theirs, raw, name in rows:
    print("%5d %5d %6.1f%%  %s" % (ours, theirs, raw * 100, name.split("::")[-1]))
print("%d function(s) where the dispatch form differs" % len(rows))
