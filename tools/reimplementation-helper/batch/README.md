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
| `build_quiet.py [--keep-going]` | `build.bat RelWithDebInfo OpenSHC.dll`, prints only errors and `BUILD_OK`/`BUILD_FAIL` (build.bat exits 0 even on errors). Retries once on a PDB server error, see the note below. |
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
| `diff_types.py [--run] [NAME]` | The non-comparison counterpart of `diff_jcc.py`: `movsx` against `movzx` for the same field (its signedness is wrong in the generated header), `add` against `sub` with the same magnitude (a sign error in a formula - how `2400/n + 40` was caught being `- 40`). It pairs only equal-length runs inside one reccmp block, so it stays quiet once the streams drift: it reports nothing across the 101 functions of `Game::GameStateStructures` and fires on both bugs when they are reintroduced. |
| `quick_diff.py FILE.cpp... [-q]` | Compile one file with `/FA` and diff it against the original function disassembled straight from `_original/` - about 6 seconds, no link and no reccmp, so a dozen source variants can be tried in the time of one build. Shows the whole original function, which reccmp's diff does not when ours is shorter. A triage loop: confirm a 1.0 with `reccmp_report.py --run`. |
| `reorder_search.py FILE NAME [--pairs] [--dry]` | Hill-climb the match % by reordering independent statements: permute runs of >=3 by default, or swap every adjacent independent pair with `--pairs`. Builds once per move and reverts anything that does not improve. |

### Choosing what to work on

| Script | Purpose |
|---|---|
| `rank_functions.py [filter] [--top N]` | Rank by source lines x (1 - match), so the big badly-matching functions come first instead of the small ones with a low percentage. |
| `scan_dispatch.py [filter]` | Functions whose dispatch form disagrees with the original (jump table on one side, if/else-if chain on the other), and which way to fix each. |
| `scan_chains.py [filter] [--min N]` | `if/else if` chains comparing one expression against several constants: the candidates to convert when `scan_dispatch.py` says the original has a table we do not. |
| `try_styles.py FUNC [style...]` | Compile and measure several hand-written variants of one function, restore the winner, print the table. Variants live in `build-RelWithDebInfo/batch/variants/FUNC/*.cpp`. |

### Readability passes

These undo decompiler artefacts. Each measured as code-generation neutral or better where
it was applied, but none is guaranteed to be -- re-measure after running one.

| Script | Purpose |
|---|---|
| `declare_at_use.py [filter]` | Move the leading declaration block down to each variable's first use, and drop declarations that are never used. Only moves one when the first assignment provably dominates every later use. |
| `decast.py [filter]` | Collapse doubled casts, `(int)((int)(x))` -> `(int)(x)`. Skips `(int)((int)X + Y)`, where the inner cast covers one operand and dropping it would move the conversion onto the sum. |
| `deparen.py [filter] [--apply]` | Drop redundant brackets from `if`/`while` conditions using C precedence. Keeps the load-bearing ones (`(a \|\| b) && c`, `(x & 7) == 0`, assignments and comma operators inside conditions). Dry run unless `--apply`. |
| `test_deparen.py` | Precedence tests for `deparen.py`. Run after touching its table: an earlier version silently rewrote `(a != 0 \|\| b != 0) && (x & 0x100) == 0` into a different expression that still compiled. |
| `undiv.py [filter] [--apply]` | Turn MSVC's biased shift for a signed power-of-two division back into a division: `(x + (x >> 0x1f & 7U)) >> 3` -> `x / 8`. Dry run unless `--apply`. Usually a large gain rather than merely neutral: over one namespace it was worth up to 22% on a single function. |
| `test_undiv.py` | Cases for `undiv.py`, including the near-misses it must leave alone: a shift disagreeing with the mask, a mask that is not 2^k - 1, and a bias taken from another variable. |
| `unmod.py [filter] [--apply]` | The same for a signed power-of-two remainder: `v = x & 0x8000000f;` plus the negative-case repair is `v = x % 16`. Forces a signed dividend, because the repair only exists for a signed operand and an unsigned `%` compiles to a bare `and`. |
| `test_unmod.py` | Cases for `unmod.py`: a repair constant that does not complement the mask, a repair applied to another variable, and a bare mask with no repair. |
| `unptr.py [filter] [--apply]` | Replace the decompiler's field-walking pointers (`piVar1 = &x.f; *piVar1 = *piVar1 + 1;`) with the field itself. Only the two-adjacent-line shape, since a pointer freezes the address while the field form re-evaluates the index. Reports which pointers are still in use. |
| `test_unptr.py` | Cases for `unptr.py`, including a pointer declared on the spot (`char* pcVar3 = &...`, whose type prefix must go with it) and the set-up-then-use-later shape it must leave alone. |

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
- Every script that runs `cl.exe` sets this worktree's own `_MSPDBSRV_ENDPOINT_`
  (`common.build_env`), the same name `build.bat` derives. `mspdbsrv.exe` is a per-user
  singleton keyed on that endpoint and each worktree carries its own toolchain copy, so a
  shared endpoint makes `cl.exe` talk to the wrong server and fail with
  `fatal error C1090: PDB API call failed`.
- `build_quiet.py` and `syntax_check.py` both retry such a failure twice, because it has two
  causes. A wedged server survives the kill `build.bat` does up front, so the first retry stops
  this worktree's `mspdbsrv.exe` (`common.kill_pdb_server`, never other worktrees'). A wedged
  *endpoint* outlives every `mspdbsrv.exe` using it, so the second retry moves to a fresh name
  (`common.fresh_pdb_endpoint`) rather than retrying into one that will keep failing.
- In `syntax_check.py` a PDB failure is not just a lost run: the fatal line counts as an error
  against whichever file hit it and the rest of the batch still gets checked, so without the
  retries the output looks like a normal error list and hides the real compile errors.
