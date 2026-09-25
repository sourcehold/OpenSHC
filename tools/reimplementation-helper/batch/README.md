# Batch reimplementation helpers

Scripts for working on many functions at once: everything listed in
`cmake/openshc-sources.txt.local`. They were written for a style pass over ~350 functions
and complement the openshc-mcp tools (same build, reccmp and commit commands, but with
compact output and one run covering the whole list).

Run them from anywhere with Python 3; they `chdir` to the repository root. Scratch
output goes to `build-RelWithDebInfo/batch/` (git-ignored). A recent `clang-format`
(`pip install clang-format`, or set `CLANG_FORMAT`) is needed for the scripts that
rewrite sources, because the Visual Studio bundled one is too old for `.clang-format`.

| Script | Purpose |
|---|---|
| `build_quiet.py [--keep-going]` | `build.bat RelWithDebInfo OpenSHC.dll`, prints only errors and `BUILD_OK`/`BUILD_FAIL` (build.bat exits 0 even on errors). |
| `syntax_check.py [substr...]` | `cl /Zs` every (matching) list file serially; finds all compile errors in one pass without linking. |
| `reccmp_report.py [--run] pct\|save\|cmp\|diff` | Match % and *normalized* % (call/tail-jump targets and resolver addresses ignored) per function, snapshots, before/after comparison, compact asm diffs. |
| `show_functions.py PREFIX [--skip-100]` | Print function bodies under `src/OpenSHC/PREFIX` with their percentages, in the block format `splice_functions.py` reads. |
| `splice_functions.py BLOCKS.txt` | Replace many function bodies at once (keeps the `// FUNCTION:` line, can add includes/usings), then clang-format. |
| `commit_progress_batch.py PREFIX... [Name=remark]` | One `reimplement:` commit per changed function with its status line, like `commit_progress`. |
| `fix_func_refs.py [--drop-include H]` | After a header refactor: rewrite `X_Func::name` references whose resolver moved to another namespace. |
| `move_to_resolver_namespace.py FILE...` | After a header refactor: re-wrap a definition in its resolver's new namespace and `git mv` it to the matching folder. |

## Typical loop

```sh
python build_quiet.py && python reccmp_report.py --run save base.json   # baseline
python show_functions.py Map/Units > work.txt                            # edit the bodies in work.txt
python splice_functions.py work.txt
python syntax_check.py Map/Units
python build_quiet.py && python reccmp_report.py --run cmp base.json Map/Units
python reccmp_report.py diff someFunction                                # inspect what still differs
python commit_progress_batch.py Map/Units "someFunction=LTCG ecx reuse"
```

## Notes

- `normalized 100%` means only call-target differences remain. `commit_progress_batch.py`
  records such functions as `100% Reimplemented`.
- A file whose `// FUNCTION:` address has no reccmp entry is reported as `--` / skipped.
  Check the address against `src/precomp/addresses-SHC-3BB0A8C1.hpp`.
- Sources are always written as UTF-8 with LF line endings.
