#!/usr/bin/env python3
"""Enable or disable struct resolvers in the generated Globals headers.

Python port of Enable-Reimplemented-Data.ps1: rewrites the boolean flag of every
MACRO_STRUCT_RESOLVER(...) line in the matched .hpp files.
"""

import argparse
import glob
import re
import sys


def enable_reimplemented_data(hpp_files=r".\src\OpenSHC\Globals\*.hpp", enable=True):
    target = str(not enable).lower()
    replacement = str(enable).lower()
    pattern = re.compile(r"MACRO_STRUCT_RESOLVER(.*), %s," % target)
    changed = []
    for path in glob.glob(hpp_files):
        with open(path, "rb") as handle:
            content = handle.read().decode("utf-8")
        new_content = pattern.sub(
            lambda m: "MACRO_STRUCT_RESOLVER%s, %s," % (m.group(1), replacement),
            content,
        )
        if new_content != content:
            with open(path, "wb") as handle:
                handle.write(new_content.encode("utf-8"))
            changed.append(path)
    return changed


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--hpp-files", default=r".\src\OpenSHC\Globals\*.hpp",
                        help="glob pattern of headers to process")
    group = parser.add_mutually_exclusive_group()
    group.add_argument("--enable", dest="enable", action="store_true", default=True,
                       help="enable the struct resolvers (default)")
    group.add_argument("--disable", dest="enable", action="store_false",
                       help="disable the struct resolvers")
    args = parser.parse_args(argv)

    changed = enable_reimplemented_data(args.hpp_files, args.enable)
    for path in changed:
        print(path)
    return 0


if __name__ == "__main__":
    sys.exit(main())
