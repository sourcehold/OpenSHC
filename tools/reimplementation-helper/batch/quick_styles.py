"""Score several source styles of one function with quick_diff.py, in seconds per variant.

This is `try_styles.py` without the build: same variant layout, same table, but each candidate is
compiled with /FA and diffed against the original straight out of `_original/` instead of going
through a link and a reccmp run. A variant costs a few seconds rather than minutes, so trying a
dozen forms of a function becomes a triage loop instead of an afternoon.

Put each complete .cpp in
    build-RelWithDebInfo/batch/variants/<function>/<style>.cpp
then run this. The original file is saved as _original.cpp.bak in that directory before the first
run, so a bad set of variants cannot lose it. The winner is left in the source tree.

usage:
  quick_styles.py FunctionName [-s] [style ...]

`-s` scores with `[esp + N]` offsets kept (quick_diff -s), which is what makes declaration order
and slot assignment visible; use it once everything else matches.

The score is quick_diff's difflib ratio, which is NOT the reccmp percentage: it is stricter about
register names and looser about stack offsets and constants. Use it to rank the forms, then confirm
the winner with `reccmp_report.py --run`. Ties are printed rather than broken for you - prefer the
form that reads best, which the style notes in AGENTS.md ask for anyway.

Do not run this while a build is running: both write the same PDB.
"""

import json
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

import common

BATCH = Path(__file__).resolve().parent
VARIANTS = common.TMP / "variants"
RATIO = re.compile(r"ratio\s+([0-9.]+)")


def measure(target, keep_slots, out_dir):
    env = dict(os.environ)
    env["QD_OUT"] = out_dir
    argv = [sys.executable, str(BATCH / "quick_diff.py"), str(target), "-q"]
    if keep_slots:
        argv.append("-s")
    proc = subprocess.run(argv, capture_output=True, text=True, env=env)
    out = proc.stdout + proc.stderr
    found = RATIO.search(out)
    if not found:
        return None, out
    return float(found.group(1)) * 100, None


def main():
    argv = sys.argv[1:]
    if not argv:
        sys.exit(__doc__)
    func = argv.pop(0)
    keep_slots = "-s" in argv
    styles = [a for a in argv if a != "-s"]

    vdir = VARIANTS / func
    if not vdir.is_dir():
        sys.exit("no variants in %s" % vdir)
    styles = styles or sorted(p.stem for p in vdir.glob("*.cpp") if p.stem != "_original.cpp")

    matches = [p for p in Path("src/OpenSHC").rglob(func + ".cpp")]
    if len(matches) != 1:
        sys.exit("expected exactly one src/OpenSHC/**/%s.cpp, found %d" % (func, len(matches)))
    target = matches[0]

    backup = vdir / "_original.cpp.bak"
    if not backup.exists():
        shutil.copy(target, backup)

    # quick_diff writes <QD_OUT>/x.asm, so keep this run out of the way of a concurrent
    # quick_diff.py or quick_reorder.py
    out_dir = "styles_" + func

    results = []
    try:
        for style in styles:
            shutil.copy(vdir / (style + ".cpp"), target)
            common.format_file(target)
            ratio, err = measure(target, keep_slots, out_dir)
            results.append((ratio, style))
            # four decimals: a variant printing the same first decimal as the baseline has
            # repeatedly turned out to be slightly below it, which is one instruction
            print("%-32s %s" % (style, "COMPILE FAIL" if ratio is None else "%.4f%%" % ratio))
            if err:
                for line in err.splitlines():
                    if "error" in line:
                        print("    " + line.strip()[:160])
    except KeyboardInterrupt:
        shutil.copy(backup, target)
        common.format_file(target)
        sys.exit("\ninterrupted; original restored")

    ranked = sorted((r for r in results if r[0] is not None), reverse=True)
    if not ranked:
        shutil.copy(backup, target)
        common.format_file(target)
        sys.exit("every variant failed to compile; original restored")

    best = ranked[0][0]
    tied = [s for r, s in ranked if abs(r - best) < 1e-9]
    print("\nbest %.4f%% achieved by: %s" % (best, ", ".join(tied)))
    if len(tied) > 1:
        print("(tied -- keeping %s; pick whichever reads best)" % tied[0])
    print("quick_diff ratio, not the reccmp score: confirm with reccmp_report.py --run")

    shutil.copy(vdir / (tied[0] + ".cpp"), target)
    common.format_file(target)
    (vdir / "quick_results.json").write_text(
        json.dumps({s: r for r, s in results if r is not None}, indent=1), encoding="utf-8")


if __name__ == "__main__":
    main()
