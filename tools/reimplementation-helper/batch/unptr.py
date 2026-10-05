"""Replace the decompiler's field-walking pointers with the field itself.

`x->field += 1` on a field the compiler already has an address for comes back as a pointer
and a store through it:

    piVar1 = &this->units[i].attackedBy;
    *piVar1 = *piVar1 + 1;

which is `this->units[i].attackedBy = this->units[i].attackedBy + 1`. MSVC regenerates the
same instruction from the field form, and the project style asks for named fields rather
than pointers walking over structs.

Only the two-adjacent-line shape is rewritten, where the store immediately follows the
pointer's assignment. That matters for more than simplicity: a pointer freezes the address,
while the field form re-evaluates the index. With nothing between the two lines the index
cannot have changed, so the rewrite is safe. Where the decompiler sets a pointer up and
dereferences it further down -- past a call, or past a write to the index -- this leaves it
alone, because there the two forms can genuinely differ.

usage:
  unptr.py [path-filter] [--apply]
"""

import argparse
import re

import common

# "  PTR = &LVALUE;\n  *PTR = *PTR <rest>;\n", the two lines adjacent and in that order
# the pointer may be declared on the spot ("char* pcVar3 = &...") as well as assigned, and
# the type prefix has to go with it
WALK = re.compile(
    r"(?P<indent>[ ]*)(?:[A-Za-z_][\w:]*\s*\*\s*)?(?P<ptr>p[a-z]*Var\d+)"
    r"\s*=\s*&\s*(?P<lvalue>[^;]+?)\s*;\s*\n"
    r"\s*\*(?P=ptr)\s*=\s*\*(?P=ptr)\s*(?P<rest>[^;]+?)\s*;[ ]*\n",
    re.S)


def replace(m):
    lvalue = " ".join(m.group("lvalue").split())
    # clang-format wraps long lvalues before the member access, so joining the line leaves
    # a space that does not belong there
    lvalue = re.sub(r"\s+(\.|->|\[)", r"\1", lvalue)
    rest = " ".join(m.group("rest").split())
    return "%s%s = %s %s;\n" % (m.group("indent"), lvalue, lvalue, rest)


def process(text):
    return WALK.subn(replace, text)


def leftover_pointers(text):
    """Pointer variables still declared after a pass, for reporting."""
    return sorted(set(re.findall(r"\b(p[a-z]*Var\d+)\b", text)))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("path_filter", nargs="?", default="")
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()

    total = 0
    for f in common.list_files():
        if args.path_filter not in f:
            continue
        old = common.read_text(f).replace("\r\n", "\n")
        new, n = process(old)
        if not n:
            continue
        left = leftover_pointers(new)
        print("%-52s %d rewritten%s"
              % (f.rsplit("/", 1)[-1][:-4], n,
                 ", %s still used" % ", ".join(left) if left else ""))
        total += n
        if args.apply:
            common.write_text(f, new)
            common.format_file(f)
    print("%d pointer walk(s) removed%s"
          % (total, "" if args.apply else " (dry run, pass --apply)"))
