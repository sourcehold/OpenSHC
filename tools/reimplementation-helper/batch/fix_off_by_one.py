"""Rewrite comparisons to the literal the original actually compares against.

`if (x > 31)` and `if (x >= 32)` mean the same thing but compile to `cmp x, 0x1f` and
`cmp x, 0x20`. Matching the original's literal costs nothing and removes the difference,
so this pairs up compare constants that are one apart and rewrites ours:

    > n   -> >= n+1        >= n   -> > n-1
    <= n  -> < n+1         <  n   -> <= n-1

    python fix_off_by_one.py                    # report on every file in the sources list
    python fix_off_by_one.py --apply Map/Units

Without --apply nothing is written; each line is printed as `before  ->  after`. A pair it
cannot place in the source is reported as NO MATCH (usually the literal is spelled
differently, e.g. hex, or the expression was folded); fix those by hand.

This is not always an improvement: the register allocator sometimes keeps the old literal
in a register and reuses it. Always rebuild and compare, and revert the functions that got
worse (reccmp_report.py cmp BASE.json).
"""

import difflib
import re
import sys

import common
import compare_constants

# how far from the attributed line to look for the comparison
WINDOW = 4


def pairs(original, ours, lines):
    """Constant pairs that differ by exactly one, with the source line of ours."""
    matcher = difflib.SequenceMatcher(None, original, ours, autojunk=False)
    blocks = [op for op in matcher.get_opcodes() if op[0] != "equal"]
    # join blocks separated by a couple of equal constants: the pair is often split up
    merged = []
    for block in blocks:
        if merged and block[1] - merged[-1][2] <= 3 and block[3] - merged[-1][4] <= 3:
            previous = merged[-1]
            merged[-1] = ("replace", previous[1], block[2], previous[3], block[4])
        else:
            merged.append(block)
    found, used = [], set()
    for _, i1, i2, j1, j2 in merged:
        for i in range(i1, i2):
            for j in range(j1, j2):
                if j in used:
                    continue
                a, b = int(original[i].split()[1], 0), int(ours[j].split()[1], 0)
                if abs(a - b) == 1:
                    used.add(j)
                    found.append((a, b, lines[j]))
                    break
    return found


def rewrite(source, line, wanted, ours):
    """Rewrite the comparison against `ours` near `line` to use `wanted`. Returns True if done."""
    if line is None:
        return False
    for index in range(max(0, line - 2), min(line + WINDOW, len(source))):
        for literal in (str(ours), hex(ours)):
            if wanted == ours + 1:
                rules = [(r"> %s\b" % literal, ">= %d" % wanted), (r"<= %s\b" % literal, "< %d" % wanted)]
            else:
                rules = [(r">= %s\b" % literal, "> %d" % wanted), (r"< %s\b" % literal, "<= %d" % wanted)]
            for pattern, replacement in rules:
                if re.search(pattern, source[index]):
                    new = re.sub(pattern, replacement, source[index], count=1)
                    print("    %s  ->  %s" % (source[index].strip(), new.strip()))
                    source[index] = new
                    return True
    return False


def main():
    apply = "--apply" in sys.argv
    names = [a for a in sys.argv[1:] if not a.startswith("--")]
    byaddr = common.load_diff()
    for path, entry, _ in common.entries(byaddr, compare_constants.select(names)):
        if entry is None:
            continue
        found = pairs(*compare_constants.constants(entry))
        if not found:
            continue
        source = common.read_text(path).split("\n")
        print("###", entry["name"])
        changed = False
        for wanted, ours, line in found:
            if rewrite(source, line, wanted, ours):
                changed = True
            else:
                print("    %s:%s NO MATCH: original %#x, ours %#x" % (path, line, wanted, ours))
        if apply and changed:
            common.write_text(path, "\n".join(source))
            common.format_file(path)


if __name__ == "__main__":
    main()
