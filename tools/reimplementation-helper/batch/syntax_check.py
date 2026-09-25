"""Fast syntax check (cl /Zs) of list files without a full build or link.

usage: syntax_check.py [path-substring...]   (default: every file in cmake/openshc-sources.txt.local)

Needs build-RelWithDebInfo/compile_commands.json from a previous configure. Files
are checked serially: runs sharing the PCH/pdb in parallel give bogus errors.
"""

import json
import os
import re
import subprocess
import sys

from common import BUILD_DIR, ROOT, TMP, list_files

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

result = subprocess.run(["cmd", "/c", str(bat.resolve())], capture_output=True, text=True)
errors = [l for l in (result.stdout + result.stderr).splitlines() if " error " in l or "fatal" in l]
for line in errors:
    print(re.sub(r"^.*src.OpenSHC.", "", line)[:260])
print("ERRORS", len(errors), "files", len(files))
