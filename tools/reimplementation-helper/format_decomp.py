#!/usr/bin/env python3
"""
format_decomp.py — pre-clang-format cleanup for decompiled OpenSHC sources.

Applies three mechanical transforms that clang-format cannot do on its own:

  1. comments : remove decompiler noise blocks, i.e. block comments whose first
                non-whitespace content is `WARNING:` or `decompilerscript:`.
                Genuine documentation comments are left untouched.
  2. includes : rewrite relative includes ("../X.func.hpp", "..\\X.func.hpp") to
                fully-qualified project paths ("OpenSHC/.../X.func.hpp"), resolved
                against the file's real location in the tree.
  3. returns  : drop a lone trailing `return;` from a void body (the redundant
                one right before the closing braces).

Then run clang-format separately to handle indentation, wrapping, and braces:

    clang-format -i $(git ls-files '*.cpp')

Safety notes:
  * Only double-quoted, dot-relative includes are rewritten; <...> and already
    "OpenSHC/..."-rooted includes are left alone.
  * A bare `return;` is only removed when it is the last statement before the
    file's final run of closing braces, so meaningful early returns inside `if`
    blocks are never touched. This assumes one function per file (true for the
    per-function generated sources); with multiple functions per file only the
    last function's trailing return would be handled — never an incorrect edit.
  * `return <expr>;` is never matched, so value-returning functions are safe.
  * Files are only rewritten when their content actually changes.
"""

from __future__ import annotations

import argparse
import os
import re
import sys

# ---------------------------------------------------------------------------
# 1. Remove decompiler noise comment blocks
# ---------------------------------------------------------------------------

# Matches a /* ... */ block whose content STARTS with WARNING: or
# decompilerscript: (after the /* and any whitespace/newlines). The leading
# anchor is what keeps real docs — which start with prose — safe.
_NOISE_BLOCK = re.compile(
    r'[ \t]*/\*\s*(?:WARNING:|decompilerscript:|added by script:).*?\*/[ \t]*\n?',
    re.DOTALL,
)

def strip_noise_comments(text: str) -> str:
    return _NOISE_BLOCK.sub('', text)


# ---------------------------------------------------------------------------
# 2. Normalize relative includes to fully-qualified OpenSHC/... paths
# ---------------------------------------------------------------------------

_REL_INCLUDE = re.compile(r'^([ \t]*#include[ \t]+")([^"]+)("[ \t]*)$', re.MULTILINE)


def _include_root_for(file_abspath: str) -> str | None:
    """Return the directory that the 'OpenSHC/...' include paths are rooted at,
    i.e. the parent of the FIRST 'OpenSHC' segment in the file's path."""
    parts = os.path.normpath(file_abspath).split(os.sep)
    try:
        idx = parts.index('OpenSHC')
    except ValueError:
        return None
    root = os.sep.join(parts[:idx])
    return root if root else os.sep


def fix_includes(text: str, file_abspath: str) -> tuple[str, list[str]]:
    warnings: list[str] = []
    include_root = _include_root_for(file_abspath)
    current_dir = os.path.dirname(os.path.abspath(file_abspath))

    def repl(m: re.Match) -> str:
        pre, path, post = m.group(1), m.group(2), m.group(3)
        norm = path.replace('\\', '/')
        # Only touch dot-relative includes; leave rooted/system ones alone.
        if not (norm.startswith('./') or norm.startswith('../')):
            return m.group(0)
        if include_root is None:
            warnings.append(f'no OpenSHC root in path; left as-is: {path}')
            return m.group(0)
        target = os.path.normpath(os.path.join(current_dir, norm))
        rel = os.path.relpath(target, include_root).replace(os.sep, '/')
        if not rel.startswith('OpenSHC/'):
            warnings.append(f'resolved outside OpenSHC/, left as-is: {path} -> {rel}')
            return m.group(0)
        return f'{pre}{rel}{post}'

    return _REL_INCLUDE.sub(repl, text), warnings


# ---------------------------------------------------------------------------
# 3. Drop a lone trailing `return;` from a void body
# ---------------------------------------------------------------------------

_BARE_RETURN = re.compile(r'^[ \t]*return;[ \t]*\n', re.MULTILINE)
_ONLY_CLOSERS = re.compile(r'[\s}]*\Z')  # whitespace and closing braces only


def drop_trailing_void_return(text: str) -> str:
    matches = list(_BARE_RETURN.finditer(text))
    if not matches:
        return text
    last = matches[-1]
    # Remove only if nothing but closing braces / whitespace follows it, so
    # early returns (which have code after them) are never removed.
    if _ONLY_CLOSERS.fullmatch(text, last.end()):
        return text[:last.start()] + text[last.end():]
    return text


# ---------------------------------------------------------------------------
# Whitespace tidy (safe subset of what clang-format will also enforce)
# ---------------------------------------------------------------------------

def tidy_whitespace(text: str) -> str:
    text = re.sub(r'[ \t]+\n', '\n', text)      # strip trailing spaces
    text = re.sub(r'\n{3,}', '\n\n', text)      # collapse 2+ blank lines -> 1
    text = re.sub(r'(\))\n\n+(\s*\{)', r'\1\n\2', text) # Remove whitespace between signature and {
    return text.rstrip('\n') + '\n'             # exactly one final newline


# ---------------------------------------------------------------------------
# Driver
# ---------------------------------------------------------------------------

TRANSFORMS = ('comments', 'includes', 'returns', 'tidy')


def process(text: str, path: str, only: set[str]) -> tuple[str, list[str]]:
    warnings: list[str] = []
    if 'comments' in only:
        text = strip_noise_comments(text)
    if 'includes' in only:
        text, w = fix_includes(text, path)
        warnings += w
    if 'returns' in only:
        text = drop_trailing_void_return(text)
    if 'tidy' in only:
        text = tidy_whitespace(text)
    return text, warnings


def iter_files(roots: list[str], exts: tuple[str, ...]):
    for root in roots:
        if os.path.isfile(root):
            yield root
            continue
        for dirpath, _, names in os.walk(root):
            for name in names:
                if name.endswith(exts):
                    yield os.path.join(dirpath, name)


def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('paths', nargs='+', help='files or directories to process')
    ap.add_argument('--ext', default='.cpp',
                    help='comma-separated file extensions (default: .cpp)')
    ap.add_argument('--only', default=','.join(TRANSFORMS),
                    help=f'subset of transforms to run: {",".join(TRANSFORMS)}')
    ap.add_argument('--dry-run', action='store_true',
                    help='report what would change without writing')
    args = ap.parse_args(argv)

    exts = tuple(e if e.startswith('.') else '.' + e
                 for e in args.ext.split(','))
    only = {t.strip() for t in args.only.split(',') if t.strip()}
    bad = only - set(TRANSFORMS)
    if bad:
        ap.error(f'unknown transform(s): {", ".join(sorted(bad))}')

    changed = scanned = 0
    for path in iter_files(args.paths, exts):
        scanned += 1
        with open(path, 'r', encoding='utf-8', newline='\n') as fh:
            original = fh.read()
        new, warnings = process(original, path, only)
        for w in warnings:
            print(f'  ! {path}: {w}', file=sys.stderr)
        if new != original:
            changed += 1
            print(('would change ' if args.dry_run else 'changed ') + path)
            if not args.dry_run:
                with open(path, 'w', encoding='utf-8', newline='\n') as fh:
                    fh.write(new)

    print(f'\n{scanned} scanned, {changed} '
          + ('would change' if args.dry_run else 'changed'))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())