# Native synchronization checks

These checks compare the compiled C++ implementations with the original
Crusader and Extreme 1.41 instructions without opening a game process.

Select these three implementations in `cmake/openshc-sources.txt.local` using
the project's local development workflow, then build `OpenSHC.dll` with
MSVC 2005 SP1 and the normal optimized configuration:

```text
src/OpenSHC/Synchrony/GameSynchronyState/checkGameSync.cpp
src/OpenSHC/Synchrony/GameSynchronyState/sendPeriodicSyncMessages.cpp
src/OpenSHC/Synchrony/GameSynchronyState/computeSomeHashOnUnitArray.cpp
```

Install the development Python dependencies `pefile`, `capstone` and `unicorn`,
then run:

```text
python tools/validation/check_native_sync.py GAME_DIRECTORY build-RelWithDebInfo/CMakeFiles/OpenSHC.dll.dir/src/OpenSHC/Synchrony/GameSynchronyState
```

`GAME_DIRECTORY` must contain both supported original executables; their SHA256
identities are checked first. No game assets or proprietary executable bytes are
included in this repository.

The checker reads actual COFF function code and relocation records, binds
resolvers to their native addresses, and compares all 397/91/21 function bytes.
It also executes each original and compiled routine in isolated x86 emulation:

- 2,376 host-check cases per variant exercise peer identity/exclusion, missing
  or early samples, equal/different advertised ticks and hashes, pending resync,
  countdowns and independent receiver/global objects.
- 2,304 periodic-message cases per variant exercise signed 32-bit elapsed-time
  comparisons, 180/1800ms thresholds, clock wrap and send callbacks changing
  the second timer or countdown.
- Ten unit-buffer hash cases per variant verify the delegated address, length,
  receiver, return value and calling convention.

All 9,380 cases compare calls and non-stack memory writes and check stack and
callee-saved register preservation. Only the clock, packet delivery and delegated
buffer-hash function are stand-ins; this does not validate transport, hash
generation, resync completion or a full replay. The unit-buffer helper hashes the
entire unit array; it is distinct from the canonical per-domain multiplayer hash
calculation, which excludes selected transient fields.

Extreme checks translate the verified later `GameSynchronyState` offsets,
resolver addresses and the fourfold unit-array capacity before comparison.
This is evidence against the Extreme native routines, not an Extreme OpenSHC
DLL build or a change to the project's generated layouts.

Native-bound function bytes and the linked DLL's `reccmp` percentage are separate
results: resolver indirections and symbol matching remain in the actual DLL.
