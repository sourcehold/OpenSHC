# How tunnels change the ground

Digging changes the ground around a tunnel, not just the tile directly above it.
The game stores both the current height and the original terrain height. Tunnel
cleanup does not simply copy the original height back: it lowers a small area and
then sets the center tile to zero. This can leave a different result from the
terrain before digging, especially where several digging steps overlap or the
original ground is raised.

These are observations about the original game. Restoring the original height
would be a gameplay correction, not a faithful reconstruction of this behavior.

## Digging and cleanup

`UpdateTunneler` calls `increaseHeightForTunnelSingleTile` with an increment of one
at digging timer values 6, 12 and 18. At the next digging step (24), it calls
`increaseHeightForTunnelWithBrush`, also with an increment of one. The brush uses
`getTileForBrush` to visit nine tiles. Clearing only the center therefore misses
part of the ground changed by digging.

`UnitsState::applyTunnelDamageAlongPathPlan` walks the stored tunnel path. It skips
tiles matching the logic mask `0x20000081`. On the remaining tiles:

- If there is no building and either the current or original height is below 16,
  it calls the same brush with an increment of **minus two**. It then writes
  **zero** to the center tile's current height.
- Otherwise, it calls the game's building-damage routine.
- It then calls `updateWalkAndPathLayer` for that path position.

The brush retains its own exclusions. A center tile reaching this branch does
not imply every surrounding tile will be changed.

Conversely, digging with a building on the center can still raise its eligible
neighbours. The cleanup caller skips that brush call when its center has a
building, so those neighbours can be missed. The path walker is also called from
the building-damage code at `0x0051751B` and `0x00517F0A` when handling a tunneler;
it is not exclusive to normal tunnel completion.

## What the brush does

For each of its nine positions, the brush skips tiles with a building or any of
these logic masks: `0x10000500`, `0xB1` and `0x60300000`. On other tiles it changes
the height only if either height is below 16 and adding the signed increment
would not produce a negative result. The actual height write is a byte addition.

For eligible positions it also updates path linkages in all eight directions,
even when the height test prevents the addition. After the loop, it calls
`updateWalkAndPathLayer` with a brush size of five. Replacing the height write
alone does not reproduce these path updates.

The height arrays also represent wall height. A general terrain reset must not
be mistaken for the game's wall-damage or building-removal operation. In
particular, the brush's exclusions and the cleanup caller's unconditional
center-zero write are different checks.

## Existing names and evidence

The names and member layouts already exist in `TileMapState.hpp`,
`TileMapState.func.hpp` and `Units/UnitsState.func.hpp`. No new names, generated
header changes or function implementations are introduced by this note.

| Existing function | SHC 1.41 reference address |
| --- | --- |
| `Units::UpdateTunneler` | `0x0054E6C0` |
| `UnitsState::applyTunnelDamageAlongPathPlan` | `0x00534130` |
| `TileMapState::increaseHeightForTunnelSingleTile` | `0x004F80E0` |
| `TileMapState::increaseHeightForTunnelWithBrush` | `0x00501CD0` |
| `TileMapState::getTileForBrush` | `0x004FBD80` |
| `PathFindingState::updatePathLinkagesInAllEightDirections` | `0x004A5F90` |
| `PathFindingState::updateWalkAndPathLayer` | `0x0049AAD0` |

At brush offset `+0x21` the native coordinate helper is called; `+0x31` through
`+0x4F` contain the exclusions; `+0x51` through `+0x72` contain the height logic;
`+0x84` and `+0xA6` call the path functions. The return is `ret 0x10` for the four
arguments `(tile, x, y, increment)` with the tile-map object in ECX. The cleanup
walk calls the brush at `+0x75` and writes zero at `+0x7A`.

The tile-map members are `HeightLayer` at `+0x29FA30`, `DefaultHeightLayer` at
`+0x2B3440`, `LogicLayer` at `+0x165160` and `BuildingLayer` at `+0x2029B0`.
These are structure offsets; the table above is reference-binary evidence,
not a runtime binding scheme for extensions.

Inspection used SHC SHA256
`3bb0a8c1e72331b3a30a5aa93ed94beca0081b476b04c1960e26d5b45387ac5a`.
The same brush and cleanup flow was checked in Extreme SHA256
`55648e6b05d67d37a5773fe699bbb17a2d6ad4de1bb9dbded9a21caef82bd7fb`,
where the brush is at `0x00502050` and the cleanup walk at `0x00534550`.
The two direct brush callers are digging and path cleanup in both binaries.

Native instruction tests executed the brush and its real coordinate helper in
Unicorn with synthetic terrain, recording downstream path calls rather than
executing full pathfinding. They confirmed the nine-tile footprint, unchanged
positive digging, and the difference between subtracting two and restoring the
original height. This is not an in-game rendering, editor, replay or performance
test, and no C++ implementation or reccmp match is claimed.
