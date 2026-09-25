"""Shared helpers for the batch reimplementation scripts.

All scripts operate on the files listed in cmake/openshc-sources.txt.local and
change the working directory to the repository root.
"""

import difflib
import json
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
# directory the script was started from, to resolve relative command line paths
INVOCATION_DIR = Path.cwd()
os.chdir(ROOT)

# override with OPENSHC_SOURCES_LIST=<file> to work on a different selection
SOURCES_LIST = Path(os.environ.get("OPENSHC_SOURCES_LIST", "cmake/openshc-sources.txt.local"))
BUILD_DIR = Path("build-RelWithDebInfo")
# scratch directory inside the (git-ignored) build directory
TMP = BUILD_DIR / "batch"
TMP.mkdir(parents=True, exist_ok=True)
DIFF_JSON = Path("reccmp/dll/diff.json")

FUNCTION_RE = re.compile(r"//\s*FUNCTION:\s*STRONGHOLDCRUSADER\s+(0x[0-9A-Fa-f]+)")


def list_files(existing_only=True):
    files = [line.strip() for line in SOURCES_LIST.read_text().splitlines() if line.strip()]
    if not existing_only:
        return files
    missing = [f for f in files if not Path(f).exists()]
    if missing:
        print("warning: %d listed file(s) do not exist, e.g. %s" % (len(missing), missing[0]), file=sys.stderr)
    return [f for f in files if Path(f).exists()]


def repo_relative(path):
    """Turn a command line path (relative to where the script was started) into a repo-relative posix path."""
    return (INVOCATION_DIR / path).resolve().relative_to(ROOT).as_posix()


def clang_format():
    """Locate a clang-format that understands the repo's .clang-format (needs a recent version)."""
    exe = os.environ.get("CLANG_FORMAT") or shutil.which("clang-format")
    if not exe:
        sys.exit("clang-format not found; pip install clang-format or set CLANG_FORMAT")
    return exe


def format_file(path):
    subprocess.run([clang_format(), "-i", "-style=file", str(path)], check=True)


def read_text(path):
    # some sources contain non-UTF-8 bytes; latin-1 round-trips them unchanged
    try:
        return Path(path).read_text(encoding="utf-8")
    except UnicodeDecodeError:
        return Path(path).read_text(encoding="latin-1")


def write_text(path, text):
    # always write UTF-8/LF (the Windows default encoding would corrupt non-ASCII comments)
    Path(path).write_text(text, encoding="utf-8", newline="\n")


def function_body_span(text, start=0):
    """Return (begin, end) of the function whose '// FUNCTION:' marker is at/after start.

    begin is the start of the marker line, end is one past the closing brace.
    """
    i = text.index("// FUNCTION:", start)
    i = text.rindex("\n", 0, i) + 1
    k = text.index("{", text.index("\n", i))
    depth = 0
    while True:
        if text[k] == "{":
            depth += 1
        elif text[k] == "}":
            depth -= 1
            if depth == 0:
                return i, k + 1
        k += 1


# ---------------------------------------------------------------- reccmp


def run_reccmp():
    result = subprocess.run(
        ["cmd", "/c", r"reccmp\dll\run.bat", "reccmp-reccmp", "--target", "STRONGHOLDCRUSADER", "--json", "diff.json"],
        capture_output=True, text=True, stdin=subprocess.DEVNULL)
    if result.returncode:
        sys.exit("reccmp failed:\n" + result.stdout[-800:] + result.stderr[-800:])


def load_diff():
    return {int(e["address"], 16): e for e in json.loads(DIFF_JSON.read_text())["data"]}


def entries(byaddr, files=None):
    """Yield (file, reccmp entry or None, address string) for every FUNCTION marker in the list files."""
    for f in files if files is not None else list_files(existing_only=False):
        try:
            text = read_text(f)
        except OSError:
            yield f, None, "MISSING"
            continue
        for address in FUNCTION_RE.findall(text):
            yield f, byaddr.get(int(address, 16)), address


SOURCE_LINE_RE = re.compile(r"\.cpp:(\d+)\)")
REGISTERS = r"(?:e?(?:ax|bx|cx|dx|si|di|bp|sp)|[abcd][lh])"


def diff_rows(entry):
    """Yield (kind, text, source line) for every row of a reccmp diff, in order.

    kind is "both", "orig" or "recomp"; text is the row as reccmp prints it, instruction
    first. Only our side carries a source annotation, so the line is carried forward until
    the next one appears. Every script that reads a diff goes through here.
    """
    line = None
    for hunk in entry.get("diff") or []:
        for block in hunk[1]:
            for kind, rows in block.items():
                for row in rows:
                    if kind != "orig":
                        m = SOURCE_LINE_RE.search(row[1])
                        if m:
                            line = int(m.group(1))
                    yield kind, row[1], line


