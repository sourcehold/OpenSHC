"""Build OpenSHC.dll and print only compiler errors (full log: build-RelWithDebInfo/batch/build.log).

usage: build_quiet.py [--keep-going] [--max N]

Prints BUILD_OK or BUILD_FAIL as the last line. build.bat exits 0 even on
compile errors, so the log is scanned instead of trusting the exit code.
--keep-going reruns the build with nmake /K to collect errors from more files.

The build runs with this worktree's own _MSPDBSRV_ENDPOINT_ (see common.build_env), which is what
build.bat does too; --keep-going bypasses build.bat and would otherwise inherit whatever endpoint
happens to be set. A build that dies with C1090/C1033 gets two retries, because that error has two
different causes:

  1. a wedged PDB server, which survives the kill build.bat does up front -> stop this worktree's
     mspdbsrv.exe and build again;
  2. a wedged *endpoint*, which outlives every mspdbsrv.exe using it -> build again on a fresh
     endpoint name, since retrying into the same name fails forever.

The second cost six consecutive builds once, across a regenerated PCH and PDBs, while the same tree
built first try under a different endpoint name.

A build that fails without naming any source line gets one more plain retry. cmake's glob
verification dies with an access violation ("Access violation" + U1077 return code 0xffffffff) on the
first build after cmake/openshc-sources.txt.local changes, which is every first build of a new
selection; the reconfigure crashed, not the compile, and a plain re-run succeeds.
"""

import argparse
import re
import subprocess
import sys

from common import PDB_ERROR_RE, TMP, build_env, fresh_pdb_endpoint, kill_pdb_server

parser = argparse.ArgumentParser()
parser.add_argument("--keep-going", action="store_true")
parser.add_argument("--max", type=int, default=60)
args = parser.parse_args()

log = TMP / "build.log"


def run_build(endpoint=None):
    with open(log, "w") as out:
        subprocess.run(["cmd", "/c", r".\build.bat RelWithDebInfo OpenSHC.dll"],
                       stdout=out, stderr=subprocess.STDOUT, env=build_env(endpoint))
    if args.keep_going:
        with open(log, "w") as out:
            subprocess.run(["cmd", "/c", r".\cmakew --build --preset RelWithDebInfo --target OpenSHC.dll -- /K"],
                           stdout=out, stderr=subprocess.STDOUT, env=build_env(endpoint))
    return log.read_text(errors="replace")


text = run_build()
if PDB_ERROR_RE.search(text):
    print("note: PDB server error, stopping this worktree's mspdbsrv.exe and retrying", file=sys.stderr)
    kill_pdb_server()
    text = run_build()
if PDB_ERROR_RE.search(text):
    # The endpoint itself can be wedged, in which case it outlives every mspdbsrv.exe using it and
    # retrying into the same name fails forever. Move to a fresh one.
    endpoint = fresh_pdb_endpoint()
    print("note: PDB endpoint still failing, retrying on a fresh endpoint %s" % endpoint,
          file=sys.stderr)
    kill_pdb_server()
    text = run_build(endpoint)

def compile_errors(text):
    return [line for line in text.splitlines()
            if re.search(r" error |warning C4700|warning C4715", line) and "U1077" not in line]


def failing(text):
    return bool(re.search(r" error |U1077", text))


if failing(text) and not compile_errors(text):
    # Nothing named a source line, so the compile is not what failed: cmake's glob verification
    # crashed during the reconfigure. It succeeds on a plain re-run.
    print("note: build failed without a compiler error, retrying once", file=sys.stderr)
    text = run_build()

errors = compile_errors(text)
for line in errors[:args.max]:
    print(re.sub(r"^.*src.OpenSHC.", "", line))
failed = failing(text)
print("BUILD_FAIL" if failed else "BUILD_OK")
# exit non-zero so `build_quiet.py && reccmp_report.py ...` stops here: a failed build
# leaves the previous DLL in place and reccmp would happily report on the old code
raise SystemExit(1 if failed else 0)
