"""Fast syntax check (cl /Zs) of list files without a full build or link.

usage: syntax_check.py [-j N] [path-substring...]   (default: every file in cmake/openshc-sources.txt.local)

Checks run -j at a time (default: one per core). On four cores, 20 files of
AI/AICState went from 141s to 47s, and the error list is identical either way. A /Zs
check is far cheaper than compiling: the same 20 files take 676s to compile at -j 4, so
this stays the quick way to find compile errors across a wide edit.

Parallel runs used to be ruled out here because they shared the PCH and the pdb and gave
bogus errors. The pdb half of that is now gone rather than managed: /Zs writes no object,
so it has no need of debug info, and the command drops the /Zi and /Fd that pointed every
cl.exe at one vcNN.pdb. Nothing mutable is then shared - the PCH is only read - and the
checks are independent processes. Dropping /Zi also makes each check slightly faster.

The template comes from a *source* file's command line, which uses /Yu to read the
precompiled header. Picking the first entry for the target instead lands on the PCH's own
command, which carries /Yc and tells every check to *create* the header; with /Zs nothing
is written so it mostly got away with it, but it is the wrong command, it stops the real
PCH from being reused, and when cl then fails partway (a bad /Fd path, say) it can leave
the build's cmake_pch.cxx.pch truncated or deleted, which costs a full rebuild afterwards.

Needs build-RelWithDebInfo/compile_commands.json from a previous configure.

cl.exe runs with this worktree's own _MSPDBSRV_ENDPOINT_ (see common.build_env). The two
C1090/C1033 retries build_quiet.py takes are kept, because a PDB failure here is not just a
lost run - the fatal line counts as an error against whichever file happened to hit it, and
the files after it are still checked, so the run reports a plausible-looking error list that
hides the real compile errors. With /Fd gone there should be no PDB to fail on, but the
retries cost nothing when they do not fire.
"""

import argparse
import json
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

from common import (BUILD_DIR, PDB_ERROR_RE, ROOT, TMP, build_env, fresh_pdb_endpoint,
                    kill_pdb_server, list_files, win_cmd)

parser = argparse.ArgumentParser()
parser.add_argument("-j", "--jobs", type=int, default=0,
                    help="concurrent checks (default: one per core)")
parser.add_argument("filter", nargs="*", help="only files whose path contains one of these")
args = parser.parse_args()

commands = json.loads((BUILD_DIR / "compile_commands.json").read_text())
# A source file's command, not the first for the target: that one is the PCH's own /Yc line.
template = next((c["command"] for c in commands
                 if "OpenSHC.dll.dir" in c["command"] and "/Yu" in c["command"]), None)
if template is None:
    sys.exit("no /Yu compile command for OpenSHC.dll in compile_commands.json; reconfigure")
template_source = template.split(" -c ")[-1].strip()
# The command names its source as the compiler sees it, e.g. Z:\...\src\OpenSHC\x.cpp. Take
# the part before \src\ as the root to build the other file names on, rather than
# os.path.abspath: that returns a native path, and off Windows a name beginning with "/"
# is read by cl as an option, which fails with "D8003 missing source filename".
_marker = template_source.lower().rfind("\\src\\")
if _marker < 0:
    sys.exit("cannot tell the source root from %r" % template_source)
WIN_ROOT = template_source[:_marker]


def win_source(path):
    """A repo-relative path as the compiler's command line spells it."""
    return WIN_ROOT + "\\" + path.replace("/", "\\")

files = list_files()
if args.filter:
    files = [f for f in files if any(s in f for s in args.filter)]
if not files:
    sys.exit("no file matches %s" % ", ".join(args.filter))
jobs = max(1, args.jobs or (os.cpu_count() or 1))


def check_command(path):
    """The template aimed at one file: syntax only, and with the pdb left out of it."""
    command = re.sub(r"/Fo\S+", "/Zs", template.replace(template_source, win_source(path)))
    command = re.sub(r"\s/Zi(?=\s)", " ", command)          # no debug info for a syntax check
    command = re.sub(r"\s/Fd\S*", " ", command)             # and so no shared vcNN.pdb
    return command


# One batch per job rather than one per file: the batch carries the toolchain environment,
# which is what vsvars32-portable.bat is for, and paying for that once per file would cost
# more than the checks. Files go round-robin so the batches stay about even.
batches = []
for index in range(min(jobs, len(files))):
    chunk = files[index::jobs]
    lines = ["@echo off",
             r"call %s\MSVC1400-SP1\vsvars32-portable.bat >nul" % ROOT,
             r"cd /d %s" % (ROOT / BUILD_DIR)]
    lines += [check_command(f) for f in chunk]
    bat = TMP / ("syntax_check_%d.bat" % index)
    bat.write_text("\n".join(lines) + "\n")
    batches.append(bat)


def run_batch(bat, endpoint):
    result = subprocess.run(win_cmd(str(bat.resolve())), capture_output=True, text=True,
                            env=build_env(endpoint), stdin=subprocess.DEVNULL)
    return result.stdout + result.stderr


def run_check(endpoint=None):
    if len(batches) == 1:
        return run_batch(batches[0], endpoint)
    with ThreadPoolExecutor(max_workers=len(batches)) as pool:
        return "".join(pool.map(lambda b: run_batch(b, endpoint), batches))


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
