"""Build OpenSHC.dll and print only compiler errors (full log: build-RelWithDebInfo/batch/build.log).

usage: build_quiet.py [--keep-going] [--max N]

Prints BUILD_OK or BUILD_FAIL as the last line. build.bat exits 0 even on
compile errors, so the log is scanned instead of trusting the exit code.
--keep-going reruns the build with nmake /K to collect errors from more files.
"""

import argparse
import re
import subprocess

from common import TMP

parser = argparse.ArgumentParser()
parser.add_argument("--keep-going", action="store_true")
parser.add_argument("--max", type=int, default=60)
args = parser.parse_args()

log = TMP / "build.log"
with open(log, "w") as out:
    subprocess.run(["cmd", "/c", r".\build.bat RelWithDebInfo OpenSHC.dll"], stdout=out, stderr=subprocess.STDOUT)
if args.keep_going:
    with open(log, "w") as out:
        subprocess.run(["cmd", "/c", r".\cmakew --build --preset RelWithDebInfo --target OpenSHC.dll -- /K"],
                       stdout=out, stderr=subprocess.STDOUT)

text = log.read_text(errors="replace")
errors = [line for line in text.splitlines()
          if re.search(r" error |warning C4700|warning C4715", line) and "U1077" not in line]
for line in errors[:args.max]:
    print(re.sub(r"^.*src.OpenSHC.", "", line))
print("BUILD_FAIL" if re.search(r" error |U1077", text) else "BUILD_OK")
