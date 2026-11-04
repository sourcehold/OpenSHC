"""Build OpenSHC.dll with the object compiles run in parallel, then link through build.bat.

usage: build_parallel.py [-j N] [--max N] [--no-link] [--no-configure] [--dry-run] [filter...]

The presets use the NMake Makefiles generator and nmake has no -j, so a full build of the
whole source list compiles one file at a time on one core. This script does the bulk of
that work concurrently and then hands the result back to the normal build:

  1. configure with the RelWithDebInfo preset, exactly as build.bat does;
  2. build the precompiled header, which every other object depends on;
  3. compile every out-of-date object of the OpenSHC.dll target, -j at a time;
  4. run build_quiet.py, which assembles the .asm, links, and gives the verdict.

It is not a second build system. Step 3 replays the command nmake would have run for each
object - the same cl.exe, the same response file contents taken from build.make and
flags.make, and the same `cmake -E cmake_cl_compile_depends` wrapper, so each .obj and its
.obj.d land exactly where nmake expects them. Step 4 is then an ordinary incremental build:
it recompiles anything this script skipped or failed on, so the final DLL and the
BUILD_OK/BUILD_FAIL verdict still come from build.bat and build_quiet.py. Measured on a
four-core container under wine, a full 1138-object build went from about 7.5 hours to 35
minutes.

Every object of a target shares one vcNN.pdb through /Fd, so parallel compiles only work
because mspdbsrv.exe serialises the writers, and mspdbsrv is a singleton keyed on
_MSPDBSRV_ENDPOINT_. All jobs therefore run with this worktree's endpoint from
common.build_env - the same one build.bat derives - which is exactly how cl /MP works. Do
not give the jobs separate endpoints: they would race on the PDB.

Runs on Windows and, for CI or a Linux checkout, under wine (set WINEPREFIX; the toolchain
and a Windows cmake must be installed in it). The compiler is invoked directly rather than
through cmd, so nothing depends on shell quoting.
"""

import argparse
import json
import os
import re
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

import common
from common import BUILD_DIR, PDB_ERROR_RE, TMP, build_env, kill_pdb_server

HERE = Path(__file__).resolve().parent
PRESET = "RelWithDebInfo"
TARGET_DIR = BUILD_DIR / "CMakeFiles/OpenSHC.dll.dir"
RSP_DIR = TMP / "rsp"
WINDOWS = os.name == "nt"

# one object rule of build.make: the dep-file wrapper, then nmake's inline response file
RULE_RE = re.compile(
    r"^\t\$\(CMAKE_COMMAND\) -E cmake_cl_compile_depends "
    r"--dep-file=(?P<dep>\S+) --working-dir=(?P<wd>\S+) "
    r"--filter-prefix=\"(?P<prefix>[^\"]*)\" -- (?P<cl>\S+) @<<\n"
    r"(?P<body>.*?)\n<<$",
    re.M | re.S)

parser = argparse.ArgumentParser()
parser.add_argument("-j", "--jobs", type=int, default=0,
                    help="concurrent compiles (default: one per core)")
parser.add_argument("--max", type=int, default=60, help="error lines to print")
parser.add_argument("--no-link", action="store_true",
                    help="only compile the objects; skip the build.bat link")
parser.add_argument("--no-configure", action="store_true",
                    help="use the existing build.make instead of reconfiguring")
parser.add_argument("--dry-run", action="store_true", help="list what would be compiled")
parser.add_argument("filter", nargs="*",
                    help="only objects whose path contains one of these, e.g. Map/Buildings")
args = parser.parse_args()


# ---------------------------------------------------------------- wine paths

def _dos_devices():
    """Map each wine drive letter to the native directory it points at."""
    prefix = Path(os.environ.get("WINEPREFIX") or Path.home() / ".wine")
    devices = {}
    try:
        for link in (prefix / "dosdevices").iterdir():
            if re.fullmatch(r"[a-z]:", link.name):
                devices[link.name[0]] = Path(os.path.realpath(link))
    except OSError:
        pass
    return devices


DEVICES = {} if WINDOWS else _dos_devices()


def win_to_native(path):
    """A Windows path as seen by the compiler, as a native path. None if not resolvable."""
    path = path.replace("\\", "/")
    if WINDOWS:
        return Path(path)
    m = re.match(r"([A-Za-z]):/(.*)", path)
    if not m:
        return None
    root = DEVICES.get(m.group(1).lower())
    return root / m.group(2) if root else None


