#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Location::Point8ShortXY;
        using OpenSHC::Map::Navigation::Algorithms::XYPair;

        /*
          WARNING: Type propagation algorithm not settling
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A83B0
        void PathFindingState::populateDestinationsArrayWithWallTileAndFreeTilePairInSameArea(
            int tile, int maxDestinations, dword area, int playerID)
        {
            int iVar2;
            int* piVar3;
            XYPair* pXVar4;
            short* psVar5;
            int (*paiVar6)[8];
            int _candidate;
            int _dIndex;
            short _tileY;
            int _axgt;
            int _tile2;
            uint _tile;
            short _x;
            short _y;
            _tileY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            _axgt = DAT_ViewportRenderState::instance.translationMatrix[_tileY].addXgetTile;
            this->searchGeneration = this->searchGeneration + 1;
            _dIndex = 0;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.currentDistance = 1;
            this->searchQueue.writeIndex = 1;
            maxDestinations = maxDestinations * 2;
            this->searchQueue.readIndex = 0;
            if (maxDestinations < 500) {
                if (maxDestinations < 50) {
                    maxDestinations = 50;
                }
            } else {
                maxDestinations = 500;
            }
            this->searchQueue.tilesQueue[0] = tile;
            this->searchQueue.yQueue[0] = _tileY;
            this->searchQueue.xQueue[0] = (short)tile - (short)_axgt;
            DAT_TileMapState::instance.CertainPathLayer[tile] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while (_tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex], _tile < 0x13a10) {
                    _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                    _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                    if ((80400 < this->searchQueue.currentDistance) || (10 < this->searchQueue.currentDistance))
                        break;
                    for (int _direction = 0; _direction < 8; _direction = _direction + 1) {
                        _candidate = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration
                            && (area == (int)(short)DAT_TileMapState::instance.PathConnectionLayer[_candidate]
                                || (iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                                  calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        this)(playerID, (dword)((int)(area)),
                                        (dword)((int)((
                                            int)(short)DAT_TileMapState::instance.PathConnectionLayer[_candidate])),
                                        0),
                                    iVar2 != 0))) {
                            /*
                              queue tiles in area that are navigatible by this player without climbing
                             */
                            short sVar1 = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.xOffset;
                            DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[_candidate] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar1 + _x;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset + _y;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                    }

                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex)
                        break;
                }
            }
            this->searchQueue.readIndex = 0;
            if (0 < this->searchQueue.writeIndex) {
                piVar3 = &this->searchQueue.destinationsArray[0].tile2OrAHelper;
                do {
                    _tile2 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    /*
                      no wall tower gatehouse crenel nor keep
                     */
                    if ((DAT_TileMapState::instance.LogicLayer[_tile2] & 0x10000300U) == 0) {
                        pXVar4 = DAT_ClimbLogicDefinedData::instance.CardinalHorizontalFirstSearchOrder;
                        do {
                            int _candidate2 = DAT_ViewportRenderState::instance
                                                  .translationMatrix[pXVar4->y
                                                      + (int)this->searchQueue.yQueue[this->searchQueue.readIndex]]
                                                  .addXgetTile
                                + pXVar4->x + (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                            if ((DAT_TileMapState::instance.LogicLayer[_candidate2] & 0x300U) != 0
                                && (DAT_TileMapState::instance.LogicLayer[_candidate2] & 0x400000U) == 0
                                && (DAT_TileMapState::instance.WallOwnerLayer[_candidate2] & 7) + 1 != playerID) {
                                /*
                                  candidate 2 is wall tower gatehouse, or crenel (variation)
                                 */
                                if (_candidate2 != 0) {
                                    *piVar3 = _candidate2;
                                    _dIndex = _dIndex + 1;
                                    ((PathHelper12*)(piVar3 + -1))->tile1 = _tile2;
                                    piVar3 = piVar3 + 3;
                                    if (maxDestinations <= _dIndex) {
                                        return;
                                    }
                                    this->searchQueue.tilesQueue[this->searchQueue.readIndex] = -1;
                                }
                                break;
                            }
                            pXVar4 = pXVar4 + 1;
                        } while ((int)pXVar4 < 0xb39238);
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                } while (this->searchQueue.readIndex < this->searchQueue.writeIndex);
            }
            this->searchQueue.readIndex = 0;
            if (0 < this->searchQueue.writeIndex) {
                piVar3 = &((PathFindingStatePartB*)(this->climbData + 200))->destinationsArray[_dIndex].tile2OrAHelper;
                do {
                    iVar2 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    /*
                      no wall tower gatehouse crenel nor keep
                     */
                    if ((DAT_TileMapState::instance.LogicLayer[iVar2] & 0x10000300U) == 0 && iVar2 != -1) {
                        ((PathHelper12*)(piVar3 + -1))->tile1 = iVar2;
                        *piVar3 = 0;
                        _dIndex = _dIndex + 1;
                        piVar3 = piVar3 + 3;
                        if (maxDestinations <= _dIndex) {
                            return;
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                } while (this->searchQueue.readIndex < this->searchQueue.writeIndex);
            }
            this->searchQueue.destinationsArray[_dIndex].tile1 = 0;
            ((PathFindingStatePartB*)(this->climbData + 200))->destinationsArray[_dIndex].tile2OrAHelper = 0;
            return;
        }

    }
}
}
