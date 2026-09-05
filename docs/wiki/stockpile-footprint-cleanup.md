# Stockpile footprint cleanup

`TileMapState::clearStockpileFootprintTiles` at `0x004FAF70` clears the nine
walkable tiles belonging to a stockpile. The four building parts are handled
elsewhere. This implementation preserves original behavior; it does not remove
starting stockpiles or change human/AI placement policy.

For each entry in `TerrainDefinedData::StockpilePathableOffsets`, it:

1. Clears only logic bits `0x102`.
2. Restores the tile's default height.
3. Reads `noRubble` from the building indexed by `AlphaGFXLayer`, before clearing
   that index. Zero clears `BuildingWasLayer`; nonzero sets `MiscDisplayLayer`
   bit `0x4000` and preserves `BuildingWasLayer`.
4. Clears `AlphaGFXLayer`.

The map layers use the member-function receiver (`ECX`), not a fixed global
`TileMapState`. Building metadata, terrain offsets and row translation use the
existing global resolvers. No generated headers or resolver flags are changed.

## Evidence and verification

Reference: Gynt's named OpenSHC Ghidra database, cross-checked against native
Stronghold Crusader 1.41 assembly. Executable SHA-256:
`3bb0a8c1e72331b3a30a5aa93ed94beca0081b476b04c1960e26d5b45387ac5a`.

Compiled with MSVC 14.00.50727.762 (VS2005 SP1), x86, `/O2 /Ob1 /MT /EHsc`,
`OPEN_SHC_DLL`, `REIMPLEMENTED_CRT=0`, and the project's forced `precomp/pch.h`.
The resulting function is **325 bytes, byte-identical to the original after
resolving its eight global-symbol relocations**. The compiler reproduces the
original three-way loop unrolling from the nine-iteration C++ loop.

`tools/verification/verify_stockpile_cleanup.py` accepts the compiled COFF object
and a user-supplied original executable:

```text
python -m pip install pefile capstone unicorn
python tools/verification/verify_stockpile_cleanup.py cleanup.obj "Stronghold Crusader.exe"
```

It verifies the original executable hash, resolves the object relocations,
checks exact instruction bytes, and emulates both implementations across 32
deterministic randomized whole-map states. Cases cover zero/nonzero building
indices, both rubble branches, varied coordinates, and both original and
relocated receiver addresses. It compares all `0x554A88` receiver bytes and
checks stack cleanup and callee-saved registers. All checks pass.

This is function-level compilation and emulation, not a full DLL link or live
gameplay test. Local development can include the new source through
`cmake/openshc-sources.txt.local` using the existing repository workflow.

## Related keep-placement finding

The investigation began with Ascension PR #30, which replaces two bytes at
Extreme file offset `0x115136` with `EB 0F`. In the checked Extreme executable
(SHA-256 `55648e6b05d67d37a5773fe699bbb17a2d6ad4de1bb9dbded9a21caef82bd7fb`),
this jumps from VA `0x00515136` to `0x00515147`, skipping the seven argument
pushes and the `placeStockpile` call at `0x00515142` to `0x005088C0`.
The equivalent standard Crusader block is `0x00514DB6` through `0x00514DC7`,
calling `placeStockpile` at `0x00508540` from `placeKeep` (`0x005146D0`).
There is no human/AI filter in that block. These offsets are executable-specific.

The stockpile branch in `checkBuildingCanBePlacedHere` (`0x005037B0`) uses
the supplied owner ID to read the player's stockpile entry. An absent entry
does not require adjacency; an existing entry requires capacity and an
adjacent owned stockpile. Earlier terrain and placement checks still apply.
`AIVState::aiPlaceAIVBuilding` (`0x004ED410`) uses the shared building-placement
path. These observations do not establish that removing AI starting
stockpiles is safe.