_MTIME_CACHE = {}
_DIR_CACHE = {}


def _resolve_ci(path):
    """Find `path` on a case-sensitive filesystem, ignoring case.

    /showIncludes reports some paths fully lower-cased, which Windows resolves and Linux
    does not, so the recorded headers have to be matched case-insensitively or every object
    looks as though a prerequisite of it had vanished.
    """
    parts = Path(os.path.normpath(str(path))).parts
    current = Path(parts[0])
    for part in parts[1:]:
        candidate = current / part
        if candidate.exists():
            current = candidate
            continue
        listing = _DIR_CACHE.get(current)
        if listing is None:
            try:
                listing = {entry.name.lower(): entry.name for entry in os.scandir(current)}
            except OSError:
                listing = {}
            _DIR_CACHE[current] = listing
        real = listing.get(part.lower())
        if real is None:
            return None
        current = current / real
    return current


def dep_mtime(spelling):
    """Modification time of a dependency as the depfile spells it, or None if it is gone.

    Cached across objects: the precompiled-header set repeats in all 1138 depfiles, so this
    turns ~100k stat calls into a few hundred. Single-threaded use only (the staleness scan
    runs before the pool starts).
    """
    if spelling in _MTIME_CACHE:
        return _MTIME_CACHE[spelling]
    native = win_to_native(spelling)
    stamp = None
    if native is not None:
        try:
            stamp = native.stat().st_mtime
        except OSError:
            resolved = _resolve_ci(native)
            if resolved is not None:
                try:
                    stamp = resolved.stat().st_mtime
                except OSError:
                    stamp = None
    _MTIME_CACHE[spelling] = stamp
    return stamp


def native_to_win(path):
    """A native path as a Windows path, picking the drive with the longest matching root."""
    path = Path(path).resolve()
    if WINDOWS:
        return str(path)
    best = None
    for letter, root in DEVICES.items():
        if path == root or root in path.parents:
            if best is None or len(str(root)) > len(str(DEVICES[best])):
                best = letter
    if best is None:
        sys.exit("cannot map %s into the wine prefix; is WINEPREFIX right?" % path)
    rest = path.relative_to(DEVICES[best])
    return "%s:\\%s" % (best.upper(), str(rest).replace("/", "\\"))


def win_argv(argv):
    """Run a Windows executable, through wine when we are not on Windows."""
    return list(argv) if WINDOWS else ["wine"] + list(argv)


# ---------------------------------------------------------------- preset environment

def preset_environment():
    """The `environment` block of the RelWithDebInfo build preset, as the build sees it.

    build.bat gets this from CMakePresets.json when it runs `cmake --build --preset`, so a
    compiler invoked directly - as this script does - has to set it up itself or cl.exe
    finds no INCLUDE. Read from the presets rather than hard-coded, so the two stay in step.
    """
    # the file is checked in with a UTF-8 BOM, which json.loads will not accept
    presets = json.loads(common.read_text("CMakePresets.json").lstrip("﻿"))
    by_name = {p["name"]: p for p in presets.get("buildPresets", [])}
    chain, name = [], PRESET
    while name:
        preset = by_name.get(name)
        if preset is None:
            sys.exit("no build preset %r in CMakePresets.json" % name)
        chain.append(preset)
        inherits = preset.get("inherits")
        name = inherits[0] if isinstance(inherits, list) else inherits
    source_dir = native_to_win(common.ROOT)
    merged = {}
    for preset in reversed(chain):  # a preset overrides what it inherits
        for key, value in (preset.get("environment") or {}).items():
            merged[key] = value.replace("${sourceDir}", source_dir).replace("/", "\\")
    env = build_env()
    for key, value in merged.items():
        # PATH reaches a wine process as WINEPATH; everything else passes straight through
        if key == "PATH" and not WINDOWS:
            key = "WINEPATH"
        # Keep whatever was already there after the preset's own entries: the toolchain
        # still wins every lookup, but a cmake.exe the caller put on the path stays
        # reachable, and cmakew needs it to configure.
        existing = env.get(key)
        env[key] = value + ";" + existing if existing else value
    return env


# ---------------------------------------------------------------- the jobs

class Job(object):
    def __init__(self, obj, source, argv):
        self.obj = obj              # repo-relative native path of the .obj
        self.source = source        # repo-relative native path of the source, or None
        self.argv = argv
        self.output = ""
        self.ok = True

    @property
    def name(self):
        return self.source or self.obj


