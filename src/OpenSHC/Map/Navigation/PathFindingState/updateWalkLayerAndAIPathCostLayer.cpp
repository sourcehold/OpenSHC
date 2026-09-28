#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
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
         * Updates the WalkLayer and AI Path Cost Layer using breadth-first search (BFS).    * This creates a distance
         * map showing how far each tile is from AI zones.    * The distance values are stored in the same layer that
         * param_5 checks in the siege tent   function.    *     * @param this - PathFindingState object pointer    *
         * @param param_1 - Maximum distance to calculate (distance limit)    * @param param_2 - Target distance for
         * candidate collection (0 = don't collect)    * @param param_3 - Area/zone ID for navigation check    * @param
         * playerID - Current player's ID      decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A7090
        void PathFindingState::updateWalkLayerAndAIPathCostLayer(
            int limit, uint borderDistance, dword fromArea, int playerID)
        {
            short sVar1;
            int _tile;
            int _canNav;
            int iVar2;
            short* psVar3;
            int (*paiVar4)[8];
            uint _tile2;
            /*
              === PATHFINDING STATE INITIALIZATION ===   Increment active flag value for this search iteration
             */
            this->searchGeneration = this->searchGeneration + 1;
            /*
              Reset flag and clear WalkLayer if exceeding threshold
             */
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    160800, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            /*
              === INITIALIZE BFS QUEUE ===
             */
            _tile = 0;
            /*
              Starting distance
             */
            this->searchQueue.currentDistance = 1;
            /*
              Read position
             */
            this->searchQueue.readIndex = 0;
            /*
              Write position (empty queue)
             */
            this->searchQueue.writeIndex = 0;
            /*
              Track maximum distance found
             */
            this->distance = 0;
            do {
                /*
                  === SEED QUEUE WITH ALL AI ZONE TILES ===   Scan entire map (80400 tiles) and add all tiles marked as
                  AI zones (value 1)   This is the "multi-source BFS" starting point   Processing in batches of 5 tiles
                  for optimization      Check tile at offset _tile
                 */
                if (DAT_TileMapState::instance.AIZoneLayer[_tile] == 1) {
                    /*
                      Get Y coordinate for this tile
                     */
                    this->searchQueue.yQueue[this->searchQueue.writeIndex]
                        = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
                    /*
                      Add tile to queue
                     */
                    this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _tile;
                    /*
                      SET DISTANCE TO 1 FOR ALL AI ZONE TILES   This is the SAME data structure that param_5 checks in
                      the siege tent   function!
                     */
                    /*
                      // Sets to 1
                     */
                    *(char*)(*(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + playerID * 0x177bc
                                 + -0x10)
                            * 0x13a10
                        + 0x1ee2998 + this->searchQueue.tilesQueue[this->searchQueue.writeIndex])
                        = (char)this->searchQueue.currentDistance;
                    /*
                      Mark as visited
                     */
                    DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[this->searchQueue.writeIndex]]
                        = (short)this->searchGeneration;
                    /*
                      Increment queue write position
                     */
                    this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                    if (80400 < this->searchQueue.writeIndex) {
                        this->searchQueue.writeIndex = 0;
                    }
                }
                /*
                  Repeat exact same logic for tiles _tile+1, _tile+2, _tile+3, _tile+4   (Unrolled loop for performance
                  - checking 5 tiles per iteration)
                 */
                if (DAT_TileMapState::instance.AIZoneLayer[_tile + 1] == 1) {
                    this->searchQueue.yQueue[this->searchQueue.writeIndex]
                        = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile + 1];
                    this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _tile + 1;
                    *(char*)(*(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + playerID * 0x177bc
                                 + -0x10)
                            * 0x13a10
                        + 0x1ee2998 + this->searchQueue.tilesQueue[this->searchQueue.writeIndex])
                        = (char)this->searchQueue.currentDistance;
                    DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[this->searchQueue.writeIndex]]
                        = (short)this->searchGeneration;
                    this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                    if (80400 < this->searchQueue.writeIndex) {
                        this->searchQueue.writeIndex = 0;
                    }
                }
                if (DAT_TileMapState::instance.AIZoneLayer[_tile + 2] == 1) {
                    this->searchQueue.yQueue[this->searchQueue.writeIndex]
                        = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile + 2];
                    this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _tile + 2;
                    *(char*)(*(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + playerID * 0x177bc
                                 + -0x10)
                            * 0x13a10
                        + 0x1ee2998 + this->searchQueue.tilesQueue[this->searchQueue.writeIndex])
                        = (char)this->searchQueue.currentDistance;
                    DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[this->searchQueue.writeIndex]]
                        = (short)this->searchGeneration;
                    this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                    if (80400 < this->searchQueue.writeIndex) {
                        this->searchQueue.writeIndex = 0;
                    }
                }
                if (DAT_TileMapState::instance.AIZoneLayer[_tile + 3] == 1) {
                    this->searchQueue.yQueue[this->searchQueue.writeIndex]
                        = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile + 3];
                    this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _tile + 3;
                    *(char*)(*(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + playerID * 0x177bc
                                 + -0x10)
                            * 0x13a10
                        + 0x1ee2998 + this->searchQueue.tilesQueue[this->searchQueue.writeIndex])
                        = (char)this->searchQueue.currentDistance;
                    DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[this->searchQueue.writeIndex]]
                        = (short)this->searchGeneration;
                    this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                    if (80400 < this->searchQueue.writeIndex) {
                        this->searchQueue.writeIndex = 0;
                    }
                }
                if (DAT_TileMapState::instance.AIZoneLayer[_tile + 4] == 1) {
                    this->searchQueue.yQueue[this->searchQueue.writeIndex]
                        = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile + 4];
                    this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _tile + 4;
                    *(char*)(*(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + playerID * 0x177bc
                                 + -0x10)
                            * 0x13a10
                        + 0x1ee2998 + this->searchQueue.tilesQueue[this->searchQueue.writeIndex])
                        = (char)this->searchQueue.currentDistance;
                    DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[this->searchQueue.writeIndex]]
                        = (short)this->searchGeneration;
                    this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                    if (80400 < this->searchQueue.writeIndex) {
                        this->searchQueue.writeIndex = 0;
                    }
                }
                /*
                  Process all 80400 tiles (entire map)
                 */
                _tile = _tile + 5;
            } while (_tile < 80400);
            /*
              === MAIN BFS LOOP ===   Expand outward from all AI zone tiles, calculating distances
             */
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                do {
                    /*
                      Get current tile from queue
                     */
                    _tile2 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    /*
                      Bounds check
                     */
                    if (0x13a0f < _tile2) {
                        return;
                    }
                    /*
                      Get Y coordinate of current tile
                     */
                    sVar1 = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    /*
                      Read the distance value for this tile from the AI path cost layer
                     */
                    this->searchQueue.currentDistance = (uint)
                        * (byte*)(*(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray
                                      + playerID * 0x177bc + -0x10)
                                * 0x13a10
                            + 0x1ee2998 + _tile2);
                    /*
                      Track maximum distance encountered, constitutes extra return value
                     */
                    if (this->distance < (int)this->searchQueue.currentDistance) {
                        this->distance = this->searchQueue.currentDistance;
                    }
                    /*
                      Stop if we've exceeded the maximum distance limit
                     */
                    if (limit < (int)this->searchQueue.currentDistance) {
                        return;
                    }
                    /*
                      === COLLECT CANDIDATE TILES AT SPECIFIC DISTANCE ===   If param_2 is non-zero and tile is at
                      exactly that distance,   and it's reachable from param_3 zone, add to candidate list
                     */
                    if ((((borderDistance != 0) && (this->searchQueue.currentDistance == borderDistance))
                            && (_canNav = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                                calculateCanPlayerUnitsNavigateToAreaFromArea,
                                    this)(playerID, (dword)((int)(fromArea)),
                                    (dword)((int)((int)(short)DAT_TileMapState::instance.PathConnectionLayer[_tile2])),
                                    0),
                                _canNav != 0))
                        && (DAT_AICState::instance.aiBorderTilesIndex < 1000)) {
                        /*
                          Add to candidate array (likely used by AI for strategic placement decisions)
                         */
                        DAT_AICState::instance.aiBorderTiles[DAT_AICState::instance.aiBorderTilesIndex].tile = _tile2;
                        DAT_AICState::instance.aiBorderTilesIndex = DAT_AICState::instance.aiBorderTilesIndex + 1;
                    }
                    /*
                      === EXPAND TO ADJACENT TILES ===   Only expand if tile doesn't have blocking terrain   0x100031
                      checks for: sea, border, border edge, river
                     */
                    if ((DAT_TileMapState::instance.LogicLayer[_tile2] & 0x100031U) == 0) {
                        /*
                          Get pointer to movement direction offsets
                         */
                        paiVar4 = DAT_TileMapState::instance.directionTranslationMatrix + sVar1;
                        /*
                          Process all 8 adjacent tiles (cardinal + diagonal directions)
                         */
                        psVar3 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].short_.yOffset;
                        do {
                            /*
                              Calculate adjacent tile index
                             */
                            iVar2 = (*paiVar4)[0] + _tile2;
                            /*
                              If adjacent tile hasn't been visited this iteration
                             */
                            if (DAT_TileMapState::instance.WalkLayer[iVar2] != this->searchGeneration) {
                                /*
                                  SET DISTANCE = CURRENT DISTANCE + 1   This creates the distance map radiating from AI
                                  zones
                                 */
                                *(char*)(*(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray
                                             + playerID * 0x177bc + -0x10)
                                        * 0x13a10
                                    + 0x1ee2998 + iVar2) = (char)this->searchQueue.currentDistance + '\x01';
                                /*
                                  previous line sets pathfinding cost layer   Mark as visited
                                 */
                                DAT_TileMapState::instance.WalkLayer[iVar2] = (short)this->searchGeneration;
                                /*
                                  Add adjacent tile to queue
                                 */
                                this->searchQueue.yQueue[this->searchQueue.writeIndex] = *psVar3 + sVar1;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar2;
                                /*
                                  Increment queue write position
                                 */
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            /*
                              Move to next direction
                             */
                            psVar3 = psVar3 + 8;
                            paiVar4 = (int (*)[8])(*paiVar4 + 2);
                            /*
                              Process all 8 directions
                             */
                        } while ((int)psVar3 < 0xb4908c);
                    }
                    /*
                      === ADVANCE TO NEXT TILE IN QUEUE ===
                     */
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            }
            return;
        }

    }
}
}
