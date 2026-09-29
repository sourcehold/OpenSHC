"""Turn the decompiler's counted do-while loops into `for` loops.

    iVar6 = 0;
    do { ... iVar6 = iVar6 + 1; } while (iVar6 < 8);

is a `for (int iVar6 = 0; iVar6 < 8; iVar6 = iVar6 + 1) { ... }`. Only the shape
where the counter is initialised immediately before the loop, stepped by the last
statement of the body, and not otherwise written is converted; anything else is
left for hand work. The counter must not be read after the loop.

usage: docount.py [filter] [--apply]   (dry run unless --apply)
"""

import re
import sys

import common

INIT = re.compile(r"^(?P<ind>[ \t]+)(?:(?P<decl>int|uint) )?(?P<var>\w+) = (?P<from>0|1);\n(?P=ind)do \{\n", re.M)


def convert(text):
    changes = 0
    pos = 0
    while True:
        m = INIT.search(text, pos)
        if not m:
            return text, changes
        indent, var = m.group("ind"), m.group("var")
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
        tail = re.match(r"\} while \((?P<cond>[^\n]+)\);\n", text[i:])
        if not tail:
            pos = m.end()
            continue
        cond = " ".join(tail.group("cond").split())
        if not re.match(r"^\(?%s\)? [<!=]=? .+$" % re.escape(var), cond):
            pos = m.end()
            continue
        body = text[brace + 1:i]
        step = re.search(r"\n(?P<ind2>[ \t]+)%s = %s \+ (?P<by>\d+);\n[ \t]*$" % ((re.escape(var),) * 2), body)
        if not step:
            pos = m.end()
            continue
        # the counter must not be assigned anywhere else in the body
        writes = re.findall(r"\b%s\b\s*(?:=[^=]|\+\+|--)" % re.escape(var), body)
        if len(writes) != 1:
            pos = m.end()
            continue
        # ... nor read after the loop
        after = text[i + tail.end():]
        stop = after.find("\n" + indent[:-4] + "}") if len(indent) >= 4 else len(after)
        if re.search(r"\b%s\b" % re.escape(var), after[:stop if stop > 0 else len(after)]):
            pos = m.end()
            continue
        body = body[:step.start()] + "\n"
        body = "\n".join(line[4:] if line.startswith(indent + "        ") else line for line in body.split("\n"))
        head = "%sfor (%s%s = %s; %s; %s = %s + %s) {" % (
            indent, (m.group("decl") + " ") if m.group("decl") else "int ",
            var, m.group("from"), cond, var, var, step.group("by"))
        text = text[:m.start()] + head + body + indent + "}\n" + text[i + tail.end():]
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
    print("%d counted do-while(s) turned into for loops%s" % (total, "" if apply else " (dry run, pass --apply)"))


main()
