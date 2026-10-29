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
         * * @param ySpace - Starting X coordinate (0-399)    * @param y - Starting Y coordinate (0-399)    * @param
         * selectionID - ID for selected unit/object (unused in function body)    * @param requiredDistanceFromAIZone -
         * Exact match required for AI zone tactical distance if   nonzero    * @param playerID - Current player's ID
         * * @return Tile index of valid siege tent location, or 0 if none found      decompilerscript: committed:
         * 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049F7D0
        dword PathFindingState::findAppropriateLocationForSiegeTent(
            int distanceUnk, uint ySpace, uint y, undefined4 selectionID, uint requiredDistanceFromAIZone, int playerID)
        {
            /*
              === INITIAL VALIDATION ===   Check if coordinates are within map bounds (400x400) and if the tileUnk is
              walkable
             */
            if (399 < ySpace || 399 < y || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + ySpace] == '\0') {
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
              If flag value exceeds 32000, reset to 1 and clear the entire WalkLayer   This prevents underflow and avoids
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
              === BFS QUEUE INITIALIZATION ===   Initialize BFS queue indices      Current tileUnk being processed
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
              Convert 2D coordinates to 1D tileUnk index
             */
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + ySpace;
            /*
              Mark starting tileUnk with distance 1
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
                do {
                    int _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if (_tile < 0 || _tile >= 80400) {
                        return (dword)(0);
                    }
                    /*
                      Y coordinate and distance from start of the current tileUnk
                     */
                    int _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = DAT_TileMapState::instance.CertainPathLayer[_tile];
                    /*
                      Safety check, then stop once the search radius is exceeded
                     */
                    if ((int)this->searchQueue.currentDistance > 80400) { // 0x49F8D5 signed jg
                        return (dword)(0);
                    }
                    if ((int)this->searchQueue.currentDistance > distanceUnk) { // 0x49F8EA signed jg (diffemu 2026-10-16)
                        return (dword)(0);
                    }
                    /*
                      === EXPLORE 8 ADJACENT TILES ===
                     */
                    for (int _direction = 0; _direction < 8; _direction++) {
                        if ((DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction]
                                & DAT_TileMapState::instance.PathLinkageLayer[_tile])
                            == 0)
                            continue;
                        dword _offsetTile = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[_offsetTile] == this->searchGeneration)
                            continue;
                        /*
                          === AI Zone DISTANCE CHECK ===   If specified (i.e. not 0), then the strategic distance of
                          the current tileUnk must be exactly that value
                         */
                        int _zoneOk = 1;
                        if (requiredDistanceFromAIZone != 0
                            && *(byte*)(*(int*)(((int)&DAT_TroopValueState::instance.attackInfo + 0x301d0 /* old hackValuesArray: AttackInfoSubElement of player p at +0x301C0 + p*0x177BC */)
                                                + playerID * 0x177bc + -0x10)
                                           * 0x13a10
                                       + 0x1ee2998 + _offsetTile)
                                != requiredDistanceFromAIZone) {
                            _zoneOk = 0;
                        }
                        /*
                          === SIEGE TENT PLACEMENT VALIDATION ===   Only beyond distance 4, on a tileUnk without units
                         */
                        if ((int)this->searchQueue.currentDistance > 4 && DAT_TileMapState::instance.UnitLayer[_offsetTile] == 0
                            && _zoneOk) {
                            /*
                              All 8 surrounding tiles must be free (no impassable terrain 0x4a7014b1 / 4, units or
                              buildings) and the terrain flat (high spread < 12)
                             */
                            int _maxHeight = DAT_TileMapState::instance.HeightLayer[_offsetTile];
                            int _minHeight = _maxHeight;
                            int _row = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.yOffset + _y;
                            int _free = 0;
                            for (int _around = 0; _around < 8; _around++) {
                                int _neighbour
                                    = DAT_TileMapState::instance.directionTranslationMatrix[_row][_around] + _offsetTile;
                                if ((DAT_TileMapState::instance.LogicLayer[_neighbour] & 0x4a7014b1) != 0
                                    || (DAT_TileMapState::instance.LogicLayer[_neighbour] & 4) != 0
                                    || DAT_TileMapState::instance.UnitLayer[_neighbour] != 0
                                    || DAT_TileMapState::instance.BuildingLayer[_neighbour] != 0)
                                    break;
                                int _height = DAT_TileMapState::instance.HeightLayer[_neighbour];
                                if (_height > _maxHeight) {
                                    _maxHeight = _height;
                                } else if (_height < _minHeight) {
                                    _minHeight = _height;
                                }
                                _free = _free + 1;
                            }
                            if (_free == 8 && _maxHeight - _minHeight < 12) {
                                /*
                                  FOUND VALID LOCATION!
                                 */
                                return _offsetTile;
                            }
                        }
                        /*
                          === ADD TILE TO BFS QUEUE ===
                         */
                        DAT_TileMapState::instance.CertainPathLayer[_offsetTile]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[_offsetTile] = (short)this->searchGeneration;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset
                            + (short)_y;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _offsetTile;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if ((int)this->searchQueue.writeIndex >= 80400) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                    /*
                      === ADVANCE TO NEXT TILE IN QUEUE ===
                     */
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if ((int)this->searchQueue.readIndex >= 80400) {
                        this->searchQueue.readIndex = 0;
                    }
                } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            }            /*
              No valid location found
             */
            return (dword)(0);
        }

    }
}
}
