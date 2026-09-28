#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
         * Finds an appropriate location for placing a siege tent near a target position.    * Uses breadth-first search
         * (BFS) to explore tiles radiating outward from the starting position.    *     * @param this -
         * PathFindingState object pointer    * @param distance? - Maximum search distance (typically 100 or 200 tiles)
         * * @param x - Starting X coordinate (0-399)    * @param y - Starting Y coordinate (0-399)    * @param
         * selectionID - ID for selected unit/object (unused in function body)    * @param requiredDistanceFromAIZone -
         * Exact match required for AI zone tactical distance if   nonzero    * @param playerID - Current player's ID
         * * @return Tile index of valid siege tent location, or 0 if none found      decompilerscript: committed:
         * 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049F7D0
        dword PathFindingState::findAppropriateLocationForSiegeTent(
            int distanceUnk, uint x, uint y, undefined4 selectionID, uint requiredDistanceFromAIZone, int playerID)
        {
            int* piVar4;
            int iVar5;
            int iVar6;
            dword _offsetTile;
            uint uVar7;
            uint uVar8;
            int local_c;
            int _tile;
            /*
              === INITIAL VALIDATION ===   Check if coordinates are within map bounds (400x400) and if the tile is
              walkable
             */
            if (399 < x || 399 < y || *(char*)(y * 400 + 0x21aec98 + x) == '\0') {
                /*
                  Invalid position - out of bounds or unwalkable
                 */
                return (dword)(0);
            }
            /*
              === PATHFINDING STATE INITIALIZATION ===   Increment calculation counter (for profiling/debugging)
             */
            this->calculations = this->calculations + 1;
            /*
              Increment the "active flag" value used to mark visited tiles this search   iteration
             */
            this->searchGeneration = this->searchGeneration + 1;
            /*
              If flag value exceeds 32000, reset to 1 and clear the entire WalkLayer   This prevents overflow and avoids
              having to clear the layer every search
             */
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                /*
                  Clear 160800 bytes 80400 short values
                 */
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    160800, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            /*
              === BFS QUEUE INITIALIZATION ===   Initialize BFS queue indices      Current tile being processed
             */
            this->searchQueue.readIndex = 0;
            /*
              Next free slot in queue
             */
            this->searchQueue.writeIndex = 1;
            /*
              Starting distance
             */
            this->searchQueue.currentDistance = 1;
            /*
              Add starting position to queue
             */
            this->searchQueue.yQueue[0] = (short)y;
            /*
              Convert 2D coordinates to 1D tile index
             */
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            /*
              Mark starting tile with distance 1
             */
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            /*
              Mark as visited with current active flag value
             */
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            /*
              === MAIN BFS LOOP ===   Continue while there are tiles in the queue to process
             */
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while ((_tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                    -1 < _tile && (_tile < 0x13a10))) {
                    /*
                      Get Y coordinate of current tile being processed
                     */
                    short sVar1 = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    /*
                      Get distance from start for current tile
                     */
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                    /*
                      Safety check: if distance exceeds max tile count, abort
                     */
                    if (80400 < this->searchQueue.currentDistance) {
                        return (dword)(0);
                    }
                    /*
                      If we've exceeded search radius, stop searching
                     */
                    if (distanceUnk < this->searchQueue.currentDistance) {
                        return (dword)(0);
                    }
                    /*
                      === EXPLORE 8 ADJACENT TILES ===   Check all 8 cardinal/diagonal directions from current tile
                     */
                    y = 0;
                    do {
                        /*
                          Check if movement is possible in this direction (using bitflag for direction   y)   Check if
                          adjacent tile hasn't been visited this iteration
                         */
                        if ((DAT_TileMapState::instance.PathLinkageLayer[_tile]
                                & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[y])
                                != 0
                            && (_offsetTile = DAT_TileMapState::instance.directionTranslationMatrix[sVar1][y] + _tile,
                                DAT_TileMapState::instance.WalkLayer[_offsetTile] != this->searchGeneration)) {
                            bool bVar2 = true;
                            /*
                              === AI Zone DISTANCE CHECK ===   If specified (i.e. not 0), then the strategic distance of
                              the current tile   must be exactly that value
                             */
                            if (requiredDistanceFromAIZone != 0
                                && (bVar2 = true,
                                    *(byte*)(*(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray
                                                 + playerID * 0x177bc + -0x10)
                                            * 0x13a10
                                        + 0x1ee2998 + _offsetTile)
                                        != requiredDistanceFromAIZone)) {
                                bVar2 = false;
                            }
                            /*
                              === SIEGE TENT PLACEMENT VALIDATION ===   Only check for valid placement if distance > 4
                              (minimum spacing requirement)
                             */
                            if (4 < this->searchQueue.currentDistance
                                && DAT_TileMapState::instance.UnitLayer[_offsetTile] == 0 && bVar2) {
                                /*
                                  Get height of candidate tile
                                 */
                                uVar7 = (uint)DAT_TileMapState::instance.HeightLayer[_offsetTile];
                                iVar6 = 0;
                                local_c = 0;
                                /*
                                  Get pointer to movement direction offsets for checking surrounding tiles   Track
                                  minimum height in surrounding area
                                 */
                                piVar4 = DAT_TileMapState::instance
                                             .directionTranslationMatrix[*(int*)((int)DAT_TerrainDefinedData::instance
                                                                                     .clockwiseCardinalTranslationMatrix
                                                                             + y * 8 + 4)
                                                 + (int)sVar1]
                                    + 1;
                                x = uVar7;
                                /*
                                  === CHECK 8 SURROUNDING TILES FOR TENT PLACEMENT ===   Loop checks tiles in groups of
                                  4 for optimization
                                 */
                                do {
                                    /*
                                      Check first tile in group
                                     */
                                    iVar5 = (*(int (*)[8])(piVar4 + -1))[0] + _offsetTile;
                                    /*
                                      Disqualify if tile has: impassable terrain, units, or buildings   0x4a7014b1
                                      checks for: sea, border, border_edge, rocky, building,    tree, river, ford,
                                      crenel wall impassible, farm field hop tree,    farm field dairy fence, moat, farm
                                     */
                                    if ((DAT_TileMapState::instance.LogicLayer[iVar5] & 0x4a7014b1U) != 0
                                        || (DAT_TileMapState::instance.LogicLayer[iVar5] & 4U) != 0
                                        || DAT_TileMapState::instance.UnitLayer[iVar5] != 0
                                        || DAT_TileMapState::instance.BuildingLayer[iVar5] != 0)
                                        break;
                                    /*
                                      Track height variation (for flatness check)
                                     */
                                    uint uVar3 = (uint)DAT_TileMapState::instance.HeightLayer[iVar5];
                                    uVar8 = uVar3;
                                    if ((uVar3 <= uVar7) && (uVar8 = uVar7, uVar3 < x)) {
                                        /*
                                          Update minimum height
                                         */
                                        x = uVar3;
                                    }
                                    uVar7 = uVar8;
                                    /*
                                      Update maximum height   Repeat checks for tiles 2, 3, and 4 in the group (Pattern
                                      repeats with piVar4[0], piVar4[1], piVar4[2])   Each tile checks: LogicLayer,
                                      UnitLayer, BuildingLayer, HeightLayer
                                     */
                                    iVar5 = *piVar4 + _offsetTile;
                                    if ((DAT_TileMapState::instance.LogicLayer[iVar5] & 0x4a7014b1U) != 0
                                        || (DAT_TileMapState::instance.LogicLayer[iVar5] & 4U) != 0
                                        || DAT_TileMapState::instance.UnitLayer[iVar5] != 0
                                        || DAT_TileMapState::instance.BuildingLayer[iVar5] != 0) {
                                        iVar6 = iVar6 + 1;
                                        break;
                                    }
                                    uVar3 = (uint)DAT_TileMapState::instance.HeightLayer[iVar5];
                                    uVar8 = uVar3;
                                    if ((uVar3 <= uVar7) && (uVar8 = uVar7, uVar3 < x)) {
                                        x = uVar3;
                                    }
                                    uVar7 = uVar8;
                                    iVar5 = piVar4[1] + _offsetTile;
                                    if ((DAT_TileMapState::instance.LogicLayer[iVar5] & 0x4a7014b1U) != 0
                                        || (DAT_TileMapState::instance.LogicLayer[iVar5] & 4U) != 0
                                        || DAT_TileMapState::instance.UnitLayer[iVar5] != 0
                                        || DAT_TileMapState::instance.BuildingLayer[iVar5] != 0) {
                                        iVar6 = iVar6 + 2;
                                        break;
                                    }
                                    uVar3 = (uint)DAT_TileMapState::instance.HeightLayer[iVar5];
                                    uVar8 = uVar3;
                                    if ((uVar3 <= uVar7) && (uVar8 = uVar7, uVar3 < x)) {
                                        x = uVar3;
                                    }
                                    iVar5 = piVar4[2] + _offsetTile;
                                    if ((DAT_TileMapState::instance.LogicLayer[iVar5] & 0x4a7014b1U) != 0
                                        || (DAT_TileMapState::instance.LogicLayer[iVar5] & 4U) != 0
                                        || DAT_TileMapState::instance.UnitLayer[iVar5] != 0
                                        || DAT_TileMapState::instance.BuildingLayer[iVar5] != 0) {
                                        iVar6 = iVar6 + 3;
                                        uVar7 = uVar8;
                                        break;
                                    }
                                    uVar3 = (uint)DAT_TileMapState::instance.HeightLayer[iVar5];
                                    uVar7 = uVar3;
                                    if ((uVar3 <= uVar8) && (uVar7 = uVar8, uVar3 < x)) {
                                        x = uVar3;
                                    }
                                    local_c = local_c + 4;
                                    piVar4 = piVar4 + 4;
                                    iVar6 = iVar6 + 4;
                                } while (local_c < 8);
                                /*
                                  === FINAL VALIDATION ===   If all 8 surrounding tiles are clear (iVar6 == 8)   AND
                                  terrain is relatively flat (height difference < 12)
                                 */
                                if (iVar6 == 8 && (int)(uVar7 - x) < 0xc) {
                                    /*
                                      FOUND VALID LOCATION!
                                     */
                                    return (dword)(_offsetTile);
                                }
                            }
                            /*
                              === ADD TILE TO BFS QUEUE ===   Mark this tile's distance (current distance + 1)
                             */
                            DAT_TileMapState::instance.CertainPathLayer[_offsetTile]
                                = (short)this->searchQueue.currentDistance + 1;
                            /*
                              Mark as visited
                             */
                            DAT_TileMapState::instance.WalkLayer[_offsetTile] = (short)this->searchGeneration;
                            /*
                              Add Y coordinate to queue
                             */
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                      + y * 8 + 4)
                                + sVar1;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _offsetTile;
                            /*
                              Increment queue write position
                             */
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (80400 < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        /*
                          Move to next direction
                         */
                        y = y + 1;
                        /*
                           Process all 8 directions
                         */
                    } while ((int)y < 8);
                    /*
                      === ADVANCE TO NEXT TILE IN QUEUE ===
                     */
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (80400 < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    /*
                      Check if queue is empty (read position caught up to write position)
                     */
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                        return (dword)(0);
                    }
                }
            }
            /*
              No valid location found
             */
            return (dword)(0);
        }

    }
}
}
