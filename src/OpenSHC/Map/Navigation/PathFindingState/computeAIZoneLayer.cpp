#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Buildings::BuildingTypeShort;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          Computes the AI Zone Layer - a flood-fill from the player's keep that marks accessible areas.   This creates a
          "zone of control" or "accessible territory" map for strategic AI decisions.      The algorithm works in
          phases:   Phase 1: Flood-fill through walkable/connected areas (marks tiles with value 1)   Phase 2: Expand
          into surrounding tiles with weighted distances based on terrain difficulty      @param this - PathFindingState
          object pointer   @param attackedPlayerID - The player whose keep/territory to analyze   @param canReachKeep -
          If non-zero, limits expansion to 2000 tiles (early termination)      decompilerscript: committed: 2025-01-30
          21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A4470
        void PathFindingState::computeAIZoneLayer(int attackedPlayerID, int canReachKeep, int param_3)
        {
            uint uVar1;
            int _offsetTile;
            int _direction;
            int (*_pDirectionTranslation)[8];
            int* piVar3;
            int _candidateTile;
            BuildingTypeShort _buildingType;
            int _candidateY;
            short _directionOffset;
            /*
                 === VALIDATE PLAYER HAS A KEEP ===   Only compute AI zones if the player has a keep (main castle)
             */
            if (DAT_GameState::instance.playerDataArray[attackedPlayerID].keep.id != 0) {
                /*
                     === INITIALIZE BFS STARTING FROM KEEP ===
                 */
                this->searchQueue.currentDistance = 1;
                this->searchQueue.readIndex = 0;
                this->searchQueue.writeIndex = 1;
                /*
                     Get the keep's position (specifically the campfire tile inside the keep)
                 */
                this->searchQueue.yQueue[0]
                    = (short)DAT_GameState::instance.playerDataArray[attackedPlayerID].campground.yEntry;
                this->searchQueue.tilesQueue[0]
                    = DAT_GameState::instance.playerDataArray[attackedPlayerID].campground.xEntry
                    + DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_GameState::instance.playerDataArray[attackedPlayerID]
                                  .campground.yEntry]
                          .addXgetTile;
                /*
                     Mark the keep tile as AI Zone with value 1 (the starting point)
                 */
                DAT_TileMapState::instance.AIZoneLayer[this->searchQueue.tilesQueue[0]] = 1;
                /*
                     Repurpose variable as iteration counter
                 */
                attackedPlayerID = 0;
                /*
                     Update path linkage (possibly opens gates or updates navigation mesh)
                 */
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(1);
                /*
                        === PHASE 1: FLOOD-FILL THROUGH WALKABLE/CONNECTED AREAS ===   This phase marks all tiles that
                   are directly connected via normal pathfinding
                 */
                while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    /*
                         Save iteration counter
                     */
                    int iVar2 = attackedPlayerID;
                    /*
                            === INNER LOOP: EXPAND THROUGH CONNECTED TILES ===
                     */
                    this->searchQueue.previousReadIndex = this->searchQueue.readIndex;
                    while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                        /*
                          Get current tile being processed
                         */
                        _candidateY = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                        _candidateTile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                        /*
                          Check all 8 adjacent directions
                         */
                        _direction = 0;
                        _pDirectionTranslation = DAT_TileMapState::instance.directionTranslationMatrix + _candidateY;
                        do {
                            _offsetTile = (*_pDirectionTranslation)[0] + _candidateTile;
                            /*
                              Add tile to AI zone if:   1. Not already marked (< 1)   2. Has path connection
                              (PathConnectionLayer != 0)   3. Either:   a) Normal pathfinding allows movement in
                              this direction, OR   b) There's a gate (GATEHOUSELARGE or GATEHOUSESMALL) on the
                              tile
                             */
                            if ((char)DAT_TileMapState::instance.AIZoneLayer[_offsetTile] < '\x01'
                                && (short)DAT_TileMapState::instance.PathConnectionLayer[_offsetTile] != 0
                                && ((DAT_TileMapState::instance.PathLinkageLayer[_candidateTile]
                                        & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction])
                                        != 0
                                    || ((DAT_TileMapState::instance.BuildingLayer[_offsetTile] != 0
                                        && ((_buildingType = DAT_BuildingsState::instance
                                                 .buildings[DAT_TileMapState::instance.BuildingLayer[_offsetTile]]
                                                 .buildingType,
                                            _buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
                                                || (_buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL))))))) {
                                /*
                                  Calculate Y offset for this direction
                                 */
                                _directionOffset
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                          .short_.yOffset;
                                /*
                                  Mark tile as part of AI zone (value 1 = directly accessible)
                                 */
                                DAT_TileMapState::instance.AIZoneLayer[_offsetTile] = 1;
                                /*
                                  Add to BFS queue for further expansion
                                 */
                                this->searchQueue.yQueue[this->searchQueue.writeIndex] = _directionOffset + _candidateY;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _offsetTile;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (80400 < this->searchQueue.writeIndex)
                                    goto LAB_004a4914;
                            }
                            _direction = _direction + 1;
                            _pDirectionTranslation = (int (*)[8])(*_pDirectionTranslation + 1);
                        } while (_direction < 8);
                        /*
                          Move to next tile in queue
                         */
                        this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                        if (80400 < this->searchQueue.readIndex) {
                            this->searchQueue.readIndex = 0;
                        }
                        /*
                          === EARLY TERMINATION CONDITIONS ===   If canReachKeep is set and we've marked > 2000
                          tiles, stop   OR if we've marked > 6000 tiles total, stop   (Performance optimization
                          to prevent excessive computation)
                         */
                        if (((canReachKeep != 0) && (1999 < this->searchQueue.writeIndex))
                            || 5999 < this->searchQueue.writeIndex)
                            goto LAB_004a4914;
                    }
                    /*
                      === PHASE 2: EXPAND INTO DIFFICULT TERRAIN ===   After marking all easily accessible tiles,
                      expand into harder-to-reach areas   with distance penalties based on terrain type
                     */
                    this->searchQueue.readIndex = this->searchQueue.previousReadIndex;
                    this->searchQueue.nextWriteIndex = this->searchQueue.writeIndex;
                    if (this->searchQueue.previousReadIndex != this->searchQueue.writeIndex) {
                        do {
                            _direction = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                            /*
                              Distance = current tile's AI zone value + 1
                             */
                            this->searchQueue.currentDistance
                                = (char)DAT_TileMapState::instance.AIZoneLayer[_direction] + 1;
                            /*
                              Get movement direction offsets
                             */
                            piVar3
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[this->searchQueue.yQueue[this->searchQueue.readIndex]]
                                + 1;
                            /*
                              Process tiles in groups of 4 (unrolled loop)   === PROCESS ADJACENT TILES (Unrolled
                              loop for 4 directions at a time) ===
                             */
                            attackedPlayerID = 2;
                            do {
                                /*
                                  === TILE 1 ===
                                 */
                                _offsetTile = (*(int (*)[8])(piVar3 + -1))[0] + _direction;
                                /*
                                  Only process if:   1. Not already marked   2. No blocking terrain (0x31 = sea,
                                  cliff, or border)   3. Either no building OR building allows passage (unknownFlag4
                                  == 0)
                                 */
                                if ((char)DAT_TileMapState::instance.AIZoneLayer[_offsetTile] < '\x01'
                                    && (uVar1 = DAT_TileMapState::instance.LogicLayer[_offsetTile], (uVar1 & 0x31) == 0)
                                    && (DAT_TileMapState::instance.BuildingLayer[_offsetTile] == 0
                                        || (DAT_BuildingsState::instance
                                                .buildings[DAT_TileMapState::instance.BuildingLayer[_offsetTile]]
                                                .unknownFlag4
                                            == '\0'))) {
                                    /*
                                      === TERRAIN-BASED DISTANCE CALCULATION ===
                                     */
                                    if ((uVar1 & 0x100) == 0) {
                                        /*
                                          Non wall Non gatehouse
                                         */
                                        if ((uVar1 & 0x40000000) == 0 || iVar2 == 0) {
                                            /*
                                              Non moat or
                                             */
                                            DAT_TileMapState::instance.AIZoneLayer[_offsetTile]
                                                = (byte)this->searchQueue.currentDistance;
                                        } else {
                                            /*
                                              Moat discount making fortified areas closer in AI Zone calculations
                                             */
                                            DAT_TileMapState::instance.AIZoneLayer[_offsetTile]
                                                = (byte)this->searchQueue.currentDistance - 1;
                                        }
                                    } else {
                                        /*
                                          wall or gatehouse   This makes walls, towers, and gatehouses "farther"
                                          strategically
                                         */
                                        DAT_TileMapState::instance.AIZoneLayer[_offsetTile]
                                            = (byte)this->searchQueue.currentDistance + 6;
                                    }
                                }
                                /*
                                  === TILE 2 (same logic as tile 1) ===
                                 */
                                _offsetTile = *piVar3 + _direction;
                                if ((char)DAT_TileMapState::instance.AIZoneLayer[_offsetTile] < '\x01'
                                    && (uVar1 = DAT_TileMapState::instance.LogicLayer[_offsetTile], (uVar1 & 0x31) == 0)
                                    && (DAT_TileMapState::instance.BuildingLayer[_offsetTile] == 0
                                        || (DAT_BuildingsState::instance
                                                .buildings[DAT_TileMapState::instance.BuildingLayer[_offsetTile]]
                                                .unknownFlag4
                                            == '\0'))) {
                                    if ((uVar1 & 0x100) == 0) {
                                        if ((uVar1 & 0x40000000) == 0 || iVar2 == 0) {
                                            DAT_TileMapState::instance.AIZoneLayer[_offsetTile]
                                                = (byte)this->searchQueue.currentDistance;
                                        } else {
                                            DAT_TileMapState::instance.AIZoneLayer[_offsetTile]
                                                = (byte)this->searchQueue.currentDistance - 1;
                                        }
                                    } else {
                                        DAT_TileMapState::instance.AIZoneLayer[_offsetTile]
                                            = (byte)this->searchQueue.currentDistance + 6;
                                    }
                                }
                                /*
                                  === TILE 3 (same logic as tile 1) ===
                                 */
                                _offsetTile = piVar3[1] + _direction;
                                if ((char)DAT_TileMapState::instance.AIZoneLayer[_offsetTile] < '\x01'
                                    && (uVar1 = DAT_TileMapState::instance.LogicLayer[_offsetTile], (uVar1 & 0x31) == 0)
                                    && (DAT_TileMapState::instance.BuildingLayer[_offsetTile] == 0
                                        || (DAT_BuildingsState::instance
                                                .buildings[DAT_TileMapState::instance.BuildingLayer[_offsetTile]]
                                                .unknownFlag4
                                            == '\0'))) {
                                    if ((uVar1 & 0x100) == 0) {
                                        if ((uVar1 & 0x40000000) == 0 || iVar2 == 0) {
                                            DAT_TileMapState::instance.AIZoneLayer[_offsetTile]
                                                = (byte)this->searchQueue.currentDistance;
                                        } else {
                                            DAT_TileMapState::instance.AIZoneLayer[_offsetTile]
                                                = (byte)this->searchQueue.currentDistance - 1;
                                        }
                                    } else {
                                        DAT_TileMapState::instance.AIZoneLayer[_offsetTile]
                                            = (byte)this->searchQueue.currentDistance + 6;
                                    }
                                }
                                /*
                                  === TILE 4 (same logic as tile 1) ===
                                 */
                                _offsetTile = piVar3[2] + _direction;
                                if ((char)DAT_TileMapState::instance.AIZoneLayer[_offsetTile] < '\x01'
                                    && (uVar1 = DAT_TileMapState::instance.LogicLayer[_offsetTile], (uVar1 & 0x31) == 0)
                                    && (DAT_TileMapState::instance.BuildingLayer[_offsetTile] == 0
                                        || (DAT_BuildingsState::instance
                                                .buildings[DAT_TileMapState::instance.BuildingLayer[_offsetTile]]
                                                .unknownFlag4
                                            == '\0'))) {
                                    if ((uVar1 & 0x100) == 0) {
                                        if ((uVar1 & 0x40000000) == 0 || iVar2 == 0) {
                                            DAT_TileMapState::instance.AIZoneLayer[_offsetTile]
                                                = (byte)this->searchQueue.currentDistance;
                                        } else {
                                            DAT_TileMapState::instance.AIZoneLayer[_offsetTile]
                                                = (byte)this->searchQueue.currentDistance - 1;
                                        }
                                    } else {
                                        DAT_TileMapState::instance.AIZoneLayer[_offsetTile]
                                            = (byte)this->searchQueue.currentDistance + 6;
                                    }
                                }
                                piVar3 = piVar3 + 4;
                                attackedPlayerID = attackedPlayerID + -1;
                            } while (attackedPlayerID != 0);
                            /*
                              Move to next tile in queue
                             */
                            this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                            if (0x13a0f < this->searchQueue.readIndex) {
                                this->searchQueue.readIndex = 0;
                            }
                        } while (this->searchQueue.readIndex != this->searchQueue.nextWriteIndex);
                    }
                    /*
                      Increment iteration counter (alternates between 0 and 1)
                     */
                    attackedPlayerID = iVar2 + 1;
                    if (1 < attackedPlayerID) {
                        attackedPlayerID = 0;
                    }
                }
            LAB_004a4914:
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(0);
            }
            return;
        }

    }
}
}
