"""Rewrite `this->field` as the global instance in the functions where the original did.

`scan_this_global.py` lists the functions whose original asm reaches a field by absolute address
while ours goes through the `this` register. There the original source named the global instance,
so the fix is textual: `this->x` -> `DAT_<Class>::instance.x`, plus the Globals include.

usage: this_to_global.py NAME... [--apply]        (names as scan_this_global.py prints them)
"""

import re
import sys

import common

apply = "--apply" in sys.argv
names = [a for a in sys.argv[1:] if a != "--apply"]
if not names:
    sys.exit(__doc__)

INCLUDE_RE = re.compile(r'^#include "OpenSHC/Globals/[^"]+"$', re.M)
changed = 0
for f in common.list_files():
    text = common.read_text(f)
    if not any(re.search(r"\b%s\b\s*\(" % n, text) for n in names) or "this->" not in text:
        continue
    klass = f.split("/")[-2]
    glob = "DAT_%s" % klass
    new = text.replace("this->", "%s::instance." % glob)
    include = '#include "OpenSHC/Globals/%s.hpp"' % glob
    if include not in new:
        existing = INCLUDE_RE.findall(new)
        if existing:
            block = sorted(existing + [include])
            new = new.replace("\n".join(existing), "\n".join(block), 1)
        else:
            new = new.replace("\nnamespace OpenSHC {", "\n%s\n\nnamespace OpenSHC {" % include, 1)
    print("%-60s %d site(s)" % (f.split("/")[-1], text.count("this->")))
    changed += 1
    if apply:
        common.write_text(f, new)
        common.format_file(f)
print("%d file(s)%s" % (changed, "" if apply else " (dry run, pass --apply)"))
