"""Replace function bodies in many source files at once, then clang-format them.

usage: splice_functions.py BLOCKS.txt

BLOCKS.txt contains blocks of the form

    @@@ Map/Units/UnitsState/someFunction.cpp      (path relative to src/OpenSHC)
    +inc OpenSHC/Globals/DAT_GameCore.hpp          (optional: add #include if missing)
    +using OpenSHC::Foo::Bar                       (optional: add using-declaration)
    int UnitsState::someFunction(int unitID)
    {
        ...
    }

The function starting at the file's '// FUNCTION:' marker (through its closing
brace) is replaced. The original '// FUNCTION:' line is always kept, so a block
may omit it (a '// FUNCTION' line in the block is dropped). This is the same
block format that show_functions.py prints.
"""

import re
import sys
from pathlib import Path

import common

text = Path(sys.argv[1]).read_text(encoding="utf-8")
for block in re.split(r"^@@@ ", text, flags=re.M)[1:]:
    header, body = block.split("\n", 1)
    path = Path("src/OpenSHC") / header.split("[")[0].strip()
    includes = re.findall(r"^\+inc (.+)$", body, re.M)
    usings = re.findall(r"^\+using (.+)$", body, re.M)
    body_lines = re.sub(r"^\+(inc|using) .+\n", "", body, flags=re.M).strip("\n").split("\n")
    if body_lines[0].strip().startswith("// FUNCTION"):
        body_lines = body_lines[1:]

    source = common.read_text(path)
    begin, end = common.function_body_span(source)
    marker = source[begin:source.index("\n", begin)].strip()
    source = source[:begin] + marker + "\n" + "\n".join(body_lines) + "\n\n" + source[end:].lstrip("\n")

    for include in includes:
        line = '#include "%s"\n' % include
        if line not in source:
            first = re.search(r"^#include .*\n", source, re.M)
            position = first.end() if first else 0
            source = source[:position] + line + source[position:]
    for using in usings:
        line = "using %s;\n" % using
        if line.strip() not in source:
            last_namespace = list(re.finditer(r"^\s*namespace \w+ \{\n", source, re.M))[-1]
            source = source[:last_namespace.end()] + "\n" + line + source[last_namespace.end():]

    common.write_text(path, source)
    common.format_file(path)
    print("ok", path)
