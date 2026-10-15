"""Collapse a guarded do-while into the plain while loop it is.

Ghidra renders every `while` whose condition the compiler hoisted as a guard plus
a do-while repeating the same test:

    if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
        do { ... } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
    }

which is just `while (cond) { ... }`. MSVC generates the same code for both, so this
is a readability change; it is applied because the original source cannot plausibly
have written the test twice.

usage: unguarded_do.py [filter] [--apply]   (dry run unless --apply)
"""

import re
import sys

import common

HEAD = re.compile(r"^(?P<ind>[ \t]+)if \((?P<cond>[^\n]+)\) \{\n(?P=ind)    do \{\n", re.M)


def norm(cond):
    return " ".join(cond.split()).strip()


def convert(text):
    changes = 0
    pos = 0
    while True:
        m = HEAD.search(text, pos)
        if not m:
            return text, changes
        indent = m.group("ind")
        # brace-match the do block
        brace = text.index("{", text.index("do ", m.start()))
        depth, i = 0, brace
        while i < len(text):
            if text[i] == "{":
                depth += 1
            elif text[i] == "}":
                depth -= 1
                if depth == 0:
                    break
            i += 1
        tail = re.match(r"\}\s*while \((?P<cond>[^\n]+)\);\n(?P=close)\}\n".replace("(?P=close)", re.escape(indent)),
                        text[i:])
        if not tail or norm(tail.group("cond")) != norm(m.group("cond")):
            pos = m.end()
            continue
        body = text[brace + 1:i]
        body = "\n".join(line[4:] if line.startswith(indent + "        ") else line for line in body.split("\n"))
        text = (text[:m.start()]
                + "%swhile (%s) {" % (indent, norm(m.group("cond")))
                + body + "}\n"
                + text[i + tail.end():])
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
        text = common.read_text(path)
        new, n = convert(text)
        if n:
            total += n
            print("%-52s %d" % (path.split("/")[-1][:-4], n))
            if apply:
                common.write_text(path, new)
    print("%d guarded do-while(s) collapsed%s" % (total, "" if apply else " (dry run, pass --apply)"))


main()
