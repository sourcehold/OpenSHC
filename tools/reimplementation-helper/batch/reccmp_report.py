"""Summarize reccmp results for every function in cmake/openshc-sources.txt.local.

usage:
  reccmp_report.py [--run] pct [path-filter]          match% and normalized% per function + average
  reccmp_report.py [--run] save SNAPSHOT.json         store current percentages (e.g. as a baseline)
  reccmp_report.py [--run] cmp SNAPSHOT.json [filter] compare against a snapshot (better / WORSE)
  reccmp_report.py [--run] diff NAME-SUBSTRING...     compact asm diff (-orig / +recomp)

--run re-runs reccmp first (otherwise reccmp/dll/diff.json from the last run is used,
e.g. from the openshc-mcp extract_*_assembly_diff tools).
"normalized" ignores call/tail-jump targets and resolver addresses: 100 there means
only call-name differences remain.
"""

import json
import sys

import common

args = sys.argv[1:]
if args and args[0] == "--run":
    common.run_reccmp()
    args = args[1:]
mode = args[0] if args else "pct"
byaddr = common.load_diff()

# Without --run the cached diff.json may be from a run over a different (narrower) build
# list -- try_styles.py in particular runs reccmp over a single function. Every missing
# function then just silently reads as "no entry", which turns a `save` into a snapshot of
# almost nothing and a `cmp` against it into a clean bill of health. Say so instead.
_listed = [a for f, e, a in common.entries(byaddr)]
_missing = sum(1 for f, e, a in common.entries(byaddr) if e is None)
if _listed and _missing > len(_listed) // 2:
    sys.stderr.write(
        "warning: the last reccmp run covers only %d of the %d functions in the build "
        "list.\n         Re-run with --run, or this reports on stale results.\n"
        % (len(_listed) - _missing, len(_listed)))

if mode == "pct":
    path_filter = args[1] if len(args) > 1 else ""
    total = count = 0
    for f, e, a in common.entries(byaddr):
        if path_filter not in f:
            continue
        if e is None:
            print("  --    --  %s %s" % (a, f))
            continue
        m = float(e["matching"])
        total += m
        count += 1
        print("%5.1f %5.1f %s" % (m * 100, common.normalized_ratio(e) * 100, e["name"]))
    if count:
        print("avg %.2f over %d" % (total / count * 100, count))

elif mode == "save":
    snapshot = {e["name"]: [float(e["matching"]), common.normalized_ratio(e)]
                for f, e, a in common.entries(byaddr) if e}
    # A snapshot of a partial run is worse than no snapshot: every function it is missing reads
    # as 0.0 later, so the comparison calls the whole namespace "better" and hides any real
    # regression among the noise. Refuse instead, rather than writing a file that looks fine.
    listed = sum(1 for _ in common.entries(byaddr))
    if listed and len(snapshot) <= listed // 2:
        sys.exit("refusing to save: the last reccmp run covers %d of the %d functions in the "
                 "build list.\nRe-run with --run first." % (len(snapshot), listed))
    json.dump(snapshot, open(args[1], "w"), indent=0)

elif mode == "cmp":
    old = json.load(open(args[1]))
    path_filter = args[2] if len(args) > 2 else ""
    for f, e, a in common.entries(byaddr):
        if not e or path_filter not in f:
            continue
        o = old.get(e["name"], [0, 0])
        m = float(e["matching"])
        tag = "WORSE" if m < o[0] - 1e-9 else ("better" if m > o[0] + 1e-9 else "")
        print("%5.1f->%5.1f  norm %5.1f->%5.1f %-6s %s"
              % (o[0] * 100, m * 100, o[1] * 100, common.normalized_ratio(e) * 100, tag, e["name"]))

elif mode == "diff":
    for f, e, a in common.entries(byaddr):
        if e and any(s in e["name"] for s in args[1:]):
            common.print_diff(e)

else:
    sys.exit(__doc__)
