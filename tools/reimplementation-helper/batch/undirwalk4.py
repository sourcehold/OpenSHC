"""The four-at-a-time variant of undirwalk.py.

Where the original wrote the neighbour loop out four directions at a time, Ghidra
walks the row of directionTranslationMatrix from its *second* element and reaches the
four directions as [-1], [0], [1] and [2], with a second pointer stepping the matching
four entries of clockwiseCardinalTranslationMatrix:

    piVar7 = DAT_TileMapState::instance.directionTranslationMatrix[iVar8] + 1;
    psVar6 = &...clockwiseCardinalTranslationMatrix[0].short_.yOffset;
    do { ... (*(int (*)[8])(piVar7 + -1))[0] ... *piVar7 ... piVar7[1] ... piVar7[2] ...
         ((Point8ShortXY*)(psVar6 + -2))->xOffset ... *psVar6 ... psVar6[2] ... psVar6[4] ...
         piVar7 = piVar7 + 4; psVar6 = psVar6 + 0x10;
    } while ((int)psVar6 < 0xb4908c);

Both pointers are the same direction index, so the block becomes

    for (int _direction = 0; _direction < 8; _direction = _direction + 4) { ... }

with every access written as `_direction + k`. The two set-up statements appear in
either order and need not be adjacent, so they are matched by looking back from the
`do`; anything else in between is left where it is.

The offsets are checked against the regular layout rather than trusted: an entry is 8
bytes with xOffset at +0 and yOffset at +4, so from a base at entry0.yOffset the k-th
pair sits at (4k - 2, 4k) shorts or (2k - 1, 2k) ints. A loop whose offsets disagree is
reported and left alone - that is either a retyped pointer or a real bug, and both need
reading the original asm.

usage: undirwalk4.py [filter] [--apply]   (dry run unless --apply)
"""

import re
import sys

import common

MATRIX = "DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix"
ROW = "DAT_TileMapState::instance.directionTranslationMatrix"
Y_BASE = 0x00B48F54 + 0xF4 + 4
ENTRY = 8
BLOCKS = 4
LOOKBACK = 4

DO = re.compile(r"^(?P<ind>[ \t]*)do (?=\{)", re.M)
SET_ROW = re.compile(r"^[ \t]*(?P<a>\w+) = " + re.escape(ROW) + r"\[(?P<y>[^\]]+)\] \+ 1;[ \t]*\n", re.M)
SET_XY = re.compile(r"^[ \t]*(?P<p>\w+) = &" + re.escape(MATRIX) + r"\[0\]\.(?P<u>short_|int_)\.yOffset;[ \t]*\n", re.M)


def find_block(text, start):
    open_brace = text.index("{", start)
    depth, i = 0, open_brace
    while i < len(text):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                break
        i += 1
    return open_brace + 1, i, text.index(";", i) + 1


def preceding_lines(text, at, count):
    """Spans of the `count` lines that end at `at`, outermost first."""
    spans, end = [], at
    for _ in range(count):
        start = text.rfind("\n", 0, end - 1) + 1
        if start <= 0:
            break
        spans.append((start, end))
        end = start
    return spans


