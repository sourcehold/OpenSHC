#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Game::GameMode;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          BFS from (param_2, param_3) up to distance param_1, scoring enemy buildings and walls owned by   player
          param_7. Buildings score higher for defensive structures (0x400 flag), distance, and fire   state. Walls are
          scored by high difference from base terrain. The best-scoring tileUnk coordinates   are written to ALG_TargetX,
          ALG_TargetY, and ALG_TargetTile. Height traversal cost is weighted in   3 tiers based on param_5.      renamed
          by: Claude Sonnet 4.6
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A6010
        void PathFindingState::findBestAttackTargetTileWithHeightAndOwner(int param_1, uint param_2, uint param_3,
            int param_4, int param_5, int param_6, int param_7, int param_8, int param_9)
        {
            int _bestScore;
            int _bestX;
            int _bestY;
            uint _bestTile;
            uint _tile;
            int _x;
            int _y;
            uint _logic;
            uint _zoneDistance;
            int _score;
            int _heightDiff;
            int _buildingID;
            int _base;
            int _startHeight;
            int _count;
            int* _pArc;
            int _direction;
            int _next;
            int _height;
            short _cost;
            _bestX = -1;
            _bestY = -1;
            _bestTile = 0xffffffff;
            this->calculations = this->calculations + 1;
            _bestScore = 1000000;
            this->ALG_TargetTile = 0;
            this->ALG_TargetY = 0;
            this->ALG_TargetX = 0;
            if (param_2 > 399 || param_3 > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[param_3 * 400 + param_2] == '\0') {
                return;
            }
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.currentDistance = 1;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.readIndex = 0;
            this->searchQueue.yQueue[0] = (short)param_3;
            this->searchQueue.xQueue[0] = (short)param_2;
            _tile = DAT_ViewportRenderState::instance.translationMatrix[param_3].addXgetTile + param_2;
            this->searchQueue.tilesQueue[0] = _tile;
            DAT_TileMapState::instance.CertainPathLayer[_tile] = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]]
                = (short)this->searchGeneration;
            _startHeight = (int)DAT_TileMapState::instance.HeightLayer[_tile];
            if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                return;
            }
            do {
                _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (_tile > 0x13a0f)
                    break;
                _x = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                _y = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                _logic = DAT_TileMapState::instance.LogicLayer[_tile];
                _zoneDistance = (uint)DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[param_7][_tile];
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                if ((int)this->searchQueue.currentDistance > param_1) {
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a10 <= (int)this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    continue;
                }
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY && param_6 >= 8) {
                    _zoneDistance = 1;
                }
                if ((_logic & 2) == 0) {
                    if ((_logic & 0x10100) != 0 && _zoneDistance != 0 && (int)_zoneDistance < param_8) {
                        /*
                          enemy wall: scored by its high above the base terrain
                         */
                        if ((DAT_TileMapState::instance.WallOwnerLayer[_tile] & 7) + 1 == param_7 && param_9 == 0) {
                            _heightDiff = (int)DAT_TileMapState::instance.HeightLayer[_tile]
                                - (int)DAT_TileMapState::instance.DefaultHeightLayer[_tile];
                            if ((int)this->searchQueue.currentDistance <= 0) {
                                _score = 100000;
                            } else if ((int)this->searchQueue.currentDistance <= 15) {
                                _score = (20 - (int)this->searchQueue.currentDistance) * 300 + _heightDiff;
                            } else {
                                _score = (int)this->searchQueue.currentDistance * 100 + _heightDiff;
                            }
                            goto LAB_004a62e3;
                        }
                    } else if ((_logic & 0x10000400) != 0 && _zoneDistance != 0 && (int)_zoneDistance < param_8
                        && (_buildingID = (int)DAT_TileMapState::instance.BuildingLayer[_tile], _buildingID != 0)
                        && DAT_BuildingDefinedData::instance.BuildingTypeHasHealth
                                [(short)DAT_BuildingsState::instance.buildings[_buildingID].buildingType]
                            != 0
                        && DAT_BuildingsState::instance.buildings[_buildingID].owner == param_7
                        && (param_9 == 0
                            || (MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor,
                                    DAT_BuildingsState::ptr)(_buildingID)
                                    != 0
                                && DAT_BuildingsState::instance.buildings[_buildingID].fireDuration == 0))) {
                        /*
                          enemy building: defensive structures (0x400) score higher
                         */
                        _base = 150;
                        if ((_logic & 0x400) == 0) {
                            _base = 75;
                        }
                        if ((int)this->searchQueue.currentDistance <= 0) {
                            _score = 100000;
                        } else if ((int)this->searchQueue.currentDistance <= 15) {
                            _score = (_base - 100) * (int)this->searchQueue.currentDistance + 1500;
                        } else {
                            _score = (int)this->searchQueue.currentDistance * _base;
                        }
                    LAB_004a62e3:
                        if (_score < _bestScore
                            && MACRO_CALL(OpenSHC::Map::Navigation_Func::calcApproxEuclideanDistance)(
                                   param_2, _x, param_3, _y)
                                <= param_1) {
                            _bestTile = _tile;
                            _bestY = _y;
                            _bestX = _x;
                            _bestScore = _score;
                        }
                    }
                }
                /*
                  expand along the arc: 1 direction on even distances, 3 on odd ones
                 */
                _count = ((int)(char)this->searchQueue.currentDistance & 1) * 2 | 1;
                _pArc = DAT_ClimbLogicDefinedData::instance.field13_0x13c[param_4];
                do {
                    _direction = *_pArc;
                    _next = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                    _logic = DAT_TileMapState::instance.LogicLayer[_next];
                    if ((int)DAT_TileMapState::instance.WalkLayer[_next] != this->searchGeneration
                        && (_logic & 0x30) == 0) {
                        if ((_logic & 0x10000400) != 0) {
                            _buildingID = (int)DAT_TileMapState::instance.BuildingLayer[_next];
                            if (_buildingID == 0 || DAT_BuildingsState::instance.buildings[_buildingID].owner != param_7)
                                goto LAB_next;
                            _height = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                DAT_BuildingsState::ptr)(_buildingID);
                        } else if ((_logic & 0x100) != 0) {
                            if ((DAT_TileMapState::instance.WallOwnerLayer[_next] & 7) + 1 != param_7)
                                goto LAB_next;
                            _height = (int)DAT_TileMapState::instance.HeightLayer[_next];
                        } else {
                            _height = (int)DAT_TileMapState::instance.HeightLayer[_next];
                            if (_height > _startHeight + param_5)
                                goto LAB_next;
                        }
                        if (_height > (param_5 * 2) / 3 + _startHeight) {
                            _cost = 3;
                        } else {
                            _cost = (_height > param_5 / 3 + _startHeight) + 1;
                        }
                        DAT_TileMapState::instance.CertainPathLayer[_next]
                            = (short)this->searchQueue.currentDistance + _cost;
                        DAT_TileMapState::instance.WalkLayer[_next] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.xOffset
                            + (short)_x;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset
                            + (short)_y;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _next;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                LAB_next:
                    _pArc = _pArc + 1;
                    _count = _count - 1;
                } while (_count != 0);
                this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                if (0x13a10 <= (int)this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            if (_bestX != -1) {
                this->ALG_TargetX = _bestX;
                this->ALG_TargetY = _bestY;
                this->ALG_TargetTile = _bestTile;
            }
            return;
        }

    }
}
}