def instruction(text):
    """A diff row without its source annotation."""
    return text.split("\t")[0].strip()


def canonical(text, registers=True):
    """An instruction with call targets, template arguments and absolute addresses folded away.

    With registers=False the register names go too, so that a difference which is only the
    allocator's choice of register compares equal. This is for spotting *structural*
    differences; _normalize below answers a different question (see normalized_ratio) and
    deliberately folds more, so the two are not interchangeable.
    """
    s = instruction(text)
    s = re.sub(r"<OFFSET\d+>|trampoline<[^>]*>|FunctionResolver::\S+", "T", s)
    s = re.sub(r"<[^>]*>", "<T>", s)
    s = re.sub(r"0x[0-9a-f]{5,}", "A", s)
    if not registers:
        s = re.sub(r"\b%s\b" % REGISTERS, "r", s)
    return s


def _normalize(line):
    """Reduce an asm line so call targets, resolver names and absolute addresses compare equal."""
    s = line.split("\t")[0].strip()
    if s.startswith("call"):
        return "call"
    if (s.startswith("jmp <") or s.startswith("jmp trampoline") or s.startswith("jmp FunctionResolver")
            or s.startswith("jmp OpenSHC") or re.match(r"jmp -?0x[0-9a-f]{3,}$", s)):
        return "tailjmp"
    s = re.sub(r"StructResolver::Instance<[^>]*>::(instance|ptr)( \(DATA\))?", "G", s)
    s = re.sub(r"0x1[0-9a-f]{7}|0x[0-9a-f]{6,}", "G", s)
    s = re.sub(r"<OFFSET\d+>", "G", s)
    return s


def _asm_lines(entry):
    orig, recomp = [], []
    for kind, row, _ in diff_rows(entry):
        if kind != "recomp":
            orig.append(row)
        if kind != "orig":
            recomp.append(row)
    return orig, recomp


def normalized_ratio(entry):
    """Match ratio ignoring call/tail-jump targets and resolver addresses.

    100% here means only call-target differences remain ("Reimplemented").
    """
    if float(entry["matching"]) >= 1:
        return 1.0
    orig, recomp = _asm_lines(entry)
    if not orig:
        return float(entry["matching"])
    return difflib.SequenceMatcher(
        None, [_normalize(x) for x in orig], [_normalize(x) for x in recomp], autojunk=False).ratio()


def print_diff(entry):
    print("### %s %.1f%% norm %.1f%%" % (entry["name"], float(entry["matching"]) * 100, normalized_ratio(entry) * 100))
    for kind, row, _ in diff_rows(entry):
        s = re.sub(r"FunctionResolver::Resolver<.*?,&([\w:]+),\d>::GameFunction.*", r"<\1>", row)
        s = re.sub(r"StructResolver::Instance<([\w:]+),\d+>::", r"I<\1>::", s)
        print({"both": " ", "orig": "-", "recomp": "+"}[kind] + s)


# ---------------------------------------------------------------- resolver index


RESOLVER_RE = re.compile(
    r"MACRO_FUNCTION_RESOLVER\((.*?),\s*(?:true|false),\s*Address::SHC_3BB0A8C1_(0x[0-9A-Fa-f]+),"
    r"\s*&([\w:\s]+?)\)\s*(\w+);", re.S)
NAMESPACE_TOKEN_RE = re.compile(r"namespace (\w+) \{|\} // namespace (\w+)")


def resolver_index():
    """Index every MACRO_FUNCTION_RESOLVER in src/OpenSHC/**/*.func.hpp.

    Each entry: addr, target (fully qualified function), name (resolver name),
    funcns (fully qualified *_Func namespace), inc (header to include), sig.
    """
    index = []
    for f in Path("src/OpenSHC").rglob("*.func.hpp"):
        text = f.read_text(encoding="utf-8", errors="replace")
        for m in RESOLVER_RE.finditer(text):
            sig, addr, target, name = m.groups()
            target = re.sub(r"\s+", "", target)
            stack = []
            for t in NAMESPACE_TOKEN_RE.finditer(text, 0, m.start()):
                if t.group(1):
                    stack.append(t.group(1))
                elif stack:
                    stack.pop()
            if not target.startswith("OpenSHC::"):
                target = "::".join(stack[:-1] + [target])
            index.append(dict(addr=int(addr, 16), target=target, name=name, funcns="::".join(stack),
                              inc=f.as_posix()[4:], sig=" ".join(sig.split())))
    return index