def convert(text, name):
    changes = 0
    pos = 0
    while True:
        do = DO.search(text, pos)
        if not do:
            return text, changes
        pos = do.end()
        row = xy = None
        for start, end in preceding_lines(text, do.start(), LOOKBACK):
            line = text[start:end]
            if row is None and SET_ROW.match(line):
                row = (start, end, SET_ROW.match(line))
            elif xy is None and SET_XY.match(line):
                xy = (start, end, SET_XY.match(line))
        if row is None or xy is None:
            continue
        a, yexpr = row[2].group("a"), row[2].group("y").strip()
        p, unit = xy[2].group("p"), xy[2].group("u")
        indent = do.group("ind")

        body_start, body_end, stmt_end = find_block(text, do.end())
        body, tail = text[body_start:body_end], text[body_end:stmt_end]
        bound = re.search(r"while \(\(int\)%s < (0x[0-9a-fA-F]+)\)" % re.escape(p), tail)
        step_a = re.search(r"\n[ \t]*%s = %s \+ (\d+);[ \t]*" % ((re.escape(a),) * 2), body)
        step_p = re.search(r"\n[ \t]*%s = %s \+ (0x[0-9a-fA-F]+|\d+);[ \t]*" % ((re.escape(p),) * 2), body)
        if not (bound and step_a and step_p) or int(step_a.group(1)) != BLOCKS:
            continue
        width = 2 if unit == "short_" else 4
        if int(step_p.group(1), 0) * width != BLOCKS * ENTRY:
            print("  %s: %s strides %s, not %d entries - left alone" % (name, p, step_p.group(1), BLOCKS))
            continue
        # the pointer froze the row at its initial index; re-reading the index each
        # iteration is only the same thing if nothing in the body writes it
        reassigned = [n for n in re.findall(r"[A-Za-z_]\w*", yexpr)
                      if re.search(r"\b%s\b\s*(?:=[^=]|\+\+|--)" % re.escape(n), body)]
        if reassigned:
            print("  %s: row index %s is reassigned in the body - left alone" % (name, reassigned[0]))
            continue
        count = (int(bound.group(1), 16) - Y_BASE) // (int(step_p.group(1), 0) * width) * BLOCKS
        var = "_direction"
        while re.search(r"\b%s\b" % var, text):
            var += "2"

        def entry(k, field):
            index = var if k == 0 else "%s + %d" % (var, k)
            return "%s[%s].%s.%s" % (MATRIX, index, unit, field)

        per_entry = ENTRY // width
        new_body = body
        row_forms = [r"\(\*\(int \(\*\)\[8\]\)\(%s \+ -1\)\)\[0\]" % re.escape(a),
                     r"\*%s\b" % re.escape(a),
                     r"%s\[1\]" % re.escape(a),
                     r"%s\[2\]" % re.escape(a)]
        for k, form in enumerate(row_forms):
            index = var if k == 0 else "%s + %d" % (var, k)
            new_body = re.sub(form, "%s[%s][%s]" % (ROW, yexpr, index), new_body)
        for k in range(BLOCKS):
            x_off, y_off = per_entry * k - (per_entry // 2), per_entry * k
            if k == 0:
                x_forms = [r"\(\(Point8%sXY\*\)\(%s \+ -%d\)\)->xOffset"
                           % ("Short" if width == 2 else "Int", re.escape(p), per_entry // 2)]
                y_forms = [r"\*%s\b" % re.escape(p)]
            else:
                x_forms = [r"%s\[%s\]" % (re.escape(p), hex(x_off)), r"%s\[%d\]" % (re.escape(p), x_off)]
                y_forms = [r"%s\[%s\]" % (re.escape(p), hex(y_off)), r"%s\[%d\]" % (re.escape(p), y_off)]
            for form in x_forms:
                new_body = re.sub(form, entry(k, "xOffset"), new_body)
            for form in y_forms:
                new_body = re.sub(form, entry(k, "yOffset"), new_body)
        new_body = re.sub(r"\n[ \t]*%s = %s \+ \d+;[ \t]*" % ((re.escape(a),) * 2), "", new_body)
        new_body = re.sub(r"\n[ \t]*%s = %s \+ (?:0x[0-9a-fA-F]+|\d+);[ \t]*" % ((re.escape(p),) * 2), "", new_body)
        if re.search(r"\b%s\b" % re.escape(p), new_body) or re.search(r"\b%s\b" % re.escape(a), new_body):
            print("  %s: offsets do not match the regular layout, left alone (check the original asm)" % name)
            continue
        head = "%sfor (int %s = 0; %s < %d; %s = %s + %d) " % (indent, var, var, count, var, var, BLOCKS)
        text = text[:do.start()] + head + "{" + new_body + "}\n" + text[stmt_end:].lstrip(" \t")
        # drop both set-up statements, later span first so the earlier offset stays valid
        for start, end, _ in sorted([row, xy], reverse=True):
            text = text[:start] + text[end:]
        changes += 1
        pos = 0
    return text, changes


def main():
    apply = "--apply" in sys.argv
    args = [a for a in sys.argv[1:] if a != "--apply"]
    filter_ = args[0] if args else ""
    total = 0
    for path in common.list_files():
        if filter_ and filter_ not in path.replace("\\", "/"):
            continue
        name = path.replace("\\", "/").split("/")[-1][:-4]
        text = common.read_text(path)
        new, n = convert(text, name)
        if n:
            total += n
            print("%-52s %d" % (name, n))
            if apply:
                common.write_text(path, new)
    print("%d unrolled direction walk(s) converted%s" % (total, "" if apply else " (dry run, pass --apply)"))


main()
