"""Diff the sequence of compare constants between the original and our build.

Every `cmp reg, imm` in the original is a literal from the source. Lining the two
sequences up shows, in one screen per function, which checks we get wrong, which we are
missing entirely and where a block sits in the wrong place -- things that are easy to miss
in a long instruction diff.

    python compare_constants.py                 # every file in the sources list
    python compare_constants.py UpdateMiner Map/Units/UpdateCow.cpp

A `-x / +y` pair that differs by one is an off-by-one literal (`> 31` where the original
wrote `>= 32`); fix_off_by_one.py rewrites those. A lone `-x` means the original tests
something we do not test at all; a run of lines moving together means our blocks are in a
different order than the original's.

Needs a reccmp run first (reccmp_report.py --run ...) so reccmp/dll/diff.json is current.
"""

import difflib
import re
import sys
from pathlib import Path

import common

CONSTANT_RE = re.compile(r"^(cmp|test) (?:byte|word|dword)? ?(?:ptr )?(?:\[[^\]]*\]|\w+), (0x[0-9a-f]+|\d+)$")
SOURCE_LINE_RE = re.compile(r"\((\w+)\.cpp:(\d+)\)")
# 0 and 1 are mostly `test eax, eax` and flag checks: too common to carry information
IGNORED = (0, 1)


def constants(entry):
    """Constants compared against in the original and in our build.

    Returns (original, ours, lines): parallel to `ours`, `lines` holds the source line the
    instruction was attributed to (or None).
    """
    original, ours, lines = [], [], []
    current_line = None
    for hunk in entry.get("diff") or []:
        for block in hunk[1]:
            for kind, rows in block.items():
                for row in rows:
                    parts = row[1].split("\t")
                    if kind in ("both", "recomp") and len(parts) > 1:
                        m = SOURCE_LINE_RE.search(parts[1])
                        if m:
                            current_line = int(m.group(2))
                    m = CONSTANT_RE.match(parts[0].strip())
                    if not m:
                        continue
                    value = int(m.group(2), 0)
                    if value in IGNORED:
                        continue
                    token = "%s %#x" % (m.group(1), value)
                    if kind in ("both", "orig"):
                        original.append(token)
                    if kind in ("both", "recomp"):
                        ours.append(token)
                        lines.append(current_line)
    return original, ours, lines


def select(names):
    """The sources list, filtered by function name or path substring."""
    files = common.list_files()
    if not names:
        return files
    chosen = [f for f in files if any(n in f or Path(f).stem == n for n in names)]
    if not chosen:
        sys.exit("no file in %s matches %s" % (common.SOURCES_LIST, names))
    return chosen


def main():
    names = [a for a in sys.argv[1:] if not a.startswith("--")]
    byaddr = common.load_diff()
    for _, entry, address in common.entries(byaddr, select(names)):
        if entry is None:
            continue
        original, ours, _ = constants(entry)
        print("### %s %.1f%%" % (entry["name"], float(entry["matching"]) * 100))
        for line in difflib.unified_diff(original, ours, n=1, lineterm=""):
            if not line.startswith(("---", "+++")):
                print("   ", line)


if __name__ == "__main__":
    main()
