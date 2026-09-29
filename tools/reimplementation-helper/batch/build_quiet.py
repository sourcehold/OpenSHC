"""Build OpenSHC.dll and print only compiler errors (full log: build-RelWithDebInfo/batch/build.log).

usage: build_quiet.py [--keep-going] [--max N]

Prints BUILD_OK or BUILD_FAIL as the last line. build.bat exits 0 even on
compile errors, so the log is scanned instead of trusting the exit code.
--keep-going reruns the build with nmake /K to collect errors from more files.

The build runs with this worktree's own _MSPDBSRV_ENDPOINT_ (see common.build_env), which is what
build.bat does too; --keep-going bypasses build.bat and would otherwise inherit whatever endpoint
happens to be set. A build that still dies with C1090/C1033 gets one retry after stopping this
worktree's mspdbsrv.exe, because a wedged PDB server survives the kill build.bat does up front.
"""

import argparse
import re
import subprocess
import sys

from common import PDB_ERROR_RE, TMP, build_env, kill_pdb_server

parser = argparse.ArgumentParser()
parser.add_argument("--keep-going", action="store_true")
parser.add_argument("--max", type=int, default=60)
args = parser.parse_args()

log = TMP / "build.log"


def run_build():
    with open(log, "w") as out:
        subprocess.run(["cmd", "/c", r".\build.bat RelWithDebInfo OpenSHC.dll"],
                       stdout=out, stderr=subprocess.STDOUT, env=build_env())
    if args.keep_going:
        with open(log, "w") as out:
            subprocess.run(["cmd", "/c", r".\cmakew --build --preset RelWithDebInfo --target OpenSHC.dll -- /K"],
                           stdout=out, stderr=subprocess.STDOUT, env=build_env())
    return log.read_text(errors="replace")


text = run_build()
if PDB_ERROR_RE.search(text):
    print("note: PDB server error, stopping this worktree's mspdbsrv.exe and retrying", file=sys.stderr)
    kill_pdb_server()
    text = run_build()

errors = [line for line in text.splitlines()
          if re.search(r" error |warning C4700|warning C4715", line) and "U1077" not in line]
for line in errors[:args.max]:
    print(re.sub(r"^.*src.OpenSHC.", "", line))
print("BUILD_FAIL" if re.search(r" error |U1077", text) else "BUILD_OK")
