"""Report deviations from REIMPLEMENTATION_STYLE_GUIDE.md in reimplemented .cpp files.

This is an advisory reader, not a gate. The guide's overriding rule is that the
match comes first, so a deviation is often deliberate: the ugly form is the one
that matched. Every finding here is a question ("is this one of those?"), never
an instruction, and rule 21 is the answer when it is -- leave a comment saying
what was measured.

Only mechanically decidable rules are implemented. Rules that need a judgement
about what a value means (6 const, 12 strings beyond the obvious, 16 naming
quality, 18 which enum) are either left out or reported as a plain count.
clang-format (rule 0) is already enforced by cpp-linter and is not repeated.

Usage:
    python -I tools/reimplementation-helper/style_lint.py FILE.cpp [FILE.cpp ...]
    python -I tools/reimplementation-helper/style_lint.py --from-stdin < filelist

Options:
    --markdown PATH   write a markdown report (default: stdout text only)
    --max-per-rule N  findings listed per rule in the markdown (default 10)

Exit status is 0 unless the tool itself failed: a deviation is not an error.
"""

import os, re, sys

GUIDE = 'REIMPLEMENTATION_STYLE_GUIDE.md'
# a relative link does not resolve inside a PR comment, so CI passes the blob URL
GUIDE_URL = os.environ.get('GUIDE_URL', GUIDE)

# Ghidra's invented names (rule 16). Deliberately anchored on the decompiler's
# own prefixes, so a hand-written name is never flagged for looking short.
DECOMP_NAME = re.compile(
    r'\b(?:[a-z]{0,3}(?:Var|Stack)\d+'
    r'|local_[0-9a-fA-F]+'
    r'|(?:in|unaff|extraout)_[A-Za-z0-9_]+'
    r'|LAB_[0-9a-fA-F]+'
    r'|(?:DAT|UNK|FUN|SUB)_[0-9a-fA-F]{6,})\b'
)
STRING_LIT = re.compile(r'"(?:[^"\\\n]|\\.)*"')
CHAR_LIT = re.compile(r"'(?:[^'\\\n]|\\.)*'")


def strip_block_comments(text):
    """Blank out /* ... */ while keeping every newline, so line numbers hold."""
    return re.sub(r'/\*.*?\*/', lambda m: re.sub(r'[^\n]', ' ', m.group(0)), text, flags=re.S)


def strip_noise(line):
    """Blank out comments and literals so a pattern cannot match inside them."""
    line = re.sub(r'//.*$', '', line)
    line = STRING_LIT.sub('""', line)
    line = CHAR_LIT.sub("''", line)
    return line


def function_close_indent(lines):
    """-> indent of the function's own closing brace, by the file's own shape.

    Files sit in two nested namespaces, so the function body is indented 8 and
    its closing brace 4. Rather than assume that, read it off the line after the
    '// FUNCTION:' marker.
    """
    for i, line in enumerate(lines):
        if '// FUNCTION:' in line:
            return len(line) - len(line.lstrip())
    return 4


