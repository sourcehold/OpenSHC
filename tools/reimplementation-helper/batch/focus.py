"""Build and measure a few functions instead of the whole list, for a fast edit loop.

The sources list decides what gets compiled into the DLL, so trimming it to the file being
worked on turns a ~15 minute build into ~15 seconds. This trims the list, builds, and
reports the match percentages, keeping the full list safe so it can be put back.

    python focus.py UpdateEngineer            # trim to that file, build, report
    python focus.py --diff UpdateEngineer     # and print its assembly diff
    python focus.py AIVState                  # every listed file whose path matches
    python focus.py --restore                 # put the full list back

Names are function names (the file's stem) or substrings of the path. The first trim saves
the current list to build-RelWithDebInfo/batch/sources-full.txt and later trims leave that
copy alone, so `--restore` always brings back the real list however many times it ran. The
list on disk stays trimmed between runs, which is what makes repeated builds cheap; restore
it before a full verification build.
"""

import subprocess
import sys
from pathlib import Path

import common

SAVED = common.TMP / "sources-full.txt"
HERE = Path(__file__).resolve().parent


def run(script, *args):
    return subprocess.run([sys.executable, str(HERE / script)] + list(args),
                          capture_output=True, text=True).stdout


def restore():
    if not SAVED.exists():
        sys.exit("no saved list at %s; nothing to restore" % SAVED)
    common.write_text(common.SOURCES_LIST, common.read_text(SAVED))
    print("restored %s (%d files)" % (common.SOURCES_LIST, len(common.list_files(existing_only=False))))


def main():
    argv = sys.argv[1:]
    if "--restore" in argv:
        restore()
        return
    want_diff = "--diff" in argv
    names = [a for a in argv if not a.startswith("--")]
    if not names:
        sys.exit(__doc__)
    # the saved copy is only written once, so repeated trims cannot lose the full list
    full = common.read_text(SAVED).splitlines() if SAVED.exists() else common.list_files(existing_only=False)
    if not SAVED.exists():
        common.write_text(SAVED, "\n".join(full) + "\n")
        print("saved the full list (%d files) to %s" % (len(full), SAVED))
    chosen = [f for f in full if any(n in f or Path(f).stem == n for n in names)]
    if not chosen:
        sys.exit("nothing in the saved list matches %s" % names)
    common.write_text(common.SOURCES_LIST, "\n".join(chosen) + "\n")
    print("building %d of %d files: %s" % (len(chosen), len(full), ", ".join(Path(f).stem for f in chosen)))
    build = run("build_quiet.py")
    if "BUILD_OK" not in build:
        print(build.strip() or "build failed")
        return
    print(run("reccmp_report.py", "--run", "pct").strip())
    if want_diff:
        for f in chosen:
            print(run("reccmp_report.py", "diff", Path(f).stem).strip())


if __name__ == "__main__":
    main()
