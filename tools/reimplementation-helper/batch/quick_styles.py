"""Score several source styles of one function with quick_diff.py, in seconds per variant.

This is `try_styles.py` without the build: same variant layout, same table, but each candidate is
compiled with /FA and diffed against the original straight out of `_original/` instead of going
through a link and a reccmp run. A variant costs a few seconds rather than minutes, so trying a
dozen forms of a function becomes a triage loop instead of an afternoon.

Put each complete .cpp in
    build-RelWithDebInfo/batch/variants/<function>/<style>.cpp
(`make_variants.py` writes them from a list of text replacements), then run this. The original
file is saved as _original.cpp.bak in that directory before the first run, so a bad set of
variants cannot lose it. The winner is left in the source tree.

usage:
  quick_styles.py FunctionName [-s] [--rank exact|reg|fine] [style ...]

`-s` scores with `[esp + N]` offsets kept (quick_diff -s), which is what makes declaration order
and slot assignment visible; use it once everything else matches.

Three scores are printed per variant, and the source as it stands is scored first as `(current)`:

  exact  quick_diff's ratio, the default ranking
  reg    the same with every register replaced by R (quick_diff -r): the structural part, which is
         what moves first while a large function's blocks are still out of order
  fine   the instructions that are equal including registers, among those `reg` aligned

On a large, badly matching function `exact` can fall while reccmp rises, because difflib rewards a
different alignment; rank by `reg` or `fine` there (`--rank`). A variant whose code is instruction
for instruction the same as an earlier row is marked `= that row`, which is how to prove that a
readability rewrite changed nothing - a tie on the score alone does not.

The scores are NOT the reccmp percentage: they are stricter about register names and looser about
stack offsets and constants. Use them to rank the forms, then confirm the winner with
`reccmp_report.py --run`. Ties are printed rather than broken for you - prefer the form that reads
best, which the style notes in AGENTS.md ask for anyway.

Do not run this while a build is running: both write the same PDB.
"""

import difflib
import json
import os
import shutil
import sys
from pathlib import Path

import common

VARIANTS = common.TMP / "variants"
RANKS = ("exact", "reg", "fine")


def scores(a, b):
    """(exact, reg, fine) in percent for the original stream a against ours b."""
    import quick_diff
    exact = difflib.SequenceMatcher(None, a, b, autojunk=False).ratio()
    ca, cb = quick_diff.register_canon(a), quick_diff.register_canon(b)
    sm = difflib.SequenceMatcher(None, ca, cb, autojunk=False)
    fine = sum(1 for blk in sm.get_matching_blocks() for k in range(blk.size) if a[blk.a + k] == b[blk.b + k])
    return exact * 100, sm.ratio() * 100, 200.0 * fine / (len(a) + len(b))


def measure(target, keep_slots):
    """(scores, our stream), or (None, None) when the file does not compile (quick_diff prints the errors)."""
    import quick_diff
    quick_diff.keep_slots = keep_slots
    a, b = quick_diff.streams(os.path.abspath(str(target)))
    if b is None:
        return None, None
    return scores(a, b), b


def main():
    argv = sys.argv[1:]
    if not argv:
        sys.exit(__doc__)
    func = argv.pop(0)
    keep_slots = "-s" in argv
    rank = 0
    if "--rank" in argv:
        k = argv.index("--rank")
        rank = RANKS.index(argv[k + 1])
        del argv[k:k + 2]
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
    # quick_diff.py or quick_reorder.py; it reads QD_OUT when it is first imported
    os.environ["QD_OUT"] = "styles_" + func

    results = []
    seen = []

    def report(style, sc, stream):
        if sc is None:
            print("%-32s COMPILE FAIL" % style)
            return
        same = [name for name, other in seen if other == stream]
        seen.append((style, stream))
        # four decimals: a variant printing the same first decimal as the baseline has
        # repeatedly turned out to be slightly below it, which is one instruction
        print("%-32s exact %.4f%%  reg %.4f%%  fine %.4f%%%s"
              % (style, sc[0], sc[1], sc[2], "  = " + same[0] if same else ""))

    current = common.read_text(target)
    try:
        report("(current)", *measure(target, keep_slots))
        for style in styles:
            shutil.copy(vdir / (style + ".cpp"), target)
            common.format_file(target)
            sc, stream = measure(target, keep_slots)
            results.append((None if sc is None else sc[rank], style))
            report(style, sc, stream)
    except KeyboardInterrupt:
        common.write_text(target, current)
        sys.exit("\ninterrupted; source restored")

    ranked = sorted((r for r in results if r[0] is not None), reverse=True)
    if not ranked:
        common.write_text(target, current)
        sys.exit("every variant failed to compile; the source is unchanged")

    best = ranked[0][0]
    tied = [s for r, s in ranked if abs(r - best) < 1e-9]
    print("\nbest %s %.4f%% achieved by: %s" % (RANKS[rank], best, ", ".join(tied)))
    if len(tied) > 1:
        print("(tied -- keeping %s; pick whichever reads best)" % tied[0])
    print("quick_diff scores, not the reccmp percentage: confirm with reccmp_report.py --run")

    shutil.copy(vdir / (tied[0] + ".cpp"), target)
    common.format_file(target)
    (vdir / "quick_results.json").write_text(
        json.dumps({s: r for r, s in results if r is not None}, indent=1), encoding="utf-8")


if __name__ == "__main__":
    main()
