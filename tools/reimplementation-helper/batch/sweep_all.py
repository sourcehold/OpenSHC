"""Run every diff-pattern sweep over the sub-100 functions at once.

Each sweep looks for one way the original's instruction stream disagrees with ours in a way the
*source* controls: an inverted branch (arms the wrong way round), a near-miss constant (`x < K+1`
vs `x <= K`), swapped compare operands, a signed/unsigned mismatch, or a redundant width
conversion.  See AGENTS.md for what each one means and how often it pays.
"""
import re
import subprocess

INV = {"je": "jne", "jne": "je", "jl": "jge", "jge": "jl", "jg": "jle", "jle": "jg",
       "ja": "jbe", "jbe": "ja", "jb": "jae", "jae": "jb"}
SIGN = ({"jl", "jb"}, {"jle", "jbe"}, {"jg", "ja"}, {"jge", "jae"})
JCC = re.compile(r"^([-+])(j\w+)\s")
NUM = re.compile(r"^([-+])cmp\s+(\S+),\s*(0x[0-9a-f]+|\d+)\b")
OPS = re.compile(r"^([-+])cmp\s+(.+?),\s*([^\t]+?)\s*(?:\t.*)?$")


def run(*args):
    return subprocess.run(["python", "tools/reimplementation-helper/batch/reccmp_report.py"] + list(args),
                          capture_output=True, text=True).stdout


names = [l.split()[2].split("::")[-1] for l in run("pct").split("\n")
         if l.strip() and l.split()[0] != "100.0" and len(l.split()) > 2]
lines = run("diff", *names).split("\n")

cur, src = None, {}
funcs = []
for i, l in enumerate(lines):
    if l.startswith("###"):
        cur = l.split("::")[-1].split()[0]
    funcs.append(cur)
    m = re.search(r"cpp:(\d+)", l)
    src[i] = m.group(1) if m else None


def nearest_src(i):
    for j in range(i, min(i + 6, len(lines))):
        if src.get(j):
            return src[j]
    return "?"


hits = {}


def add(kind, i, text):
    hits.setdefault(funcs[i], []).append("%-9s @%-5s %s" % (kind, nearest_src(i), text))


for i, l in enumerate(lines):
    m = JCC.match(l)
    if m and m.group(1) == "-":
        for j in range(i + 1, min(i + 4, len(lines))):
            m2 = JCC.match(lines[j])
            if not m2 or m2.group(1) != "+":
                continue
            if INV.get(m.group(2)) == m2.group(2):
                add("INVERTED", j, "%s -> %s" % (m.group(2), m2.group(2)))
            elif {m.group(2), m2.group(2)} in SIGN:
                add("SIGNED", j, "%s / %s" % (m.group(2), m2.group(2)))
            break
    if re.match(r"^-movsx \w+, word ptr", l):
        nxt = " ".join(lines[i + 1:i + 4])
        if "+movzx" in nxt and "movsx" in nxt:
            add("WIDTH", i, l.strip()[:48])

pend = []
for i, l in enumerate(lines):
    m = NUM.match(l)
    if m:
        pend.append((i, m.group(1), int(m.group(3), 0)))
for k in range(len(pend) - 1):
    (i, s1, v1), (j, s2, v2) = pend[k], pend[k + 1]
    if funcs[i] == funcs[j] and s1 == "-" and s2 == "+" and v1 != v2 and abs(v1 - v2) <= 4:
        add("CONST", j, "orig %s vs ours %s" % (hex(v1), hex(v2)))

prev = None
for i, l in enumerate(lines):
    if l.startswith("###"):
        prev = None
        continue
    m = OPS.match(l)
    if not m:
        continue
    if prev and prev[1] == "-" and m.group(1) == "+" and (prev[2] == m.group(3) or prev[3] == m.group(2)) \
            and (prev[2], prev[3]) != (m.group(2), m.group(3)):
        add("OPERANDS", i, "orig %s,%s | ours %s,%s" % (prev[2][:14], prev[3][:14], m.group(2)[:14], m.group(3)[:14]))
    prev = (i,) + m.groups()

for k in sorted(hits, key=lambda x: -len(hits[x])):
    print("%s  (%d)" % (k, len(hits[k])))
    for t in hits[k][:6]:
        print("    " + t)