def check_file(path, text):
    """-> [(rule, line_no, message)] for one file."""
    out = []
    lines = text.splitlines()
    code = [strip_noise(l) for l in strip_block_comments(text).splitlines()]
    base = os.path.basename(path)
    stem = base[:-4] if base.endswith('.cpp') else base
    fn_indent = function_close_indent(lines)
    body_indent = ' ' * (fn_indent + 4)
    close_brace = ' ' * fn_indent + '}'

    # --- rule 1: the decompiler's trailing return; -------------------------
    # Only the function's own: a return; at body indent whose next code line is
    # the function's closing brace. An early return sits deeper or is followed
    # by more statements.
    for i, line in enumerate(code):
        if line.rstrip() != body_indent + 'return;':
            continue
        nxt = next((code[j] for j in range(i + 1, len(code)) if code[j].strip()), '')
        if nxt.rstrip() == close_brace:
            out.append((1, i + 1, 'trailing `return;` in a void function'))

    # --- rule 15: + -1 ------------------------------------------------------
    for i, line in enumerate(code):
        if re.search(r'[-+]\s*\+\s*-|\+\s*-\s*\d', line):
            out.append((15, i + 1, 'writes `+ -N`; the readable form is `- N`'))

    # --- rule 16: decompiler names -----------------------------------------
    names = {}
    for i, line in enumerate(code):
        for m in DECOMP_NAME.finditer(line):
            n = m.group(0)
            # DAT_ globals are this project's own naming for the real globals.
            if n.startswith('DAT_'):
                continue
            names.setdefault(n, i + 1)
    for n, ln in sorted(names.items(), key=lambda kv: kv[1]):
        out.append((16, ln, 'decompiler name `%s`' % n))

    # --- rule 9: while / do-while ------------------------------------------
    for i, line in enumerate(code):
        if re.search(r'\bdo\s*\{', line):
            out.append((9, i + 1, '`do`-loop; the guide asks for a `for`'))
        elif re.search(r'(^|[^\w.])while\s*\(', line) and '} while' not in line:
            out.append((9, i + 1, '`while`-loop; the guide asks for a `for`'))

    # --- no goto (AGENTS.md) -----------------------------------------------
    for i, line in enumerate(code):
        if re.search(r'\bgoto\b', line):
            out.append((20, i + 1, '`goto`; check how many predecessors the target has first'))

    # --- rule 11 / 18: magic addresses and hex constants -------------------
    # A big hex number is only an address if it is used like one. A literal
    # masked with &, |, ^ or ~ is a bit flag however large it is, and belongs
    # to rule 18 (give it its name) rather than rule 11.
    for i, line in enumerate(code):
        if '// FUNCTION:' in lines[i]:
            continue
        masked = re.search(r'[&|^~]', line) is not None
        for m in re.finditer(r'\b0x([0-9a-fA-F]+)\b', line):
            v = int(m.group(1), 16)
            if v <= 0xFF:
                continue
            single_bit = v != 0 and (v & (v - 1)) == 0
            # An address in this project is written out in full, as the eight
            # digits of 0x00EE0FE8. Six digits of 0xffffff is a colour, and
            # value alone cannot tell the two apart.
            spelled_as_address = len(m.group(1)) == 8
            if 0x400000 <= v and spelled_as_address and not masked and not single_bit:
                out.append((11, i + 1, 'literal address `0x%X`' % v))
            else:
                out.append((18, i + 1, 'hex constant `0x%X`; use a name, or decimal' % v))

    # --- rule 22: (uint) range trick ---------------------------------------
    for i, line in enumerate(code):
        if re.search(r'\((?:uint|unsigned int|uint32_t)\)\s*\([^()]*[-+][^()]*\)\s*[<>]', line):
            out.append((22, i + 1, 'unsigned range trick; spell the two bounds out'))

    # --- rule 2: cast on a returned comparison -----------------------------
    for i, line in enumerate(code):
        if re.search(r'\breturn\s*\((?:uint|int|BOOL|BOOLEnum)\)\s*\(.*(?:==|!=|<=|>=|<|>)', line):
            out.append((2, i + 1, 'cast on a returned comparison'))

    # --- rule 23: ternary ---------------------------------------------------
    for i, line in enumerate(code):
        if '?' in line and ':' in line.split('?', 1)[1]:
            out.append((23, i + 1, 'ternary; the guide prefers extending the if-else chain'))

    # --- rule 8 / 10: a for-loop stepping by more than one -----------------
    for i, line in enumerate(code):
        m = re.search(r'\bfor\s*\(.*;.*;\s*\w+\s*\+=\s*([2-9])\s*\)', line)
        if m:
            out.append((8, i + 1, 'loop steps by %s; try the plain loop and let MSVC unroll' % m.group(1)))

    # --- rule 24: a declaration with no initialiser ------------------------
    # Two legitimate forms are not deviations and are excluded: an out-param,
    # whose address is taken, and a value assigned in every arm of an if-else
    # chain, which cannot be folded into its declaration at all. What is left
    # is the declare-then-assign-once shape rule 24 is actually about.
    for i, line in enumerate(code):
        m = re.match(r'\s*(?:int|short|char|long|uint|ushort|byte|float|double|BOOLEnum)\s+(\w+)\s*;\s*$', line)
        if not m:
            continue
        name = m.group(1)
        if re.search(r'&\s*%s\b' % re.escape(name), text):
            continue
        stores = sum(
            len(re.findall(r'\b%s\s*=(?!=)' % re.escape(name), c)) for j, c in enumerate(code) if j != i
        )
        if stores == 1:
            out.append((24, i + 1, 'declare `%s` where it is first assigned' % name))

    # --- rule 14: the first include is your own class ----------------------
    # The folder is the class (rule 13), so that is what the first include has
    # to name. Both the '../Class.hpp' and the full 'OpenSHC/.../Class.hpp'
    # spelling are accepted: 325 files on main use the latter, so treating it
    # as a deviation would be reporting the project's own habit back at it.
    own_class = os.path.basename(os.path.dirname(path))
    first = next((l for l in lines if l.lstrip().startswith('#include')), None)
    if first is not None and own_class:
        want = ('/%s.hpp"' % own_class, '/%s.func.hpp"' % own_class,
                '"%s.hpp"' % own_class, '"%s.func.hpp"' % own_class)
        if not any(w in first for w in want):
            out.append((14, lines.index(first) + 1,
                        'first include is not `%s`; the folder is the class' % own_class))

    # --- rule 13: one function per file, named after the file --------------
    markers = [i for i, l in enumerate(lines) if '// FUNCTION:' in l]
    defined = []
    for i in markers:
        sig = ' '.join(lines[i + 1 : i + 3])
        m = re.search(r'(?:[A-Za-z_]\w*::)*([A-Za-z_~]\w*)\s*\(', sig)
        if m:
            defined.append((i + 2, m.group(1)))
    if defined and not any(n == stem or n.startswith(stem + '_') or stem.startswith(n + '_') for _, n in defined):
        out.append((13, defined[0][0], 'none of %s matches the file name `%s`'
                    % (', '.join('`%s`' % n for _, n in defined), stem)))

    out.sort(key=lambda f: (f[1], f[0]))
    return out