def read_jobs():
    build_make = TARGET_DIR / "build.make"
    if not build_make.exists():
        sys.exit("%s not found; run without --no-configure" % build_make)
    flags = {}
    for line in common.read_text(TARGET_DIR / "flags.make").splitlines():
        m = re.match(r"^(CXX_DEFINES|CXX_INCLUDES|CXX_FLAGS|ASM_MASM_\w+) = (.*)$", line)
        if m:
            flags[m.group(1)] = m.group(2)
    text = common.read_text(build_make)
    m = re.search(r"^CMAKE_COMMAND = (.+)$", text, re.M)
    if not m:
        sys.exit("no CMAKE_COMMAND in %s" % build_make)
    cmake = m.group(1).strip()

    RSP_DIR.mkdir(parents=True, exist_ok=True)
    pch, jobs = None, []
    for rule in RULE_RE.finditer(text):
        dep = rule.group("dep")
        if "OpenSHC.dll.dir" not in dep:
            continue
        obj = dep[:-2]  # the rule names the .obj.d, we want the .obj
        body = rule.group("body").strip()
        for key, value in flags.items():
            body = body.replace("$(%s)" % key, value)
        if "$(" in body:
            sys.exit("unexpanded make variable in the rule for %s:\n%s" % (obj, body))
        rsp = RSP_DIR / (obj.replace("\\", "_").replace("/", "_") + ".rsp")
        # cl reads a response file in the ambient code page; these are all ASCII
        rsp.write_text(body + "\n", encoding="ascii", newline="\r\n")
        argv = win_argv([cmake, "-E", "cmake_cl_compile_depends",
                         "--dep-file=" + dep,
                         "--working-dir=" + rule.group("wd"),
                         "--filter-prefix=" + rule.group("prefix"),
                         "--", rule.group("cl"), "@" + native_to_win(rsp)])
        # derive the source from the object path: no drive-letter mapping needed, and it is
        # the path the rest of the tooling (the sources list, git) uses
        rel = obj.replace("\\", "/")
        prefix = "CMakeFiles/OpenSHC.dll.dir/"
        source = rel[len(prefix):-4] if rel.startswith(prefix) and rel.endswith(".obj") else None
        if source is not None and not (common.ROOT / source).exists():
            source = None  # generated, e.g. the PCH's own cmake_pch.cxx
        job = Job(rel, source, argv)
        if rel.endswith("cmake_pch.cxx.obj"):
            pch = job
        else:
            jobs.append(job)
    if pch is None:
        sys.exit("no precompiled-header rule found in %s" % build_make)
    return pch, sorted(jobs, key=lambda j: j.obj)


def out_of_date(job):
    """Whether the object has to be recompiled.

    Mirrors the rule's own dependencies - the source, flags.make, the PCH - plus the headers
    the last compile recorded in the .obj.d. Anything unknown counts as out of date, so the
    worst case is compiling something nmake would have skipped; nmake still gets the final
    say in step 4.
    """
    obj = BUILD_DIR / job.obj
    try:
        newest_allowed = obj.stat()
    except OSError:
        return True
    if newest_allowed.st_size == 0:  # a killed compile leaves an empty object behind
        return True
    stamp = newest_allowed.st_mtime
    fixed = [TARGET_DIR / "flags.make", TARGET_DIR / "cmake_pch.cxx.pch"]
    if job.source:
        fixed.append(common.ROOT / job.source)
    for dep in fixed:
        try:
            if dep.stat().st_mtime > stamp:
                return True
        except OSError:
            return True
    depfile = Path(str(obj) + ".d")
    if not depfile.exists():
        return True  # never compiled by a build that records dependencies
    for line in common.read_text(depfile).splitlines():
        line = line.strip()
        if not line:
            continue
        recorded = dep_mtime(line)
        if recorded is None or recorded > stamp:
            return True
    return False


def run_job(job, env):
    # The rules address the dep file, the .obj and the PCH relative to the build directory,
    # which is where nmake runs them; from anywhere else the wrapper fails before compiling.
    #
    # Output goes to a file rather than a pipe on purpose. Under wine the long-lived
    # wineserver inherits the child's handles, so a pipe is not closed when the compiler
    # exits and reading it to EOF can block for good.
    handle, path = tempfile.mkstemp(suffix=".out", dir=str(TMP))
    try:
        with os.fdopen(handle, "w+b") as out:
            result = subprocess.run(job.argv, stdout=out, stderr=subprocess.STDOUT,
                                    stdin=subprocess.DEVNULL, env=env, cwd=str(BUILD_DIR))
            out.seek(0)
            job.output = out.read().decode("utf-8", "replace")
    except OSError as error:
        # Could not even start the compiler (no wine, bad path); report it as this object's
        # failure rather than letting it unwind the whole pool.
        job.output, job.ok = "%s: %s" % (job.name, error), False
        return job
    finally:
        try:
            os.unlink(path)
        except OSError:
            pass
    # cl.exe prints the file name it is compiling on success, so a zero exit with an
    # "error" line in the output is still a failure; check both.
    job.ok = result.returncode == 0 and not re.search(r" error [A-Z]+\d|fatal error", job.output)
    return job


