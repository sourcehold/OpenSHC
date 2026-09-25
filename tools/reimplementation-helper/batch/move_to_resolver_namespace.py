"""Move function sources into the namespace/folder their resolver now lives in.

usage: move_to_resolver_namespace.py [--dry-run] [--drop-include HEADER]... FILE...

For each FILE (single '// FUNCTION:' marker), the resolver with that address is
looked up in all *.func.hpp files. The definition is re-wrapped in the resolver's
namespaces (or qualified with its class), includes are updated, the file is
moved with `git mv` to src/<namespace path>/<function>.cpp, and the entry in
cmake/openshc-sources.txt.local is renamed. Used after the upstream UI refactor
removed OpenSHC/UI.func.hpp; run fix_func_refs.py afterwards for call sites.
"""

import argparse
import os
import re
import subprocess

import common

parser = argparse.ArgumentParser()
parser.add_argument("--dry-run", action="store_true")
parser.add_argument("--drop-include", action="append", default=[])
parser.add_argument("files", nargs="+")
args = parser.parse_args()

by_address = {e["addr"]: e for e in common.resolver_index()}
sources_list = common.SOURCES_LIST.read_text()


def owner_is_class(owner):
    header = "src/" + "/".join(owner[:-1]) + "/" + owner[-1] + ".hpp"
    if not os.path.exists(header):
        return False
    return re.search(r"\b(class|struct)\s+%s\b" % owner[-1], common.read_text(header)) is not None


for f in [common.repo_relative(p) for p in args.files]:
    text = common.read_text(f)
    addresses = common.FUNCTION_RE.findall(text)
    if len(addresses) != 1:
        print("SKIP (need exactly one FUNCTION marker)", f, addresses)
        continue
    resolver = by_address.get(int(addresses[0], 16))
    if not resolver:
        print("NO RESOLVER for", addresses[0], f)
        continue
    parts = resolver["target"].split("::")
    name, owner = parts[-1], parts[:-1]
    is_class = owner_is_class(owner)

    includes = [l for l in text.splitlines() if l.startswith("#include") and
                not any(h in l for h in args.drop_include)]
    own_include = '#include "%s"' % resolver["inc"]
    if own_include not in includes:
        includes.insert(0, own_include)

    # strip the existing namespace wrappers, keep the code inside them
    inner, opened = [], 0
    for line in text[text.index("namespace OpenSHC {"):].splitlines():
        if re.match(r"^\s*namespace \w+ \{\s*$", line):
            opened += 1
        else:
            inner.append(line)
    closed = 0
    while inner and closed < opened and (re.match(r"^\s*\}\s*(//.*)?$", inner[-1]) or not inner[-1].strip()):
        if inner[-1].strip():
            closed += 1
        inner.pop()
    code = "\n".join(inner)
    qualified = (owner[-1] + "::" + name) if is_class else name
    code, found = re.subn(r"(?<![\w:])[\w:]*\b%s\s*\(" % name, qualified + "(", code, count=1)

    namespaces = owner[:-1] if is_class else owner
    ordered = sorted(set(includes), key=lambda x: (not x.endswith('.func.hpp"'), "Globals" in x, x))
    result = "\n".join(ordered) + "\n\n" + "".join("namespace %s {\n" % n for n in namespaces)
    result += "\n" + code.strip("\n") + "\n\n" + "}\n" * len(namespaces)

    destination = "src/" + "/".join(owner) + "/" + name + ".cpp"
    print("%s %s -> %s%s" % ("MOVE" if destination != f else "KEEP", f, destination,
                             "" if found else "  (definition not found!)"))
    if args.dry_run:
        continue
    if destination != f:
        if os.path.exists(destination):
            print("  destination exists, skipped")
            continue
        os.makedirs(os.path.dirname(destination), exist_ok=True)
        subprocess.run(["git", "mv", f, destination], check=True)
        sources_list = sources_list.replace(f + "\n", destination + "\n")
    common.write_text(destination, result)
    common.format_file(destination)

if not args.dry_run:
    common.write_text(common.SOURCES_LIST, sources_list)
