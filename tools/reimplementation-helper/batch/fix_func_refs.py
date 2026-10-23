"""Repair *_Func resolver references after upstream header refactors (namespaces moved/renamed).

usage: fix_func_refs.py [--dry-run] [--drop-include HEADER]...

For every `X_Func::name` in the list files whose resolver no longer exists in
namespace X_Func, look the name up in all *.func.hpp files; if it is unique
(or unique within the same top-level namespace), rewrite the reference to the
new fully qualified `..._Func::name` and add the new .func.hpp include.
--drop-include removes an include that no longer exists (e.g. OpenSHC/UI.func.hpp).
Ambiguous or unknown names are reported and left alone.
"""

import argparse
import re

import common

parser = argparse.ArgumentParser()
parser.add_argument("--dry-run", action="store_true")
parser.add_argument("--drop-include", action="append", default=[])
args = parser.parse_args()

index = common.resolver_index()
known = set((e["funcns"], e["name"]) for e in index)
by_name = {}
for e in index:
    by_name.setdefault(e["name"], []).append(e)
REFERENCE_RE = re.compile(r"((?:OpenSHC::)?(?:\w+::)*\w+_Func)::\s*(\w+)")

for f in common.list_files():
    text = common.read_text(f)
    new_includes, notes = [], []

    def replace(m):
        namespace, name = m.group(1), m.group(2)
        full = namespace if namespace.startswith("OpenSHC::") else "OpenSHC::" + namespace
        if (full, name) in known:
            return m.group(0)
        candidates = by_name.get(name, [])
        if len(candidates) > 1:
            same_area = [e for e in candidates if e["funcns"].split("::")[1] == full.split("::")[1]]
            candidates = same_area or candidates
        if len(candidates) != 1:
            notes.append("AMBIGUOUS %s::%s (%d)" % (namespace, name, len(candidates)))
            return m.group(0)
        new_includes.append('#include "%s"' % candidates[0]["inc"])
        return candidates[0]["funcns"] + "::" + name

    fixed = REFERENCE_RE.sub(replace, text)
    if re.sub(r"\s", "", fixed) == re.sub(r"\s", "", text):
        if notes:
            print("NOTE", f, " ".join(notes))
        continue
    for header in args.drop_include:
        fixed = fixed.replace('#include "%s"\n' % header, "")
    existing = set(l for l in fixed.split("\n") if l.startswith("#include"))
    added = [i for i in dict.fromkeys(new_includes) if i not in existing]
    fixed = "".join(i + "\n" for i in added) + fixed
    print("FIXED", f, " ".join(notes))
    if not args.dry_run:
        common.write_text(f, fixed)
        common.format_file(f)
