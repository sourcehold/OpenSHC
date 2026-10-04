"""Fast syntax check (cl /Zs) of list files without a full build or link.

usage: syntax_check.py [path-substring...]   (default: every file in cmake/openshc-sources.txt.local)

Needs build-RelWithDebInfo/compile_commands.json from a previous configure. Files
are checked serially: runs sharing the PCH/pdb in parallel give bogus errors.

cl.exe runs with this worktree's own _MSPDBSRV_ENDPOINT_ (see common.build_env). A run that dies
with C1090/C1033 gets the same two retries build_quiet.py takes - stop this worktree's mspdbsrv.exe,
then move to a fresh endpoint name. A PDB error matters more here than in a build: it is counted as
an error against whichever file happened to hit it, and the files after it in the batch are still
checked, so the run reports a plausible-looking error list that hides the real compile errors.
"""

import json
import os
import re
import subprocess
import sys

from common import (BUILD_DIR, PDB_ERROR_RE, ROOT, TMP, build_env, fresh_pdb_endpoint,
                    kill_pdb_server, list_files)

commands = json.loads((BUILD_DIR / "compile_commands.json").read_text())
template = next(c["command"] for c in commands if "OpenSHC.dll.dir" in c["command"])
template_source = template.split(" -c ")[-1].strip()

files = list_files()
if sys.argv[1:]:
    files = [f for f in files if any(s in f for s in sys.argv[1:])]

lines = ["@echo off",
         r"call %s\MSVC1400-SP1\vsvars32-portable.bat >nul" % ROOT,
         r"cd /d %s" % (ROOT / BUILD_DIR)]
for f in files:
    lines.append(re.sub(r"/Fo\S+", "/Zs", template.replace(template_source, os.path.abspath(f))))
bat = TMP / "syntax_check.bat"
bat.write_text("\n".join(lines) + "\n")


def run_check(endpoint=None):
    result = subprocess.run(["cmd", "/c", str(bat.resolve())], capture_output=True, text=True,
                            env=build_env(endpoint))
    return result.stdout + result.stderr


output = run_check()
if PDB_ERROR_RE.search(output):
    print("note: PDB server error, stopping this worktree's mspdbsrv.exe and retrying", file=sys.stderr)
    kill_pdb_server()
    output = run_check()
if PDB_ERROR_RE.search(output):
    endpoint = fresh_pdb_endpoint()
    print("note: PDB endpoint still failing, retrying on a fresh endpoint %s" % endpoint, file=sys.stderr)
    kill_pdb_server()
    output = run_check(endpoint)

errors = [l for l in output.splitlines() if " error " in l or "fatal" in l]
for line in errors:
    print(re.sub(r"^.*src.OpenSHC.", "", line)[:260])
print("ERRORS", len(errors), "files", len(files))
