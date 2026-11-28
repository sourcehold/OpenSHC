"""Swap the two arms of an if/else chain in place, without changing behaviour.

`if (C1) { B1 } else { B2 }`           becomes  `if (negC1) { B2 } else { B1 }`
`if (C1) { B1 } else if (C2) { B2 }`   becomes  `if (negC1) { if (C2) { B2 } } else { B1 }`

The point is the generated block *layout*: reccmp reads the original's block order as its
source order, so putting our arms in that order is how the two streams line up.  Both the
`if` header and the `else if` header may wrap over several lines.

usage: swap_arms.py FILE IF_LINE "negated C1"      (IF_LINE is 1-based)
"""
import sys
from pathlib import Path


def header_end(lines, start):
    j = start
    while not lines[j].rstrip().endswith("{"):
        j += 1
    return j


def find_chain(lines, a):
    ind = len(lines[a]) - len(lines[a].lstrip())
    body = header_end(lines, a) + 1
    depth, else_at = 1, None
    for j in range(body, len(lines)):
        stripped = lines[j].strip()
        same_level = (len(lines[j]) - len(lines[j].lstrip())) == ind
        if depth == 1 and same_level and stripped.startswith("} else"):
            else_at = j
            break
        depth += lines[j].count("{") - lines[j].count("}")
    assert else_at is not None, "no `} else` for the if at line %d" % (a + 1)
    hdr = header_end(lines, else_at)
    depth, end = 1, None
    for j in range(hdr + 1, len(lines)):
        depth += lines[j].count("{") - lines[j].count("}")
        if depth == 0:
            end = j
            break
    assert end is not None and lines[end].strip() == "}", "no close for the else at line %d" % (else_at + 1)
    return ind, body, else_at, hdr, end


def reindent(block, extra):
    pad = " " * extra
    return [pad + x if x.strip() else x for x in block]


def main():
    path, at, neg = Path(sys.argv[1]), int(sys.argv[2]) - 1, sys.argv[3]
    lines = path.read_text().split("\n")
    assert lines[at].strip().startswith("if ("), repr(lines[at])
    ind, body, else_at, hdr, end = find_chain(lines, at)
    pad = " " * ind
    arm1 = lines[body:else_at]
    arm2 = lines[hdr + 1:end]
    header = [lines[else_at].strip()[len("} else "):]] + [x.strip() for x in lines[else_at + 1:hdr + 1]]
    if header[0] == "{":
        new = [pad + "if (" + neg + ") {"] + arm2 + [pad + "} else {"] + arm1 + [pad + "}"]
        kind = "plain else"
    else:
        new = ([pad + "if (" + neg + ") {"]
               + [pad + "    " + h for h in header]
               + reindent(arm2, 4) + [pad + "    }", pad + "} else {"] + arm1 + [pad + "}"])
        kind = "else-if (%d header lines)" % len(header)
    path.write_text("\n".join(lines[:at] + new + lines[end + 1:]))
    print("line %d: arm1 %d lines, arm2 %d lines, %s" % (at + 1, len(arm1), len(arm2), kind))


main()
