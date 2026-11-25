"""Enable the function resolvers of exactly the .cpp files in the build list.

`MACRO_FUNCTION_RESOLVER(..., false, Address::SHC_..., &Class::name)` sends a call to the
*original* game address; with `true` it calls our own implementation. The flag matters for
measuring, not only at runtime: `/GL` buys nothing while the call still leaves the module,
because LTCG cannot see the callee's register use. `getSalesPrice` went from 68.4% to 100%
once `getSellResourceAmount`'s resolver was flipped - the original keeps `this` in the
volatile EDX across that call, which only LTCG over our own code can reproduce.

`tools/reimplementation-control/Enable-Reimplemented-Functions.ps1` flips every resolver
that has a .cpp anywhere in the tree, which does not link while the build list is a subset:
each enabled resolver whose .cpp is not compiled becomes an unresolved external. This script
flips exactly the addresses implemented by the files in `cmake/openshc-sources.txt.local`,
so a narrowed list keeps linking.

Like the struct resolvers in `src/OpenSHC/Globals`, the flipped `.func.hpp` files are never
committed, so re-run this after a rebase, a fresh clone or a `git checkout` - together with
`tools/reimplementation-control/enable_reimplemented_data.py`. Note that
`git checkout -- src/OpenSHC` reverts both at once.

usage:
  enable_local_functions.py [--disable]
"""

import re
import subprocess
import sys
from pathlib import Path

import common

FUNCTION_MARKER_RE = re.compile(r"//\s*FUNCTION:\s*\S+\s+(0x[0-9A-Fa-f]+)")


def main():
    enable = "--disable" not in sys.argv[1:]
    headers = sorted(Path("src/OpenSHC").rglob("*.func.hpp"))
    # start from the committed state so a re-run is idempotent and --disable is exact
    subprocess.run(["git", "checkout", "--"] + [h.as_posix() for h in headers], check=True)
    if not enable:
        print("restored %d .func.hpp file(s) to the committed state" % len(headers))
        return 0

    addresses = set()
    for line in common.read_text(common.SOURCES_LIST).split():
        text = Path(line).read_text(encoding="utf-8", errors="replace")
        addresses |= {a.lower() for a in FUNCTION_MARKER_RE.findall(text)}

    flipped, touched = 0, 0
    for header in headers:
        text = original = header.read_text(encoding="utf-8")
        for address in addresses:
            # every resolver is one macro invocation; stop the body at the next invocation
            pattern = re.compile(
                r"(MACRO_FUNCTION_RESOLVER(?:_EXT)?\((?:(?!MACRO_FUNCTION_RESOLVER).)*?),"
                r"\s*false(\s*,\s*Address::SHC_3BB0A8C1_%s\b)" % address,
                re.S | re.I,
            )
            text, count = pattern.subn(r"\1, true\2", text)
            flipped += count
        if text != original:
            common.write_text(header, text)
            touched += 1

    missing = len(addresses) - flipped
    print("enabled %d resolver(s) in %d header(s) for %d address(es)" % (flipped, touched, len(addresses)))
    if missing:
        print("warning: %d address(es) in the build list have no resolver" % missing, file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
