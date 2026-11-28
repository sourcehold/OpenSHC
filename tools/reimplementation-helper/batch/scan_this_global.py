"""Functions where the original reaches the TroopValueState-style globals by absolute address
while our source goes through `this->`.

An original that loads `I<X>::instance+N` for a field our code writes as `this->field` means the
original source named the global instance there, not the implicit object. Reported per function as
the number of such lines on each side, plus how often our source mentions `this->`.
"""

import re
import sys

import common

GLOBAL = re.compile(r"StructResolver::Instance<([\w:]+)")
# a field access through the this pointer: the register holding `this` plus a displacement
THIS_FIELD = re.compile(r"\[(e[a-z][a-z]) [+-] 0x[0-9a-f]+\]")

filter_ = sys.argv[1] if len(sys.argv) > 1 else ""
rows = []
for f, e, _ in common.entries(common.load_diff()):
    if e is None or filter_ not in f:
        continue
    orig, recomp = common._asm_lines(e)
    name = e["name"].split("::")[-1]
    klass = "::".join(e["name"].split("::")[:-1])
    orig_global = sum(1 for l in orig if klass in l)
    our_global = sum(1 for l in recomp if klass in l)
    our_this = sum(1 for l in recomp if THIS_FIELD.search(l))
    if orig_global > our_global and our_this:
        rows.append((orig_global - our_global, name, orig_global, our_global, our_this,
                     common.read_text(f).count("this->")))

for gap, name, og, ng, nt, src in sorted(rows, reverse=True):
    print("%4d  %-55s orig %3d  ours %3d  our-this-lines %3d  src this-> %3d" % (gap, name, og, ng, nt, src))
print("%d function(s)" % len(rows))
