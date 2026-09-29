"""Turn the decompiler's direction-matrix pointer walk into an indexed for loop.

Ghidra renders the eight-direction (or four-cardinal) neighbour loop of every
PathFindingState search as two pointers walking in lockstep: one over
TerrainDefinedData::clockwiseCardinalTranslationMatrix (as shorts or ints) and
one over the current row of TileMapState::directionTranslationMatrix, ended by
comparing the first pointer against an absolute address. Both are the same
direction index, so the whole shape is a plain `for` over that index:

    psVar3 = &...clockwiseCardinalTranslationMatrix[0].short_.yOffset;
    paiVar2 = DAT_TileMapState::instance.directionTranslationMatrix + sVar1;
    do { ... (*paiVar2)[0] ... *psVar3 ... ((Point8ShortXY*)(psVar3 + -2))->xOffset ...
         psVar3 = psVar3 + 4; paiVar2 = (int (*)[8])(*paiVar2 + 1);
    } while ((int)psVar3 < 0xb4908c);

becomes

    for (int _direction = 0; _direction < 8; _direction = _direction + 1) { ... }

usage: undirwalk.py [filter] [--apply]   (dry run unless --apply)
"""

import re
import sys

import common

MATRIX = "DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix"
ROW = "DAT_TileMapState::instance.directionTranslationMatrix"
# &clockwiseCardinalTranslationMatrix[0].<u>.yOffset lives at 0x00B48F54 + 0xF4 + 4.
Y_BASE = 0x00B48F54 + 0xF4 + 4
ENTRY = 8

SET_P = re.compile(r"^(?P<indent>[ \t]*)(?P<p>\w+)\s*=\s*&" + re.escape(MATRIX) + r"\[0\]\.(?P<u>short_|int_)(?:\.yOffset)?;[ \t]*\n", re.M)


def find_block(text, start):
    """Return (body_start, body_end, stmt_end) of the do { ... } while (...); at start."""
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


def convert(text):
    changes = 0
    while True:
        m = SET_P.search(text)
        if not m:
            break
        p, unit, indent = m.group("p"), m.group("u"), m.group("indent")
        rest = text[m.end():]
        # the row pointer set-up sits on either side of the matrix pointer, then the do
        ROWSET = r"(?P<a>\w+)\s*=\s*" + re.escape(ROW) + r"(?:\s*\+\s*(?P<y>[^;\n]+)|\[(?P<y2>[^\]]+)\]\s*\+\s*0)\s*;"
        m2 = re.match(r"[ \t]*" + ROWSET + r"[ \t]*\n[ \t]*do\s*(?=\{)", rest)
        start = m.start()
        if m2:
            do_at = m.end() + m2.end()
        else:
            # the row pointer was emitted before the matrix pointer
            before = re.search(r"\n[ \t]*" + ROWSET + r"[ \t]*\n?[ \t]*$", text[:m.start()])
            m2 = re.match(r"[ \t]*do\s*(?=\{)", rest)
            if not before or not m2:
                print("  skip (no row pointer around %s)" % p)
                return text, changes
            start = before.start() + 1
            do_at = m.end() + m2.end()
            m2 = before
        a = m2.group("a")
        yexpr = (m2.group("y") or m2.group("y2")).strip()
        body_start, body_end, stmt_end = find_block(text, do_at)
        body = text[body_start:body_end]
        tail = text[body_end:stmt_end]
        bound = re.search(r"while\s*\(\s*\(int\)\s*%s\s*<\s*(0x[0-9a-fA-F]+)\s*\)\s*;" % re.escape(p), tail)
        if not bound:
            print("  skip (%s: unexpected loop tail)" % p)
            return text, changes
        step_p = re.search(r"\n[ \t]*%s\s*=\s*%s\s*\+\s*(\d+);[ \t]*" % ((re.escape(p),) * 2), body)
        step_a = re.search(r"\n[ \t]*%s\s*=\s*\(int \(\*\)\[8\]\)\(\*%s\s*\+\s*(\d+)\);[ \t]*" % ((re.escape(a),) * 2), body)
        if not step_p or not step_a:
            print("  skip (%s: no increments)" % p)
            return text, changes
        width = 2 if unit == "short_" else 4
        stride = int(step_p.group(1)) * width // ENTRY
        if stride != int(step_a.group(1)):
            print("  skip (%s: strides disagree %d/%s)" % (p, stride, step_a.group(1)))
            return text, changes
        count = (int(bound.group(1), 16) - Y_BASE) // (int(step_p.group(1)) * width) * stride
        var = "_direction"
        while re.search(r"\b%s\b" % var, text):
            var += "2"
        entry = "%s[%s]" % (MATRIX, var)
        body = re.sub(r"\n[ \t]*%s\s*=\s*%s\s*\+\s*\d+;[ \t]*" % ((re.escape(p),) * 2), "", body)
        body = re.sub(r"\n[ \t]*%s\s*=\s*\(int \(\*\)\[8\]\)\(\*%s\s*\+\s*\d+\);[ \t]*" % ((re.escape(a),) * 2), "", body)
        body = body.replace("((Point8ShortXY*)(%s + -2))->xOffset" % p, "%s.short_.xOffset" % entry)
        body = body.replace("((Point8IntXY*)(%s + -1))->xOffset" % p, "%s.int_.xOffset" % entry)
        body = re.sub(r"\b%s\[-1\]" % re.escape(p), "%s.int_.xOffset" % entry, body)
        body = re.sub(r"\*%s\b" % re.escape(p), "%s.%s.yOffset" % (entry, unit), body)
        body = re.sub(r"\(\*%s\)\[0\]" % re.escape(a), "%s[%s][%s]" % (ROW, yexpr, var), body)
        if p in body or re.search(r"\b%s\b" % re.escape(a), body):
            print("  skip (%s/%s: pointer still used in body)" % (p, a))
            return text, changes
        head = "%sfor (int %s = 0; %s < %d; %s = %s + %d) " % (indent, var, var, count, var, var, stride)
        text = text[:start] + head + "{" + body + "}\n" + text[stmt_end:]
        text = text[:len(text) - len(text[stmt_end:])] if False else text
        changes += 1
    return text, changes


def main():
    apply = "--apply" in sys.argv
    args = [a for a in sys.argv[1:] if a != "--apply"]
    filter_ = args[0] if args else ""
    total = 0
    for path in common.list_files():
        if filter_ and filter_ not in path.replace("\\", "/"):
            continue
        text = common.read_text(path)
        new, n = convert(text)
        if n:
            total += n
            print("%-52s %d" % (path.split("/")[-1][:-4], n))
            if apply:
                common.write_text(path, new)
    print("%d direction walk(s) converted%s" % (total, "" if apply else " (dry run, pass --apply)"))


main()
