#!/usr/bin/env python3
"""
Usage:
    python setstatus.py src/path/to/file.cpp "90%" "Reimplemented, missing info"

Updates the matching line in the status file, git-adds the cpp and status
file, and commits with:
    reimplement: <FUNCTION_ID> <percent> <status>
"""

import argparse
import re
import subprocess
import sys
from pathlib import Path

# Adjust this to wherever your status file lives (relative to the repo root / cwd)
DEFAULT_STATUS_FILE = "status/addresses-SHC-3BB0A8C1.txt"

FUNCTION_MARKER_RE = re.compile(r"//\s*FUNCTION:\s*\S+\s+(0x[0-9A-Fa-f]+)")
STATUS_LINE_RE = re.compile(r"^(?P<id>\S+_(?P<addr>0x[0-9A-Fa-f]+))\s*\|")


def parse_percent(text: str) -> tuple[str, str]:
    """Return (value as written for the status file, value as written for the commit)."""
    cleaned = text.strip().rstrip("%").strip()
    try:
        value = float(cleaned)
    except ValueError:
        sys.exit(f"error: invalid percentage '{text}'")
    if not 0 <= value <= 100:
        sys.exit(f"error: percentage out of range: {value}")
    return f"{value:.1f}%", f"{cleaned}%"


def find_address(cpp_path: Path) -> str:
    content = cpp_path.read_text(encoding="utf-8", errors="replace")
    matches = FUNCTION_MARKER_RE.findall(content)
    if not matches:
        sys.exit(f"error: no '// FUNCTION: ... 0x...' marker found in {cpp_path}")
    unique = list(dict.fromkeys(m.lower() for m in matches))
    if len(unique) > 1:
        sys.exit(f"error: multiple FUNCTION markers in {cpp_path}: {', '.join(unique)}")
    return unique[0]


def update_status_file(status_path: Path, address: str,
                       percent: str, status: str) -> str:
    lines = status_path.read_text(encoding="utf-8").splitlines(keepends=True)
    function_id = None

    for i, line in enumerate(lines):
        m = STATUS_LINE_RE.match(line)
        if m and m.group("addr").lower() == address:
            if function_id is not None:
                sys.exit(f"error: address {address} appears more than once in {status_path}")
            function_id = m.group("id")
            newline = "\n"
            lines[i] = f"{function_id} | {percent} | {status}{newline}"

    if function_id is None:
        sys.exit(f"error: address {address} not found in {status_path}")

    status_path.write_text("".join(lines), encoding="utf-8", newline="")
    return function_id


def run_git(*args: str) -> None:
    result = subprocess.run(["git", *args])
    if result.returncode != 0:
        sys.exit(f"error: 'git {' '.join(args)}' failed")


def main() -> None:
    parser = argparse.ArgumentParser(description="Set reimplementation status and commit.")
    parser.add_argument("cpp", type=Path, help="path to the cpp file")
    parser.add_argument("percent", help='completion percentage, e.g. "90%%"')
    parser.add_argument("status", help='status text, e.g. "Reimplemented, missing info"')
    parser.add_argument("--status-file", type=Path, default=Path(DEFAULT_STATUS_FILE),
                        help=f"path to the status file (default: {DEFAULT_STATUS_FILE})")
    parser.add_argument("--no-commit", action="store_true",
                        help="only update the status file, skip git add/commit")
    args = parser.parse_args()

    if not args.cpp.is_file():
        sys.exit(f"error: cpp file not found: {args.cpp}")
    if not args.status_file.is_file():
        sys.exit(f"error: status file not found: {args.status_file}")

    status_percent, commit_percent = parse_percent(args.percent)
    status_text = args.status.strip()

    address = find_address(args.cpp)
    function_id = update_status_file(args.status_file, address, status_percent, status_text)
    print(f"Updated {function_id} -> {status_percent} | {status_text}")

    if args.no_commit:
        return

    run_git("add", str(args.cpp), str(args.status_file))
    run_git("commit", "-m", f"reimplement: {function_id} {commit_percent} {status_text}")


if __name__ == "__main__":
    main()