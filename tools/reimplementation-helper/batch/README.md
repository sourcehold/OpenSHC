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
| `orig_asm.py NAME [--both\|--stats]` | The **original** instruction stream of one function (not the interleaved diff), in address order; `--stats` reports the tells that decide how to reimplement it: `mov reg, 0` (handwritten asm), frame pointer, frame size, jump tables. |
| `show_functions.py PREFIX [--skip-100]` | Print function bodies under `src/OpenSHC/PREFIX` with their percentages, in the block format `splice_functions.py` reads. |
| `splice_functions.py BLOCKS.txt` | Replace many function bodies at once (keeps the `// FUNCTION:` line, can add includes/usings), then clang-format. |
| `commit_progress_batch.py PREFIX... [Name=remark]` | One `reimplement:` commit per changed function with its status line, like `commit_progress`. |
| `enable_local_functions.py [--disable]` | Set the `MACRO_FUNCTION_RESOLVER` flag to `true` for exactly the .cpp files in the build list, so calls between them land in our own code. `/GL` buys nothing without this - LTCG cannot see a callee it does not compile (`getSalesPrice` 68.4% -> 100%). The repository-wide `Enable-Reimplemented-Functions.ps1` flips every resolver that has a .cpp anywhere in the tree, which does not link while the list is a subset. Never committed, like the `Globals` flags. |
| `fix_func_refs.py [--drop-include H]` | After a header refactor: rewrite `X_Func::name` references whose resolver moved to another namespace. |
| `move_to_resolver_namespace.py FILE...` | After a header refactor: re-wrap a definition in its resolver's new namespace and `git mv` it to the matching folder. |

Analysis helpers, for deciding *what* to change when a function is stuck below 100%:

| Script | Purpose |
|---|---|
| `diff_triage.py [--run] [filter]` | One line per function: match %, raw and register/slot-normalized difflib ratios, `sub esp` frame size per side, byte-sized `[esp]` accesses per side, `ret` placement. Flags `FRAME` / `BYTE` / `RET` / `alloc-only`. |
| `diff_slots.py NAME` | Every `[esp + N]` slot with its access count on each side, and the slots only we use. Run after `diff_triage.py` reports `FRAME`. |
| `diff_jcc.py [NAME]` | Comparisons whose operator is one strictness step off the original (`jl`/`jle`, `jg`/`jge`, `ja`/`jae`) or whose `cmp` operands are the other way round, with context. |
| `diff_types.py [--run] [NAME]` | The non-comparison counterpart of `diff_jcc.py`: `movsx` against `movzx` for the same field (its signedness is wrong in the generated header), `add` against `sub` with the same magnitude (a sign error in a formula - how `2400/n + 40` was caught being `- 40`). It pairs only equal-length runs inside one reccmp block, so it stays quiet once the streams drift: it reports nothing across the 101 functions of `Game::GameStateStructures` and fires on both bugs when they are reintroduced. |
| `diff_anchor.py [--run] [NAME]` | Functions whose struct/loop base anchor differs from the original's (`lea esi, [ecx + 0x367e4]` against a different constant). Every displacement in the function then differs while the opcodes still line up, which reads as allocator noise - it is the whole gap between 83.7% and 61.7% on `processFoodConsumption`. The delta is the distance between the two fields MSVC chose; the decompilation names the original's as the pointer it starts the loop with. |
| `diff_lea.py [--run] [NAME]` | `lea reg, [a + b]` on our side where the original has the destructive `add a, b`: `field = snapshotLocal + delta` has to keep the snapshot, `field = field + delta` updates the cached read in place. Drop the local when nothing between the read and the use writes the field - that was `updatePopularity`'s last 6.1%. `RLEA` is the reverse, a local the original keeps and we do not. |
| `diff_signed.py [NAME-SUBSTRING]` | Comparisons the original makes signed and we make unsigned (or the reverse): `jg/jge/jl/jle` against our `ja/jae/jb/jbe` over the same `cmp`. Fix it by comparing through `(int)` in the source, not by editing the generated header, and re-run the tool to confirm - one instruction barely moves the percentage. |
| `quick_diff.py FILE.cpp... [-q]` | Compile one file with `/FA` and diff it against the original function disassembled straight from `_original/` - about 6 seconds, no link and no reccmp, so a dozen source variants can be tried in the time of one build. Shows the whole original function, which reccmp's diff does not when ours is shorter. A triage loop: confirm a 1.0 with `reccmp_report.py --run`, and do not trust a *rise* of its ratio below about 0.6 - on a badly matching function difflib rewards a different alignment, and one such "gain" was a 10-point loss in reccmp. |
| `push_pattern.py FILE.cpp...` | Per call, the argument-push run as `pushes/interleaved` for both sides. A neat run (`0` interleaved) means every argument was already in a register or slot, i.e. the source had a **local**; a mixed run is what writing the expression inline at the call produces. A starred row is a call where the two sides disagree - add the local, or drop it, accordingly. Counts only calls whose set-up it can see, so a differing call *total* means our source has an extra call (a duplicated block), not that the tool failed. |
| `perm_decls.py FILE FIRST LAST` | Permute one short run of declarations and keep the order that matches best, scored by `quick_diff.py -s`. MSVC assigns stack slots in declaration order, so two locals declared the wrong way round sit in each other's slots and usually in each other's registers - `assignSelectionToKey` 95.9% -> 100% from one swapped line. Find the candidates with `diff_slots.py`: same slot count, different use count per slot. |
| `reorder_search.py FILE NAME [--pairs] [--dry]` | Hill-climb the match % by reordering independent statements: permute runs of >=3 by default, or swap every adjacent independent pair with `--pairs`. Builds once per move and reverts anything that does not improve. |
| `quick_reorder.py FILE START END [START END ...] [-s]` | The same hill-climb scored by `quick_diff.py` instead of a build, so a trial takes seconds: every statement of each named block (from the line containing START up to the line containing END) is tried at every other position, and only strict ratio gains are kept. With `-s` stack offsets count, which makes **declaration order** visible - it took `AICState::selectAttackTarget` 68.8% -> 100% and `smallestTribeOfUnitType` 57% -> 96% with two or three moves each. It does not check data dependencies (a use before a declaration fails to compile and is rejected, a store moved across a read is not), so give it blocks of declarations and pure `return` guards and read `git diff` afterwards. Set `QD_OUT` per run to run several in parallel, and let them finish before a full build (shared PDB, C1033). |

