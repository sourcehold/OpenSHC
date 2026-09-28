"""Build and measure several source styles of one function, then keep the best.

Whether a given style matches better is not predictable: naming a repeatedly read field
gained 18% in one function and lost 12% in another, and reusing a pointer for two rows
helped one function and hurt its near-identical neighbour. So write the candidates out and
measure them instead of arguing about them.

Put each complete .cpp in
    build-RelWithDebInfo/batch/variants/<function>/<style>.cpp
then run this. It compiles them one at a time with the build list set to just that
function, records the match, restores the winner and prints the table. Ties are left for
you to break on readability, which is why every variant is printed.

The original file is saved as _original.cpp.bak in the same directory before the first
run, so a bad set of variants cannot lose it.

usage:
  try_styles.py FunctionName [style ...]
"""

import json
import shutil
import subprocess
import sys
from pathlib import Path

import common

BATCH = Path(__file__).resolve().parent
VARIANTS = common.TMP / "variants"


def run(*args):
    return subprocess.run([sys.executable] + [str(a) for a in args],
                          capture_output=True, text=True).stdout


def measure(func):
    out = run(BATCH / "build_quiet.py")
    if "BUILD_FAIL" in out and "C1090" in out:
        # mspdbsrv occasionally dies mid-build; that is not the variant's fault
        subprocess.run(["taskkill", "/F", "/IM", "mspdbsrv.exe"], capture_output=True)
        out = run(BATCH / "build_quiet.py")
    if "BUILD_FAIL" in out:
        return None, out
    for line in run(BATCH / "reccmp_report.py", "--run", "pct").splitlines():
        if line.strip().endswith("::" + func):
            return float(line.split()[0]), None
    return None, "function not found in the reccmp report"


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    func = sys.argv[1]
    vdir = VARIANTS / func
    if not vdir.is_dir():
        sys.exit("no variants in %s" % vdir)
    styles = sys.argv[2:] or sorted(p.stem for p in vdir.glob("*.cpp"))

    matches = [p for p in Path("src/OpenSHC").rglob(func + ".cpp")]
    if len(matches) != 1:
        sys.exit("expected exactly one src/OpenSHC/**/%s.cpp, found %d" % (func, len(matches)))
    target = matches[0]

    backup = vdir / "_original.cpp.bak"
    if not backup.exists():
        shutil.copy(target, backup)
    common.write_text(common.SOURCES_LIST, target.as_posix() + "\n")

    results = []
    for style in styles:
        shutil.copy(vdir / (style + ".cpp"), target)
        common.format_file(target)
        pct, err = measure(func)
        results.append((pct, style))
        print("%-32s %s" % (style, "BUILD FAIL" if pct is None else "%.2f%%" % pct))
        if err:
            for line in err.splitlines():
                if "error" in line:
                    print("    " + line.strip()[:160])

    ranked = sorted((r for r in results if r[0] is not None), reverse=True)
    if not ranked:
        shutil.copy(backup, target)
        sys.exit("every variant failed to build; original restored")
    best = ranked[0][0]
    tied = [s for p, s in ranked if abs(p - best) < 1e-9]
    print("\nbest %.2f%% achieved by: %s" % (best, ", ".join(tied)))
    if len(tied) > 1:
        print("(tied -- keeping %s; pick whichever reads best)" % tied[0])
    shutil.copy(vdir / (tied[0] + ".cpp"), target)
    common.format_file(target)
    (vdir / "results.json").write_text(
        json.dumps({s: p for p, s in results if p is not None}, indent=1), encoding="utf-8")


if __name__ == "__main__":
    main()
