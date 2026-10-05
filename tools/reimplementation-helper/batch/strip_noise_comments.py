"""Remove the block comments above a reimplemented function.

Ghidra prefixes a decompilation with one block comment per analysis complaint, plus the
provenance marker the import writes:

    /*
      WARNING: Enum "MappersEnumInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

Every block comment in the run directly above a `// FUNCTION:` line is deleted, including
blocks holding hand-written notes. Comments inside a body (the string literal annotated
next to a playWAVSFX call, say) and `//` line comments are never touched.

Dry run by default like the other rewriting scripts: read the report, then pass --apply.

usage:
  strip_noise_comments.py [path-filter] [--apply] [--show]
"""

import re
import sys
from pathlib import Path

import common

FUNCTION_LINE = re.compile(r"^\s*//\s*FUNCTION:")
# a whole-line comment opener/closer, so a trailing comment on a line of code is not mistaken for one
OPEN = re.compile(r"^\s*/\*")
CLOSE = re.compile(r"\*/\s*$")


def content_lines(block):
    """The block's text with the /* */ framing and the leading ` * ` decoration stripped."""
    text = "\n".join(block)
    text = text[text.index("/*") + 2:]
    text = text[:text.rindex("*/")]
    out = []
    for line in text.split("\n"):
        line = re.sub(r"^\s*\*(?!/)", "", line).strip()
        if line:
            out.append(line)
    return out


def preceding_blocks(lines, index):
    """Spans (start, end) of the block comments immediately above lines[index], outermost first."""
    spans = []
    j = index - 1
    while j >= 0:
        if not CLOSE.search(lines[j]) or lines[j].strip().startswith("//"):
            break
        k = j
        while k >= 0 and not OPEN.match(lines[k]):
            k -= 1
        if k < 0:
            break
        spans.append((k, j))
        j = k - 1
    spans.reverse()
    return spans


def main():
    path_filter = ""
    apply = False
    show = False
    for arg in sys.argv[1:]:
        if arg == "--apply":
            apply = True
        elif arg == "--show":
            show = True
        else:
            path_filter = arg

    files = sorted(p.as_posix() for p in Path("src/OpenSHC").rglob("*.cpp"))
    removed = touched = 0
    for f in files:
        if path_filter not in f:
            continue
        lines = common.read_text(f).replace("\r\n", "\n").split("\n")
        drop = set()
        n = 0
        for i, line in enumerate(lines):
            if not FUNCTION_LINE.match(line):
                continue
            for start, end in preceding_blocks(lines, i):
                drop.update(range(start, end + 1))
                n += 1
                if show:
                    print("%s:%d | %s" % (f, start + 1,
                                          " / ".join(content_lines(lines[start:end + 1]))[:120]))
        if not n:
            continue
        removed += n
        touched += 1
        print("%-60s -%d" % (f[len("src/OpenSHC/"):], n))
        if apply:
            common.write_text(f, "\n".join(l for i, l in enumerate(lines) if i not in drop))

    print("%d block comment(s) in %d file(s)%s"
          % (removed, touched, "" if apply else " (dry run, pass --apply)"))


main()
