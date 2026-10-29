#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Location::Point8ShortXY;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Type propagation algorithm not settling
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A79A0
        void PathFindingState::pathPlanningForTribe(
            uint tribeID, undefined4 targetUnitID, uint ySpace, uint y, int unitCount, dword area, int playerID)
        {
            uint _tile;
            int _next;
            int _startTile;
            int _startHeight;
            int _height;
            int _dy;
            int _dx;
            int _destIndex;
            PathHelper12* _pDest;
            _destIndex = 0;
            BOOL _assasinsTribe = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::isTribeAllAssassins, DAT_TribesState::ptr)(tribeID);
            if (399 < ySpace) {
                return;
            }
            if (399 < y) {
                return;
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + ySpace] == '\0') {
                return;
            }
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            unitCount = unitCount * 2;
            if (unitCount > 500) {
                unitCount = 500;
            } else if (unitCount < 50) {
                unitCount = 50;
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = (short)y;
            this->searchQueue.xQueue[0] = (short)ySpace;
            _startTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + ySpace;
            this->searchQueue.tilesQueue[0] = _startTile;
            DAT_TileMapState::instance.CertainPathLayer[_startTile] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]]
                = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                do {
                    _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if (_tile > 0x13a0f)
                        break;
                    int _x = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    int _y = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                    if ((int)this->searchQueue.currentDistance > 0x13a10)
                        break;
                    if ((int)this->searchQueue.currentDistance > 10)
                        break;
                    for (int _direction = 0; _direction < 8; _direction = _direction + 1) {
                        _next = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                        if ((int)DAT_TileMapState::instance.WalkLayer[_next] != this->searchGeneration
                            && ((int)area == (int)(short)DAT_TileMapState::instance.PathConnectionLayer[_next]
                                || MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                         calculateCanPlayerUnitsNavigateToAreaFromArea,
                                       DAT_PathFindingState::ptr)(playerID, area,
                                       (dword)(int)(short)DAT_TileMapState::instance.PathConnectionLayer[_next], 0)
                                    != 0
                                || (_assasinsTribe != 0
                                    && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                             calculateCanReachUsingCachedAreaLogic,
                                           DAT_PathFindingState::ptr)(_startTile, _next)
                                        != FALSE))) {
                            DAT_TileMapState::instance.CertainPathLayer[_next]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[_next] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                      .short_.xOffset
                                + (short)_x;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                      .short_.yOffset
                                + (short)_y;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _next;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a10 <= (int)this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            }
            /*
              Pass 1: tiles at Chebyshev distance 2 with a high difference below 32
             */
            this->searchQueue.readIndex = 0;
            if (0 < (int)this->searchQueue.writeIndex) {
                _pDest = this->searchQueue.destinationsArray;
                do {
                    _startHeight = (int)DAT_TileMapState::instance.HeightLayer[_startTile];
                    if ((DAT_TileMapState::instance.LogicLayer[_startTile] & 0x10000000) != 0) {
                        _startHeight += MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                            DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance.BuildingLayer[_startTile]);
                    }
                    _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    _height = (int)DAT_TileMapState::instance.HeightLayer[_tile];
                    if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x10000000) != 0) {
                        _height += MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                            DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance.BuildingLayer[_tile]);
                    }
                    _dy = abs((int)y - (int)this->searchQueue.yQueue[this->searchQueue.readIndex]);
                    _dx = abs((int)ySpace - (int)this->searchQueue.xQueue[this->searchQueue.readIndex]);
                    if (_dx <= _dy) {
                        _dx = _dy;
                    }
                    if (_dx == 2 && abs(_startHeight - _height) < 32) {
                        _pDest->tile1 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                        _destIndex = _destIndex + 1;
                        _pDest->tile2OrAHelper = 1;
                        _pDest = _pDest + 1;
                        if (_destIndex >= unitCount) {
                            return;
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                } while ((int)this->searchQueue.readIndex < (int)this->searchQueue.writeIndex);
                if (_destIndex >= 5)
                    goto LAB_004a7e8c;
            }
            /*
              Pass 2: tiles at Chebyshev distance 1 with a high difference below 32
             */
            this->searchQueue.readIndex = 0;
            if (0 < (int)this->searchQueue.writeIndex) {
                _pDest = this->searchQueue.destinationsArray + _destIndex;
                do {
                    _startHeight = (int)DAT_TileMapState::instance.HeightLayer[_startTile];
                    if ((DAT_TileMapState::instance.LogicLayer[_startTile] & 0x10000000) != 0) {
                        _startHeight += MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                            DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance.BuildingLayer[_startTile]);
                    }
                    _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    _height = (int)DAT_TileMapState::instance.HeightLayer[_tile];
                    if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x10000000) != 0) {
                        _height += MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                            DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance.BuildingLayer[_tile]);
                    }
                    _dy = abs((int)y - (int)this->searchQueue.yQueue[this->searchQueue.readIndex]);
                    _dx = abs((int)ySpace - (int)this->searchQueue.xQueue[this->searchQueue.readIndex]);
                    if (_dx <= _dy) {
                        _dx = _dy;
                    }
                    if (_dx == 1 && abs(_startHeight - _height) < 32) {
                        _pDest->tile1 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                        _destIndex = _destIndex + 1;
                        _pDest->tile2OrAHelper = 1;
                        _pDest = _pDest + 1;
                        if (_destIndex >= unitCount) {
                            return;
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                } while ((int)this->searchQueue.readIndex < (int)this->searchQueue.writeIndex);
            }
            /*
              Pass 3: every tileUnk further away than 2
             */
        LAB_004a7e8c:
            this->searchQueue.readIndex = 0;
            if (0 < (int)this->searchQueue.writeIndex) {
                _pDest = this->searchQueue.destinationsArray + _destIndex;
                do {
                    _dy = abs((int)y - (int)this->searchQueue.yQueue[this->searchQueue.readIndex]);
                    _dx = abs((int)ySpace - (int)this->searchQueue.xQueue[this->searchQueue.readIndex]);
                    if (_dx <= _dy) {
                        _dx = _dy;
                    }
                    if (_dx > 2) {
                        _pDest->tile1 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                        _destIndex = _destIndex + 1;
                        _pDest->tile2OrAHelper = 0;
                        _pDest = _pDest + 1;
                        if (_destIndex >= unitCount) {
                            return;
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                } while ((int)this->searchQueue.readIndex < (int)this->searchQueue.writeIndex);
            }
            this->searchQueue.destinationsArray[_destIndex].tile1 = 0;
            this->searchQueue.destinationsArray[_destIndex].tile2OrAHelper = 0;            return;
        }

    }
}
}
