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
| `orig_asm.py NAME [--both\|--stats]` | The **original** instruction stream of one function (not the interleaved diff), in address order; `--stats` reports the tells that decide how to reimplement it: `mov reg, 0` (handwritten asm), frame pointer (built /Od), frame size, jump tables. |
| `show_functions.py PREFIX [--skip-100]` | Print function bodies under `src/OpenSHC/PREFIX` with their percentages, in the block format `splice_functions.py` reads. |
| `splice_functions.py BLOCKS.txt` | Replace many function bodies at once (keeps the `// FUNCTION:` line, can add includes/usings), then clang-format. |
| `commit_progress_batch.py PREFIX... [Name=remark]` | One `reimplement:` commit per changed function with its status line, like `commit_progress`. |
| `fix_func_refs.py [--drop-include H]` | After a header refactor: rewrite `X_Func::name` references whose resolver moved to another namespace. |
| `move_to_resolver_namespace.py FILE...` | After a header refactor: re-wrap a definition in its resolver's new namespace and `git mv` it to the matching folder. |

Analysis helpers, for deciding *what* to change when a function is stuck below 100%:

| Script | Purpose |
|---|---|
| `diff_triage.py [--run] [filter]` | One line per function: match %, raw and register/slot-normalized difflib ratios, `sub esp` frame size per side, byte-sized `[esp]` accesses per side, `ret` placement. Flags `FRAME` / `BYTE` / `RET` / `alloc-only`. |
| `diff_slots.py NAME` | Every `[esp + N]` slot with its access count on each side, and the slots only we use. Run after `diff_triage.py` reports `FRAME`. |
| `diff_jcc.py [NAME]` | Comparisons whose operator is one strictness step off the original (`jl`/`jle`, `jg`/`jge`, `ja`/`jae`) or whose `cmp` operands are the other way round, with context. |
| `reorder_search.py FILE NAME [--pairs] [--dry]` | Hill-climb the match % by reordering independent statements: permute runs of >=3 by default, or swap every adjacent independent pair with `--pairs`. Builds once per move and reverts anything that does not improve. |

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

## Reading `diff_triage.py`

The two ratios are the quickest way to tell whether more source work can pay:

- `norm` much higher than `raw` - only register and stack-slot *naming* differs.
  The allocator is not reachable from the source; record the reason and move on.
- `norm` still low - real structure or ordering differs; keep looking.
- `FRAME` - one local too many or too few. Chase it with `diff_slots.py`; this has
  been worth 10-30 points (a redundant Ghidra temp, or two copies of a parameter
  where the original introduced fresh locals instead of reassigning it).
- `BYTE` - we have byte-sized stack slots the original does not: every `bool`/`byte`
  local is an `int` in the original.
- `RET` - we inline a cold early-return block the original places out of line.
  Restructure so the cold case is last in the source (`if (ok) { body } else { reset }`
  rather than a guard at the top), which is what makes MSVC outline it.

Confirm a `diff_jcc.py` fix by re-running that tool and checking the pair is gone,
not by the percentage: a single instruction moves the score by ~0.1 and tells you
nothing, while three such fixes in one namespace turned out to be real off-by-one
bugs that Ghidra had decompiled wrongly.

## Notes

- `normalized 100%` means only call-target differences remain. `commit_progress_batch.py`
  records such functions as `100% Reimplemented`.
- A file whose `// FUNCTION:` address has no reccmp entry is reported as `--` / skipped.
  Check the address against `src/precomp/addresses-SHC-3BB0A8C1.hpp`.
- Sources are always written as UTF-8 with LF line endings.
