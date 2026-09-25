"""Commit progress for every changed list file (one commit per function), like commit_progress.

usage: commit_progress_batch.py PREFIX... [FunctionName=remark ...] [--dry-run]

PREFIX is relative to src/OpenSHC (e.g. "Map/" or "UI/Helpers"). Only files that
differ from HEAD (or are untracked) are committed. Uses the current
reccmp/dll/diff.json, so run reccmp first (reccmp_report.py --run pct).

Progress: 100% "Reimplemented" when the function matches or only call targets
differ (normalized 100%), otherwise the reccmp % with the given remark
(max 30 chars, default "Style pass, asm differs").

Uses tools/reimplementation-helper/setstatusandcommit.py when present (on main);
otherwise the same status-file update + commit is done here.
"""

import re
import subprocess
import sys
from pathlib import Path

import common

STATUS_FILE = Path("status/addresses-SHC-3BB0A8C1.txt")
HELPER = Path("tools/reimplementation-helper/setstatusandcommit.py")

remarks, prefixes = {}, []
dry_run = "--dry-run" in sys.argv
for arg in sys.argv[1:]:
    if arg == "--dry-run":
        continue
    if "=" in arg:
        key, value = arg.split("=", 1)
        remarks[key] = value[:30]
    else:
        prefixes.append(arg)
if not prefixes:
    sys.exit(__doc__)


def git(*args):
    return subprocess.run(["git"] + list(args), capture_output=True, text=True)


def commit(cpp, address, percent, remark):
    if HELPER.exists():
        r = subprocess.run([sys.executable, str(HELPER), cpp, "%.2f%%" % percent, remark],
                           capture_output=True, text=True)
        return r.returncode == 0, r.stdout[-200:] + r.stderr[-300:]
    lines = STATUS_FILE.read_text(encoding="utf-8").splitlines(True)
    function_id = None
    for i, line in enumerate(lines):
        m = re.match(r"^(\S+_(0x[0-9A-Fa-f]+))\s*\|", line)
        if m and m.group(2).lower() == address.lower():
            function_id = m.group(1)
            lines[i] = "%s | %.1f%% | %s\n" % (function_id, percent, remark)
    if function_id is None:
        return False, "address %s not in %s (wrong FUNCTION address?)" % (address, STATUS_FILE)
    STATUS_FILE.write_text("".join(lines), encoding="utf-8", newline="")
    git("add", cpp, str(STATUS_FILE))
    r = git("commit", "-m", "reimplement: %s %.2f%% %s" % (function_id, percent, remark))
    return r.returncode == 0, r.stdout[-200:] + r.stderr[-300:]


changed = set(git("diff", "--name-only", "HEAD").stdout.split())
changed |= set(git("ls-files", "--others", "--exclude-standard").stdout.split())
for f, e, address in common.entries(common.load_diff()):
    if f not in changed or not any(f.startswith("src/OpenSHC/" + p) for p in prefixes):
        continue
    if e is None:
        print("  SKIP (no reccmp entry)       %s" % f)
        continue
    name = e["name"].split("::")[-1]
    matching = float(e["matching"])
    if matching >= 1 or common.normalized_ratio(e) >= 1:
        percent, remark = 100.0, "Reimplemented"
    else:
        percent, remark = round(matching * 100, 2), remarks.get(name, "Style pass, asm differs")
    ok, output = (True, "") if dry_run else commit(f, address, percent, remark)
    print("%6.2f %-30s %s %s" % (percent, remark, name, "" if ok else "FAIL " + output))
