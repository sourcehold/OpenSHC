"""Write source variants of one function from a list of text replacements, for quick_styles.py / try_styles.py.

usage:
  make_variants.py FunctionName SPEC.py [--keep]

SPEC.py is Python that defines

    VARIANTS = {
        "flip_mask": [("if ((x & 4) == 0) {", "if ((x & 4) != 0) {"), ...],
        "plain_loop": [(old, new), ...],
    }

Each variant applies its (old, new) pairs in order to the function's current source and is written to
build-RelWithDebInfo/batch/variants/<FunctionName>/<name>.cpp. Every `old` must occur in the text it is
applied to - a missing one skips that variant with a message instead of writing a file that silently lacks
the change. The variant directory is cleared first unless --keep is given (its _original.cpp.bak is kept
either way). Writing the replacements down rather than hand-copying files keeps a dozen variants of a
5000-line function reviewable, and lets a variant be regenerated after the source moves on.
"""

import sys
from pathlib import Path

import common


def main():
    argv = sys.argv[1:]
    if len(argv) < 2:
        sys.exit(__doc__)
    func, spec = argv[0], common.INVOCATION_DIR / argv[1]
    matches = list(Path("src/OpenSHC").rglob(func + ".cpp"))
    if len(matches) != 1:
        sys.exit("expected exactly one src/OpenSHC/**/%s.cpp, found %d" % (func, len(matches)))
    src = common.read_text(matches[0]).replace("\r\n", "\n")
    ns = {}
    exec(compile(common.read_text(spec), str(spec), "exec"), ns)

    out = common.TMP / "variants" / func
    out.mkdir(parents=True, exist_ok=True)
    if "--keep" not in argv:
        for old in out.glob("*.cpp"):
            old.unlink()
    written = 0
    for name, reps in ns["VARIANTS"].items():
        text = src
        for old, new in reps:
            if old not in text:
                print("%s: skipped, not found: %r" % (name, old[:70]))
                break
            text = text.replace(old, new)
        else:
            common.write_text(out / (name + ".cpp"), text)
            written += 1
    print("%d variant(s) in %s" % (written, out))


if __name__ == "__main__":
    main()