RULE_TITLES = {
    1: 'Drop the decompiler trailing `return;`',
    2: 'No cast on a returned comparison',
    8: 'Let the compiler unroll',
    9: 'Prefer `for` over `while`/`do`',
    11: 'No magic addresses',
    13: 'One function per file, named after it',
    14: 'The shape of a file',
    15: 'Write `- 1`, not `+ -1`',
    16: 'Give variables a name that says what they hold',
    18: 'Use the name, not the number',
    20: 'Keep nesting low; no `goto`',
    22: 'Prefer descriptive code',
    23: 'Prefer if-else over ternary',
    24: 'Declare variables upon first use',
}


def markdown(findings_by_file, max_per_rule, checked):
    by_rule = {}
    for path, findings in findings_by_file.items():
        for rule, ln, msg in findings:
            by_rule.setdefault(rule, []).append((path, ln, msg))
    total = sum(len(v) for v in by_rule.values())

    lines = ['<!-- style-lint -->', '**Style guide reading** (advisory, posted once)', '']
    if not total:
        lines.append(
            'Nothing to report: the %d reimplemented `.cpp` file(s) in this PR show no mechanically '
            'detectable deviation from [%s](%s).' % (checked, GUIDE, GUIDE_URL)
        )
        lines.append('')
        return '\n'.join(lines)

    lines.append(
        '%d possible deviation(s) from [%s](%s) across %d of the %d reimplemented `.cpp` file(s) '
        'in this PR.' % (total, GUIDE, GUIDE_URL, len(findings_by_file), checked)
    )
    lines.append('')
    lines.append(
        '**The match comes first.** Where the ugly form is what matched, it stays -- that is the '
        'guide\'s own overriding rule, and rule 21 asks for a one-line comment saying what was '
        'measured so the next reader does not retry it. This report is posted once, when the PR '
        'opens, and is not repeated on later pushes.'
    )
    lines.append('')
    lines.append('| rule | what it asks | hits |')
    lines.append('| --- | --- | --- |')
    for rule in sorted(by_rule):
        lines.append('| %d | %s | %d |' % (rule, RULE_TITLES.get(rule, '?'), len(by_rule[rule])))
    lines.append('')
    lines.append('<details><summary>Where</summary>')
    lines.append('')
    for rule in sorted(by_rule):
        hits = by_rule[rule]
        lines.append('**Rule %d — %s**' % (rule, RULE_TITLES.get(rule, '?')))
        lines.append('')
        for path, ln, msg in hits[:max_per_rule]:
            lines.append('- `%s:%d` — %s' % (path, ln, msg))
        if len(hits) > max_per_rule:
            lines.append('- _... and %d more_' % (len(hits) - max_per_rule))
        lines.append('')
    lines.append('</details>')
    lines.append('')
    return '\n'.join(lines)


def main(argv):
    max_per_rule = 10
    md_path = None
    paths = []
    i = 0
    while i < len(argv):
        a = argv[i]
        if a == '--markdown':
            i += 1
            md_path = argv[i]
        elif a == '--max-per-rule':
            i += 1
            max_per_rule = int(argv[i])
        elif a == '--from-stdin':
            paths.extend(p.strip() for p in sys.stdin.read().split() if p.strip())
        else:
            paths.append(a)
        i += 1

    # Only reimplemented sources are in scope: generated headers are not.
    paths = [p.replace('\\', '/') for p in paths]
    paths = [p for p in paths if p.endswith('.cpp') and p.startswith('src/OpenSHC/')]

    findings_by_file = {}
    for p in sorted(set(paths)):
        if not os.path.exists(p):
            continue
        text = open(p, encoding='utf-8', errors='replace').read()
        f = check_file(p, text)
        if f:
            findings_by_file[p] = f

    total = sum(len(v) for v in findings_by_file.values())
    print('files checked: %d' % len(paths))
    print('files with findings: %d' % len(findings_by_file))
    print('findings=%d' % total)
    for p in sorted(findings_by_file):
        for rule, ln, msg in findings_by_file[p]:
            print('  %s:%d rule %d: %s' % (p, ln, rule, msg))

    if md_path:
        with open(md_path, 'w', encoding='utf-8', newline='\n') as f:
            f.write(markdown(findings_by_file, max_per_rule, len(paths)))
        print('wrote %s' % md_path)
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
