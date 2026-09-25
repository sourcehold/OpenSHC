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
| `original_asm.py NAME [--jumptable]` | Disassemble a function in the original exe, or print the case values per switch body in body order. Takes a function name or an address. |
| `jump_table_order.py [--apply] [NAME...]` | Compare a state `switch` with the original's jump table and put the cases in the order the original emits their bodies. |
| `compare_constants.py [NAME...]` | Diff the sequence of `cmp` constants (original vs ours) per function: shows wrong literals, missing checks and blocks in the wrong order. |
| `fix_off_by_one.py [--apply] [NAME...]` | Rewrite comparisons whose literal is one off from the original's (`> 31` -> `>= 32`). |
| `diff_reasons.py [--context N] [NAME...]` | Per function: where the assembly *first* really diverges, its source line and a guess at why. Skips differences that are only registers, call targets or prologue housekeeping. |

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

## Chasing a difference that is not register allocation

Once the obvious rewrites are done, most of what is left in a diff is LTCG register
allocation, which the source cannot control. These three find the differences that it can:

```sh
python diff_reasons.py                           # which functions are worth opening at all
python jump_table_order.py Map/Units             # cases in the original's body order?
python compare_constants.py UpdateMiner          # which literals/checks differ, and where
python fix_off_by_one.py --apply Map/Units       # > 31 -> >= 32 and friends
python original_asm.py UpdateMiner | less        # read the original when in doubt
```

`jump_table_order.py` is worth running over any state machine written before this was
understood: MSVC emits jump-table case bodies in source order, so cases in the wrong order
cap the match (Deer 37 -> 65%, Rabbit 70 -> 79%, Ladderman 25 -> 37%).

`original_asm.py` and `jump_table_order.py` read `_original/Stronghold Crusader.exe`
directly and need `capstone` (`pip install capstone`); the other two read
`reccmp/dll/diff.json`, so run reccmp first.

## Notes

- `normalized 100%` means only call-target differences remain. `commit_progress_batch.py`
  records such functions as `100% Reimplemented`.
- A file whose `// FUNCTION:` address has no reccmp entry is reported as `--` / skipped.
  Check the address against `src/precomp/addresses-SHC-3BB0A8C1.hpp`.
- A low match % on its own is not a reason to work on a function. Diffs cascade, so one
  differing instruction makes everything after it count as different; `diff_reasons.py`
  exists to tell a real difference from that tail. Most of what is left across Map/Units is
  LTCG register allocation and instruction scheduling, which the source cannot reach.
- Only jump-table *body* order is evidence of source order. The order of `cmp` instructions
  in an if-chain is not: MSVC reorders side-effect-free compares, and matching it by hand
  made UpdateChild 8 points worse.
- `short` locals used as an array index compile to `movzx` plus a separate sign-extend where
  the original has a single `movsx`; `int` matches. State locals must stay 16 bit
  (`UnitStateShort`), or the compares widen.
- `fix_off_by_one.py` is not always an improvement: the register allocator sometimes keeps
  the old literal in a register and reuses it. Rebuild, `reccmp_report.py cmp BASE.json`
  and revert the functions that got worse.
- Sources are always written as UTF-8 with LF line endings.
