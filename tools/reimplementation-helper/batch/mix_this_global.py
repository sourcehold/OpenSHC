"""Generate `this->` / global-instance variants of one function for quick_styles.py.

The original sources mix the two: `this->field` and `DAT_X::instance.field` are the same object at
run time but compile to different addressing, and which one each *field* used is not uniform within
a function. A blanket conversion either way therefore loses as often as it gains - 16 of 49
functions measured worse when `this_to_global.py` converted everything - while splitting the fields
recovers the original's choice. Over Map::Units::TroopValueState:

    registerSpottedEnemyTile        38.7% -> 81.8%   (the indexed array on the global, the rest on this)
    initializeOrAdvanceAttackWave   40.9% -> 54.8%   (the scalars on the global, the arrays on this)
    scanForSiegeTentPoints          32.0% -> 37.2%   (one field back on this, which stops a hoist)

The split that wins is not predictable, which is the point of measuring all four. `arrays` are the
fields a `[` follows and `scalars` the rest; the variants convert whichever form the file uses into
the other one, so it works from either starting point.

usage: mix_this_global.py FILE.cpp [--run]     (--run then calls quick_styles.py)
"""

import re
import subprocess
import sys

import common

args = [a for a in sys.argv[1:] if a != "--run"]
if not args:
    sys.exit(__doc__)
path = common.repo_relative(args[0])
text = common.read_text(path)
klass = path.split("/")[-2]
glob_prefix = "DAT_%s::instance" % klass

this_member = re.search(r"this->(\w+)\.", text)
glob_member = re.search(r"%s\.(\w+)\." % re.escape(glob_prefix), text)
if this_member:
    member, src_form = this_member.group(1), "this->" + this_member.group(1)
elif glob_member:
    member, src_form = glob_member.group(1), "%s.%s" % (glob_prefix, glob_member.group(1))
else:
    sys.exit("no `this-><member>.` or `%s.<member>.` accesses in %s" % (glob_prefix, path))
dst_form = "%s.%s" % (glob_prefix, member) if src_form.startswith("this->") else "this->" + member
include = '#include "OpenSHC/Globals/DAT_%s.hpp"' % klass

fields = {"arrays": set(), "scalars": set()}
for name, after in re.findall(r"%s\.(\w+)(\[?)" % re.escape(src_form), text):
    fields["arrays" if after == "[" else "scalars"].add(name)
if not fields["arrays"] and not fields["scalars"]:
    sys.exit("nothing to split")


def convert(names):
    out = re.sub(r"%s\.(\w+)" % re.escape(src_form),
                 lambda m: "%s.%s" % (dst_form, m.group(1)) if m.group(1) in names else m.group(0), text)
    if dst_form.startswith("DAT_") and include not in out:
        out = out.replace('#include "OpenSHC/Globals/', include + '\n#include "OpenSHC/Globals/', 1)
    return out


name = re.search(r"//\s*FUNCTION:[^\n]*\n\s*[\w:&*\s]+?(\w+)\s*\(", text).group(1)
out_dir = common.TMP / "variants" / name
out_dir.mkdir(parents=True, exist_ok=True)
for style, body in (("base", text),
                    ("all_other", convert(fields["arrays"] | fields["scalars"])),
                    ("arrays_other", convert(fields["arrays"])),
                    ("scalars_other", convert(fields["scalars"]))):
    (out_dir / (style + ".cpp")).write_text(body, encoding="utf-8", newline="")
print("%s: %s -> %s, %d array field(s), %d scalar field(s)"
      % (name, src_form, dst_form, len(fields["arrays"]), len(fields["scalars"])))
if "--run" in sys.argv:
    subprocess.run([sys.executable, str(common.ROOT / "tools/reimplementation-helper/batch/quick_styles.py"), name])
