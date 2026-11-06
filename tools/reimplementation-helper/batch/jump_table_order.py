"""Put the cases of a state switch in the order the original emits their bodies.

MSVC lays the bodies of a real jump-table switch out in source order, so a source whose
cases are in a different order can never match beyond the dispatch. This compares the
switch in each source with the original's jump table and reorders the cases to match.

    python jump_table_order.py                  # report on every file in the sources list
    python jump_table_order.py UpdateDeer       # one function
    python jump_table_order.py --apply Map/Units

Names may be function names, or substrings of the source path. Without --apply nothing is
written. Reordering is refused when a case body can fall through into the next one, since
moving it would change behaviour.
"""

import re
import sys
from pathlib import Path

import common
import original_asm

SWITCH_RE = re.compile(r"^        switch \(.*\.state\.\w+\) \{\n", re.M)
CASE_RE = re.compile(r"^        (?:case (.*?):(?:$| \{)|default:)")
# a body that ends in one of these cannot fall through into the case below it
TERMINATORS = ("return;", "break;", "return TRUE;", "return FALSE;", "}")


def state_values():
    """Map every UnitState* enumerator name to its value."""
    values = {}
    for header in Path("src/OpenSHC/Map/Units/States").glob("*.hpp"):
        for m in re.finditer(r"(\w+) = (\d+),? //", common.read_text(header)):
            values[m.group(1)] = int(m.group(2))
    return values


def case_value(label, values):
    """The numeric value of a `case X:` label, or None for default/unknown."""
    label = label.strip()
    m = re.fullmatch(r"(?:\(.*\)\s*)?(0x[0-9a-fA-F]+|\d+)", label)
    if m:
        return int(m.group(1), 0)
    return values.get(label.split("::")[-1])


def parse_switch(text, values):
    """Split the body of the state switch into case groups.

    Returns (start, end, groups); each group has its source lines and its case values.
    """
    m = SWITCH_RE.search(text)
    if not m:
        return None
    start = m.end()
    end = text.index("\n        }\n", start) + 1
    groups, current, previous_was_case = [], None, False
    for line in text[start:end].split("\n"):
        case = CASE_RE.match(line)
        if case and not previous_was_case:
            current = dict(lines=[], values=[])
            groups.append(current)
        current["lines"].append(line)
        if case and case.group(1) is not None:
            current["values"].append(case_value(case.group(1), values))
        previous_was_case = case is not None
    return start, end, groups


def falls_through(group):
    body = [line.strip() for line in group["lines"] if line.strip()]
    return bool(body) and not body[-1].endswith(TERMINATORS)


def process(path, apply, values):
    name = Path(path).stem
    try:
        address = original_asm.resolve(name)
    except SystemExit:
        return
    table = original_asm.state_table(original_asm.disassemble(address))
    if not table:
        return
    text = common.read_text(path)
    parsed = parse_switch(text, values)
    if not parsed:
        print("%-28s switch not found in the source (an if-chain cannot be reordered)" % name)
        return
    start, end, groups = parsed
    order, used = [], set()
    for wanted in original_asm.case_groups(table):
        for i, group in enumerate(groups):
            if i not in used and set(wanted) & set(group["values"]):
                order.append(i)
                used.add(i)
                break
    order += [i for i in range(len(groups)) if i not in used]
    if order == list(range(len(groups))):
        print("%-28s already in jump-table order" % name)
        return
    risky = [i for i in order if falls_through(groups[i])]
    if risky:
        print("%-28s REFUSED: case %s can fall through into the next one" % (
            name, groups[risky[0]]["values"][:1]))
        return
    print("%-28s reorder %s -> %s" % (name, [g["values"][:1] for g in groups],
                                      [groups[i]["values"][:1] for i in order]))
    if not apply:
        return
    lines = []
    for i in order:
        group = list(groups[i]["lines"])
        while group and not group[-1].strip():
            group.pop()
        lines.extend(group)
    common.write_text(path, text[:start] + "\n".join(lines) + "\n" + text[end:])
    common.format_file(path)


def main():
    apply = "--apply" in sys.argv
    names = [a for a in sys.argv[1:] if not a.startswith("--")]
    files = common.list_files()
    if names:
        files = [f for f in files if any(n in f or Path(f).stem == n for n in names)]
        if not files:
            sys.exit("no file in %s matches %s" % (common.SOURCES_LIST, names))
    values = state_values()
    for path in files:
        process(path, apply, values)


if __name__ == "__main__":
    main()
