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
    run(BATCH / "reccmp_report.py", "--run", "pct")
    # Read the ratio out of diff.json rather than parsing the printed percentage: that is
    # formatted to one decimal, so every variant sharing a first decimal compared as an
    # exact tie. One such "tie" was really 0.02 points below the baseline.
    for entry in common.load_diff().values():
        if entry["name"].endswith("::" + func):
            return float(entry["matching"]) * 100, None
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

    # narrow the build list to this one function so each variant builds in seconds, and
    # put it back afterwards -- every other batch tool reads it to decide what to report on
    saved_list = common.read_text(common.SOURCES_LIST)
    common.write_text(common.SOURCES_LIST, target.as_posix() + "\n")
    try:
        results = []
        for style in styles:
            shutil.copy(vdir / (style + ".cpp"), target)
            common.format_file(target)
            pct, err = measure(func)
            results.append((pct, style))
            # four decimals, because two hid a real regression behind an apparent tie: a
            # variant that printed the same "29.20%" as the baseline was actually 0.02
            # points below it, which is one instruction in a large function
            print("%-32s %s" % (style, "BUILD FAIL" if pct is None else "%.4f%%" % pct))
            if err:
                for line in err.splitlines():
                    if "error" in line:
                        print("    " + line.strip()[:160])
    finally:
        common.write_text(common.SOURCES_LIST, saved_list)

    ranked = sorted((r for r in results if r[0] is not None), reverse=True)
    if not ranked:
        shutil.copy(backup, target)
        sys.exit("every variant failed to build; original restored")
    best = ranked[0][0]
    tied = [s for p, s in ranked if abs(p - best) < 1e-9]
    print("\nbest %.4f%% achieved by: %s" % (best, ", ".join(tied)))
    if len(tied) > 1:
        print("(tied -- keeping %s; pick whichever reads best)" % tied[0])
    shutil.copy(vdir / (tied[0] + ".cpp"), target)
    common.format_file(target)
    (vdir / "results.json").write_text(
        json.dumps({s: p for p, s in results if p is not None}, indent=1), encoding="utf-8")

    # The trials left the DLL and reccmp/dll/diff.json built from the narrowed list, so every
    # batch tool would go on reporting the last variant's single-function result. Restoring
    # the list is not enough -- rebuild so the tree, the DLL and the diff agree again.
    print("\nrebuilding with the full list so later reports are valid...")
    print(run(BATCH / "build_quiet.py").strip().splitlines()[-1])


if __name__ == "__main__":
    main()