### Choosing what to work on

| Script | Purpose |
|---|---|
| `rank_functions.py [filter] [--top N]` | Rank by source lines x (1 - match), so the big badly-matching functions come first instead of the small ones with a low percentage. |
| `scan_dispatch.py [filter]` | Functions whose dispatch form disagrees with the original (jump table on one side, if/else-if chain on the other), and which way to fix each. |
| `scan_chains.py [filter] [--min N]` | `if/else if` chains comparing one expression against several constants: the candidates to convert when `scan_dispatch.py` says the original has a table we do not. |
| `quick_styles.py FUNC [-s] [style...]` | `try_styles.py` scored by `quick_diff.py` instead of a build: about a second per variant against roughly half a minute for an incremental build plus a reccmp run, so a dozen source forms cost less than one build cycle. Same variant directory (`build-RelWithDebInfo/batch/variants/FUNC/*.cpp`), same table, same winner-restore; `-s` keeps `[esp + N]` offsets, for declaration order. It never touches the source list or the DLL, so it leaves no stale `diff.json` behind. The score is difflib's ratio, not the reccmp percentage - rank the forms here, then confirm the winner with `reccmp_report.py --run`, and mind `quick_diff`'s warning about ratio rises below about 0.6. |
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
| `undirwalk.py [filter] [--apply]` | Turn the two pointers Ghidra walks in lockstep over `clockwiseCardinalTranslationMatrix` and a row of `directionTranslationMatrix` back into `for (int _direction = 0; _direction < 8; ...)`. Derives the direction count and stride from the pointer steps and the absolute end address, and refuses when the row index is reassigned inside the body (that pointer froze the *initial* row) or when either pointer survives the rewrite. |
| `undirwalk4.py [filter] [--apply]` | The four-at-a-time variant of the same neighbour loops, including the ones that already carry the direction index and the set-ups `clang-format` wrapped across lines. Matches either set-up order and guards the row index. |
| `unoffset_matrix.py [filter] [--apply]` | Resolve hand-computed byte offsets into the same matrix, `*(short*)((int)matrix + i * 8 + 0xc)` -> `matrix[i + 1].short_.yOffset`. Code-generation neutral; it only removes magic numbers. |
| `unguarded_do.py [filter] [--apply]` | Collapse `if (cond) { do { ... } while (cond); }` into `while (cond) { ... }`. Usually neutral, but **measure**: where the original really did compile a do-while this has cost up to 22% on one function, so re-run `reccmp_report.py cmp` and revert per file. |
| `docount.py [filter] [--apply]` | Counted `i = 0; do { ... i = i + 1; } while (i < N);` -> `for (int i = 0; i < N; i = i + 1)`. Only when the counter is stepped by the last statement, written nowhere else, and not read after the loop. |
| `early_return.py [filter] [--apply]` | Turn a function whose body is one big `if (bounds guard) { ... } return X;` into `if (!guard) { return X; } ...`. Inverts a top-level `&&` chain of simple comparisons by De Morgan and bails on anything else. Measured code-generation neutral across 20 functions; it is a readability change. |

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
