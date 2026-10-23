"""List if/else-if chains that compare one expression against several constants.

That is the shape a switch compiles from, so when scan_dispatch.py says the original has
a jump table we do not, this finds the candidates to convert. It is also a readability
report on its own: a chain of six `x == K` tests usually reads better as a switch.

usage:
  scan_chains.py [path-filter] [--min N]
"""

import argparse
import re

import common

parser = argparse.ArgumentParser()
parser.add_argument("path_filter", nargs="?", default="")
parser.add_argument("--min", type=int, default=4, dest="least")
args = parser.parse_args()

TEST = re.compile(r"(?:\}\s*)?else\s+if\s*\(\s*(?P<lhs>[^()]+?)\s*==\s*[^()]+\)|"
                  r"^\s*if\s*\(\s*(?P<lhs2>[^()]+?)\s*==\s*[^()]+\)")

total = 0
for f in common.list_files():
    if args.path_filter not in f:
        continue
    lines = common.read_text(f).splitlines()
    lhs_run, start, count = None, 0, 0

    def report():
        global total
        if count >= args.least:
            print("%-52s line %-5d %2d branches on  %s"
                  % (f.rsplit("/", 1)[-1][:-4], start + 1, count, lhs_run[:55]))
            total += 1

    for i, line in enumerate(lines):
        m = TEST.search(line)
        lhs = (m.group("lhs") or m.group("lhs2")).strip() if m else None
        if lhs is not None and lhs == lhs_run:
            count += 1
            continue
        report()
        lhs_run, start, count = (lhs, i, 1) if lhs is not None else (None, i, 0)
    report()

print("%d chain(s) with at least %d branches" % (total, args.least))
