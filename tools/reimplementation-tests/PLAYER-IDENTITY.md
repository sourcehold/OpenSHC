# Player-handle translation

`GameSynchronyState::translateMultiplayerIDsIntoPlayerIDs` resolves a transport
handle to the logical player that owns a command. It is called both during
selection/sorting and immediately before native dispatch. Replaying the raw
handle through ordinary single-player dispatch therefore executes as the local
player, regardless of the recorded actor.

The source preserves the original behavior:

- Modes 0 and 99 return the receiver's local slot without examining the handle.
- Other modes scan slots 1 through 8; slot 0 is ignored.
- A missing handle returns zero. Duplicate handles return the highest matching
  slot, including sentinel values. This routine itself does not validate a roster.
- It does not mutate game state and preserves ECX, which native callers reuse.

The addresses are `0x47EAF0` in Crusader and `0x47ECC0` in Extreme. Original
instructions use ECX-relative state, not the fixed globals suggested by Ghidra's
decompiler. Both variants use mode offset `0x618` and handles at `0x6A8`; the
local-slot offsets are `0x109E74` and `0x166304` respectively. The OpenSHC source
uses its existing Crusader structure layout; the checker populates each native
variant's own layout for comparison.

## Reproduce

From a checkout with the project's toolchain/dependencies initialized:

```powershell
$taskRoot = (Get-Location).Path
$taskMsvc = Join-Path $taskRoot 'MSVC1400-SP1'
$env:PATH = "$taskMsvc/Common7/IDE;$taskMsvc/VC/bin;$env:PATH"
$env:INCLUDE = "$taskMsvc/VC/include;$taskMsvc/VC/PlatformSDK/Include"
New-Item -ItemType Directory -Force tmp | Out-Null
& "$taskMsvc/VC/bin/cl.exe" /nologo /c /O2 /EHsc /DOPEN_SHC_DLL `
  /I "$taskRoot/src" /I "$taskRoot/dependencies/ucp3/include" `
  /I "$taskRoot/dependencies/lua/include" /I "$taskRoot/dependencies/DXSDK_Aug2007/include" `
  /FI "$taskRoot/src/precomp/pch.h" /Fotmp/playerIdentity.obj `
  src/OpenSHC/Synchrony/GameSynchronyState/translateMultiplayerIDsIntoPlayerIDs.cpp
if ($LASTEXITCODE -ne 0) { throw 'Compilation failed' }
python -m pip install pefile unicorn==2.1.4
python tools/reimplementation-tests/player_identity.py tmp/playerIdentity.obj 'PATH/Stronghold Crusader.exe'
python tools/reimplementation-tests/player_identity.py tmp/playerIdentity.obj 'PATH/Stronghold_Crusader_Extreme.exe'
```

The checker requires the known original executable SHA-256, compares the actual
compiled source and native routine against an independent last-match model, and
checks receiver relocation, missing/duplicate/sentinel handles, all slots,
single-player/end-of-game modes, memory read/write bounds and stack/register
behavior. Use Python 3.10+ without `-O`.

This is readable C++03 with no generated-header or resolver changes. MSVC emits
137 bytes, the same size as the original, but places the single-player return
block differently. Exact-byte matching, a linked-DLL reccmp score and live
multiplayer behavior are not claimed. The contribution supplies a verified
native identity primitive; it does not enable multiplayer replay.
