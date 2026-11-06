"""Add files to cmake/compiler-flags-gl.txt, the per-file /GL (LTCG) list.

The original was built with LTCG, so it keeps values in callee-saved registers across
calls. /GL only reproduces that when the callee is compiled with /GL too, which is why the
list has to name a caller *and* everything it calls through a resolver. This works those
callees out from the resolver index instead of guessing paths.

    python gl_flags.py --dry src/OpenSHC/Map/Units/UpdateEngineer.cpp
    python gl_flags.py UpdateEngineer UpdateChild      # function names work too

Nothing is written without omitting --dry. A callee whose .cpp does not exist yet is still
listed: cmake ignores missing entries, so the file is ready when that function is
reimplemented.

Careful: /GL is not free. It gives a function a register calling convention, which is wrong
for anything the original called with arguments on the stack -- putting parameterised
helpers in this list made them *worse* (see the README). It pays off for the big
state-machine functions and their callees.
"""

import re
import sys
from pathlib import Path

import common

LIST = Path("cmake/compiler-flags-gl.txt")
CALL_RE = re.compile(r"MACRO_CALL(?:_MEMBER)?\(\s*((?:\w+::)+)(\w+)")


def implementation_index():
    """Map a function address to the .cpp that implements it."""
    index = {}
    for path in Path("src/OpenSHC").rglob("*.cpp"):
        for address in common.FUNCTION_RE.findall(common.read_text(path)):
            index[int(address, 16)] = path.as_posix()
    return index


def resolve_callees(source, resolvers, implementations):
    """The .cpp paths of every function `source` calls through a resolver."""
    found = []
    for namespace, name in CALL_RE.findall(source):
        namespace = namespace.rstrip(":")
        for entry in resolvers:
            if entry["name"] != name or not entry["funcns"].endswith(namespace.split("::")[-1]):
                continue
            path = implementations.get(entry["addr"])
            if path is None:
                # not reimplemented yet: name the file it will live in
                parts = [p[:-5] if p.endswith("_Func") else p for p in entry["funcns"].split("::")]
                path = "src/" + "/".join(parts) + "/" + name + ".cpp"
            found.append(path)
            break
    return found


def main():
    dry = "--dry" in sys.argv
    names = [a for a in sys.argv[1:] if not a.startswith("--")]
    if not names:
        sys.exit(__doc__)
    resolvers = common.resolver_index()
    implementations = implementation_index()
    by_stem = {}
    for address, path in implementations.items():
        by_stem.setdefault(Path(path).stem, path)

    wanted = []
    for name in names:
        path = name.replace("\\", "/")
        if not Path(path).exists():
            path = by_stem.get(name)
            if path is None:
                sys.exit("no source found for %s" % name)
        wanted.append(path)
        wanted += resolve_callees(common.read_text(path), resolvers, implementations)

    current = [l.strip() for l in common.read_text(LIST).splitlines() if l.strip()] if LIST.exists() else []
    added = []
    for path in wanted:
        if path not in current and path not in added:
            added.append(path)
    for path in added:
        print(("exists  " if Path(path).exists() else "missing ") + path)
    if added and not dry:
        common.write_text(LIST, "\n".join(current + added) + "\n")
    print("%s %d entr%s" % ("would add" if dry else "added", len(added), "y" if len(added) == 1 else "ies"))


if __name__ == "__main__":
    main()
