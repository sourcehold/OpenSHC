#!/usr/bin/env python3
"""
Usage:
    python set_sources_from_incomplete_status.py [--base main] [--destination FILE]

Takes the functions this branch touched but did not finish - the lines added to
the status file relative to the base branch whose status is neither 100% nor
0.0% - and writes the .cpp files implementing them to
cmake/openshc-sources.txt.local. Run from the repository root.
"""

import argparse
import re
import subprocess
import sys
from pathlib import Path

DEFAULT_STATUS_FILE = "status/addresses-SHC-3BB0A8C1.txt"
DEFAULT_SOURCE_ROOT = "src/OpenSHC"
DEFAULT_DESTINATION = "cmake/openshc-sources.txt.local"

FUNCTION_MARKER_RE = re.compile(r"//\s*FUNCTION:\s*\S+\s+0x([0-9A-Fa-f]+)")
STATUS_LINE_RE = re.compile(r"^SHC_[0-9A-Fa-f]+_0x([0-9A-Fa-f]+)")


def incomplete_status_lines(base: str, status_file: str) -> list[str]:
    diff = subprocess.run(
        ["git", "diff", base, "HEAD", "--", status_file],
        check=True,
        capture_output=True,
        text=True,
        encoding="utf-8",
    ).stdout
    return [
        line[1:]
        for line in diff.splitlines()
        if line.startswith("+SHC") and "| 100" not in line and "| 0.0%" not in line
    ]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--base", default="main")
    parser.add_argument("--status-file", default=DEFAULT_STATUS_FILE)
    parser.add_argument("--source-root", default=DEFAULT_SOURCE_ROOT)
    parser.add_argument("--destination", default=DEFAULT_DESTINATION)
    args = parser.parse_args()

    # address -> status line
    wanted = {}
    for line in incomplete_status_lines(args.base, args.status_file):
        match = STATUS_LINE_RE.match(line)
        if match:
            wanted[match.group(1).upper()] = line

    # A single .cpp can hold several // FUNCTION: lines, so every match in every file is checked.
    files = set()
    found = set()
    for path in Path(args.source_root).rglob("*.cpp"):
        text = path.read_text(encoding="utf-8", errors="replace")
        addresses = {address.upper() for address in FUNCTION_MARKER_RE.findall(text)} & wanted.keys()
        if addresses:
            found |= addresses
            files.add(path.as_posix())

    for address in sorted(wanted.keys() - found):
        print(f"warning: no .cpp found for: {wanted[address]}", file=sys.stderr)

    with open(args.destination, "w", encoding="utf-8", newline="\n") as handle:
        handle.writelines(f"{name}\n" for name in sorted(files))

    print(f"{len(wanted)} incomplete functions -> {len(files)} files written to {args.destination}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
