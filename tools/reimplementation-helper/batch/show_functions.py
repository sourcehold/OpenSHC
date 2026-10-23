"""Print the function bodies of list files under a path prefix, with their match percentages.

usage: show_functions.py PREFIX [--skip-100] [--snapshot SNAPSHOT.json]

PREFIX is relative to src/OpenSHC (e.g. "Map/Units"). Percentages come from the
snapshot written by `reccmp_report.py save`, otherwise from the last reccmp run.
The output uses the same '@@@ path' block format that splice_functions.py reads.
"""

import argparse
import json
import os

import common

parser = argparse.ArgumentParser()
parser.add_argument("prefix")
parser.add_argument("--skip-100", action="store_true", help="print only the header for functions already at 100%%")
parser.add_argument("--snapshot")
args = parser.parse_args()

if args.snapshot:
    pct = json.load(open(args.snapshot))
else:
    pct = {e["name"]: [float(e["matching"]), common.normalized_ratio(e)]
           for f, e, a in common.entries(common.load_diff()) if e}
by_short_name = {name.split("::")[-1].lower(): v for name, v in pct.items()}

for f in sorted(common.list_files()):
    if not f.startswith("src/OpenSHC/" + args.prefix):
        continue
    text = common.read_text(f)
    value = by_short_name.get(os.path.basename(f)[:-4].lower())
    label = "%.1f/%.1f" % (value[0] * 100, value[1] * 100) if value else "?"
    print("@@@ %s [%s]" % (f[len("src/OpenSHC/"):], label))
    if args.skip_100 and value and value[0] >= 1 or "// FUNCTION:" not in text:
        continue
    begin, end = common.function_body_span(text)
    lines = text[begin:end].split("\n")
    indent = len(lines[-1]) - len(lines[-1].lstrip())
    print("\n".join([lines[0].strip()] + [l[indent:] if not l[:indent].strip() else l for l in lines[1:]]))
