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

with every access written as `_direction + k`. The offsets are checked against the
regular layout rather than trusted: an entry is 8 bytes with xOffset at +0 and yOffset
at +4, so from a base at entry0.yOffset the k-th pair sits at (4k - 2, 4k) shorts or
(2k - 1, 2k) ints. A file whose offsets disagree is reported and left alone - that is
either a retyped pointer or a real bug, and both need reading the original asm.

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

SET_ROW = re.compile(r"^(?P<ind>[ \t]*)(?P<a>\w+) = " + re.escape(ROW) + r"\[(?P<y>[^\]]+)\] \+ 1;[ \t]*\n", re.M)
SET_XY = re.compile(r"^[ \t]*(?P<p>\w+)\s*=\s*&" + re.escape(MATRIX) + r"\[0\]\.(?P<u>short_|int_)\.yOffset;[ \t]*\n")


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


def convert(text, name):
    changes = 0
    pos = 0
    while True:
        m = SET_ROW.search(text, pos)
        if not m:
            return text, changes
        a, yexpr, indent = m.group("a"), m.group("y").strip(), m.group("ind")
        rest = text[m.end():]
        m2 = SET_XY.match(rest)
        if not m2:
            pos = m.end()
            continue
        p, unit = m2.group("p"), m2.group("u")
        do_at = m.end() + m2.end()
        if not re.match(r"[ \t]*do\s*(?=\{)", text[do_at:]):
            pos = m.end()
            continue
        body_start, body_end, stmt_end = find_block(text, do_at)
        body, tail = text[body_start:body_end], text[body_end:stmt_end]
        bound = re.search(r"while \(\(int\)%s < (0x[0-9a-fA-F]+)\)" % re.escape(p), tail)
        step_a = re.search(r"\n[ \t]*%s = %s \+ (\d+);[ \t]*" % ((re.escape(a),) * 2), body)
        step_p = re.search(r"\n[ \t]*%s = %s \+ (0x[0-9a-fA-F]+|\d+);[ \t]*" % ((re.escape(p),) * 2), body)
        if not (bound and step_a and step_p) or int(step_a.group(1)) != BLOCKS:
            print("  %s: unexpected loop tail, left alone" % name)
            return text, changes
        width = 2 if unit == "short_" else 4
        if int(step_p.group(1), 0) * width != BLOCKS * ENTRY:
            print("  %s: %s strides %s, not %d entries - left alone"
                  % (name, p, step_p.group(1), BLOCKS))
            return text, changes
        count = (int(bound.group(1), 16) - Y_BASE) // (int(step_p.group(1), 0) * width) * BLOCKS
        var = "_direction"
        while re.search(r"\b%s\b" % var, text):
            var += "2"

        def entry(k, field):
            index = var if k == 0 else "%s + %d" % (var, k)
            return "%s[%s].%s.%s" % (MATRIX, index, unit, field)

        per_entry = ENTRY // width           # 4 shorts or 2 ints per entry
        new_body = body
        # the row of directionTranslationMatrix
        row_forms = [r"\(\*\(int \(\*\)\[8\]\)\(%s \+ -1\)\)\[0\]" % re.escape(a),
                     r"\*%s\b" % re.escape(a), r"%s\[1\]" % re.escape(a), r"%s\[2\]" % re.escape(a)]
        for k, form in enumerate(row_forms):
            new_body = re.sub(form, "%s[%s][%s + %d]" % (ROW, yexpr, var, k) if k else
                              "%s[%s][%s]" % (ROW, yexpr, var), new_body)
        # the matching entries of clockwiseCardinalTranslationMatrix
        for k in range(BLOCKS):
            x_off, y_off = per_entry * k - (per_entry // 2), per_entry * k
            x_forms = ([r"\(\(Point8ShortXY\*\)\(%s \+ -2\)\)->xOffset" % re.escape(p)] if k == 0 and width == 2
                       else [r"\(\(Point8IntXY\*\)\(%s \+ -1\)\)->xOffset" % re.escape(p)] if k == 0
                       else [r"%s\[%s\]" % (re.escape(p), hex(x_off)), r"%s\[%d\]" % (re.escape(p), x_off)])
            y_forms = ([r"\*%s\b" % re.escape(p)] if k == 0
                       else [r"%s\[%s\]" % (re.escape(p), hex(y_off)), r"%s\[%d\]" % (re.escape(p), y_off)])
            for form in x_forms:
                new_body = re.sub(form, entry(k, "xOffset"), new_body)
            for form in y_forms:
                new_body = re.sub(form, entry(k, "yOffset"), new_body)
        new_body = re.sub(r"\n[ \t]*%s = %s \+ \d+;[ \t]*" % ((re.escape(a),) * 2), "", new_body)
        new_body = re.sub(r"\n[ \t]*%s = %s \+ (?:0x[0-9a-fA-F]+|\d+);[ \t]*" % ((re.escape(p),) * 2), "", new_body)
        if re.search(r"\b%s\b" % re.escape(p), new_body) or re.search(r"\b%s\b" % re.escape(a), new_body):
            print("  %s: offsets do not match the regular layout, left alone (check the original asm)" % name)
            return text, changes
        head = "%sfor (int %s = 0; %s < %d; %s = %s + %d) " % (indent, var, var, count, var, var, BLOCKS)
        text = text[:m.start()] + head + "{" + new_body + "}\n" + text[stmt_end:].lstrip(" \t")
        changes += 1
        pos = m.start()


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
