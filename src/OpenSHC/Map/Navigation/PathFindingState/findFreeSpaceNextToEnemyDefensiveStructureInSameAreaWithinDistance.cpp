#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeInt.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Buildings::BuildingTypeInt;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x004A7F50
        void PathFindingState::findFreeSpaceNextToEnemyDefensiveStructureInSameAreaWithinDistance(
            int tile, int maxDestinations, int* area, int playerID, int shortenedDistance, int direction)
        {
            int iVar2;
            int _candidate2;
            int* piVar3;
            XYPair* pXVar4;
            BuildingTypeInt _buildingType;
            short* psVar5;
            int (*paiVar6)[8];
            int _candidate;
            int _index;
            int _dIndex;
            int _maxDistance;
            int _tile2;
            short _origY;
            int _origAXGT;
            short _x;
            short _y;
            uint _tile;
            _origY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            _origAXGT = DAT_ViewportRenderState::instance.translationMatrix[_origY].addXgetTile;
            _dIndex = 0;
            _maxDistance = 10;
            if (shortenedDistance == 1) {
                _maxDistance = 3;
            }
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    160800, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            maxDestinations = maxDestinations * 2;
            if (maxDestinations < 500) {
                if (maxDestinations < 0x32) {
                    maxDestinations = 0x32;
                }
            } else {
                maxDestinations = 500;
            }
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.readIndex = 0;
            this->searchQueue.tilesQueue[0] = tile;
            this->searchQueue.yQueue[0] = _origY;
            this->searchQueue.xQueue[0] = (short)tile - (short)_origAXGT;
            DAT_TileMapState::instance.CertainPathLayer[tile] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while (_tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex], _tile < 0x13a10) {
                    _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                    _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                    if ((80400 < this->searchQueue.currentDistance)
                        || (_maxDistance < this->searchQueue.currentDistance))
                        break;
                    psVar5 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].short_.yOffset;
                    paiVar6 = DAT_TileMapState::instance.directionTranslationMatrix + _y;
                    do {
                        _candidate = (*paiVar6)[0] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration
                            && (area == (int*)(int)(short)DAT_TileMapState::instance.PathConnectionLayer[_candidate]
                                || (iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                                  calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        this)(playerID, (dword)((int)(area)),
                                        (dword)((int)((
                                            int)(short)DAT_TileMapState::instance.PathConnectionLayer[_candidate])),
                                        0),
                                    iVar2 != 0))) {
                            short sVar1 = ((Point8ShortXY*)(psVar5 + -2))->xOffset;
                            /*
                              queue tiles in same area that are pathable without climbing
                             */
                            DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[_candidate] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar1 + _x;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = *psVar5 + _y;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        psVar5 = psVar5 + 4;
                        paiVar6 = (int (*)[8])(*paiVar6 + 1);
                    } while ((int)psVar5 < 0xb4908c);
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
                area = &this->searchQueue.destinationsArray[0].tile2OrAHelper;
                do {
                    _tile2 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if ((DAT_TileMapState::instance.LogicLayer[_tile2] & 0x10000300U) == 0) {
                        _index = 0;
                        pXVar4 = DAT_ClimbLogicDefinedData::instance
                                     .OrderedOrientationBasedCardinalDirectionList[direction];
                        do {
                            _candidate2 = DAT_ViewportRenderState::instance
                                              .translationMatrix[pXVar4->y
                                                  + (int)this->searchQueue.yQueue[this->searchQueue.readIndex]]
                                              .addXgetTile
                                + ((XYPair*)&pXVar4->x)->x + (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                            /*
                              if a wall gatehouse crenel keep and not a stockpile, and not a keep, and wall   is of
                              enemy... break
                             */
                            if ((DAT_TileMapState::instance.LogicLayer[_candidate2] & 0x10000300U) != 0
                                && (DAT_TileMapState::instance.LogicLayer[_candidate2] & 2U) == 0
                                && (DAT_TileMapState::instance.BuildingLayer[_candidate2] == 0
                                    || ((_buildingType = (BuildingTypeInt)(short)DAT_BuildingsState::instance
                                             .buildings[DAT_TileMapState::instance.BuildingLayer[_candidate2]]
                                             .buildingType,
                                        _buildingType != OpenSHC::Map::Buildings::BT_STOCKPILE
                                            && (2 < _buildingType - OpenSHC::Map::Buildings::BT_MANORHOUSE))))
                                && DAT_GameState::instance.mapAndTime
                                        .playerTeams[(DAT_TileMapState::instance.WallOwnerLayer[_candidate2] & 7) + 1]
                                    != DAT_GameState::instance.mapAndTime.playerTeams[playerID])
                                break;
                            _candidate2 = 0;
                            _index = _index + 1;
                            pXVar4 = pXVar4 + 1;
                        } while (_index < 4);
                        if (((shortenedDistance != 1) || (DAT_TileMapState::instance.UnitLayer[_candidate2] == 0))
                            && _candidate2 != 0) {
                            area[-1] = _tile2;
                            _dIndex = _dIndex + 1;
                            *area = _candidate2;
                            area = area + 3;
                            if (maxDestinations <= _dIndex) {
                                return;
                            }
                            this->searchQueue.tilesQueue[this->searchQueue.readIndex] = -1;
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                } while (this->searchQueue.readIndex < this->searchQueue.writeIndex);
            }
            this->searchQueue.readIndex = 0;
            if (0 < this->searchQueue.writeIndex) {
                piVar3 = &((PathFindingStatePartB*)(this->climbData + 200))->destinationsArray[_dIndex].tile2OrAHelper;
                do {
                    iVar2 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
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