def compile_all(jobs, env, jobcount):
    done, failed = 0, []
    with ThreadPoolExecutor(max_workers=jobcount) as pool:
        for job in pool.map(lambda j: run_job(j, env), jobs):
            done += 1
            if not job.ok:
                failed.append(job)
            if done % 25 == 0 or done == len(jobs):
                print("  [%d/%d] %d failed" % (done, len(jobs), len(failed)), file=sys.stderr)
    return failed


# ---------------------------------------------------------------- main

if not args.no_configure:
    print("configuring with preset %s" % PRESET, file=sys.stderr)
    configure = subprocess.run(win_argv(["cmd", "/c", r".\cmakew", "--preset", PRESET]),
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                               stdin=subprocess.DEVNULL, env=preset_environment())
    if configure.returncode:
        sys.stdout.write(configure.stdout.decode("utf-8", "replace")[-4000:])
        print("BUILD_FAIL")
        raise SystemExit(1)

pch, jobs = read_jobs()
if args.filter:
    wanted = [f.replace("\\", "/") for f in args.filter]
    jobs = [j for j in jobs if any(f in j.obj for f in wanted)]
    if not jobs:
        sys.exit("no object matches %s" % ", ".join(args.filter))
env = preset_environment()
jobcount = args.jobs or (os.cpu_count() or 1)

stale = [j for j in jobs if out_of_date(j)]
pch_stale = out_of_date(pch)
if args.dry_run:
    for job in stale:
        print(job.name)
    print("%d of %d object(s) out of date%s"
          % (len(stale), len(jobs), "; the PCH too" if pch_stale else ""))
    raise SystemExit(0)

failed = []
if pch_stale:
    # Serial and first: every other object reads this .pch, and they would all miss or race it.
    print("building the precompiled header", file=sys.stderr)
    if not run_job(pch, env).ok:
        failed = [pch]

if not failed and stale:
    print("compiling %d of %d object(s), %d at a time" % (len(stale), len(jobs), jobcount),
          file=sys.stderr)
    failed = compile_all(stale, env, jobcount)
    pdb_hit = [j for j in failed if PDB_ERROR_RE.search(j.output)]
    if pdb_hit:
        # A wedged PDB server fails whatever happened to be compiling at the time and says
        # nothing about those sources; see the note in build_quiet.py.
        print("note: %d PDB server error(s), restarting mspdbsrv.exe and retrying those"
              % len(pdb_hit), file=sys.stderr)
        kill_pdb_server()
        still = compile_all(pdb_hit, env, 1)
        failed = [j for j in failed if j not in pdb_hit] + still
elif not failed:
    print("every object is up to date", file=sys.stderr)

log = TMP / "build_parallel.log"
with open(log, "w", encoding="utf-8") as out:
    for job in failed:
        out.write("=== %s\n%s\n" % (job.name, job.output))

if failed:
    # Report like build_quiet.py: the compiler lines only, source paths shortened.
    lines = [line for job in failed for line in job.output.splitlines()
             if re.search(r" error [A-Z]+\d|fatal error|warning C4700|warning C4715", line)]
    for line in lines[:args.max]:
        print(re.sub(r"^.*src.OpenSHC.", "", line))
    print("%d object(s) failed to compile (full output: %s)" % (len(failed), log), file=sys.stderr)
    print("BUILD_FAIL")
    raise SystemExit(1)

if args.no_link:
    print("%d object(s) compiled; not linking" % len(stale), file=sys.stderr)
    print("BUILD_OK")
    raise SystemExit(0)

# Hand back to the normal build for the .asm, the link and the verdict. It is an incremental
# build now, so it only picks up what is left - including anything this script chose to skip.
print("linking through build_quiet.py", file=sys.stderr)
raise SystemExit(subprocess.run([sys.executable, str(HERE / "build_quiet.py"),
                                 "--max", str(args.max)]).returncode)
