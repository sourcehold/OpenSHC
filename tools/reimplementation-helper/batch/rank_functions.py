"""Rank the listed functions by how much of them still differs.

The score is source lines x (1 - match), so it puts the big, badly matching functions
first instead of the small ones with a low percentage. Use it to pick what to work on.

usage:
  rank_functions.py [path-filter] [--top N]
"""

import argparse

import common

parser = argparse.ArgumentParser()
parser.add_argument("path_filter", nargs="?", default="")
parser.add_argument("--top", type=int, default=25)
args = parser.parse_args()

rows = []
for f, e, a in common.entries(common.load_diff()):
    if e is None or args.path_filter not in f:
        continue
    lines = len(common.read_text(f).splitlines())
    raw = float(e["matching"])
    rows.append((lines * (1 - raw), lines, raw, common.normalized_ratio(e), e["name"]))

rows.sort(reverse=True)
print("%7s %6s %6s %6s  %s" % ("lost", "lines", "raw", "norm", "function"))
for lost, lines, raw, norm, name in rows[:args.top]:
    print("%7.0f %6d %5.1f%% %5.1f%%  %s" % (lost, lines, raw * 100, norm * 100, name.split("::")[-1]))
if rows:
    print("%d functions, average raw %.2f%%"
          % (len(rows), sum(r[2] for r in rows) / len(rows) * 100))
