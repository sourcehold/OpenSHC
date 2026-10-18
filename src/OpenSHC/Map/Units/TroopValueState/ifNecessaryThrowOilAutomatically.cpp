#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "../TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitInstructionType;
        using Map::Units::Behavior::UnitStanceEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C570
        undefined4 TroopValueState::ifNecessaryThrowOilAutomatically(int param_1)
        {
            short* _pUpdateTickTracker;
            short _buildingID;
            ushort _buildingX;
            ushort _buildingY;
            ushort _tileUnitID;
            int _buildingSize;
            int _tileOrTroopValue;
            int _searchRadiusOrTargetUnitID;
            int _playerIDOrUnitID;
            int _tribeIDOrTileIndex;
            int _enemyTroopValue;
            int _friendlyTroopValue;
            _tribeIDOrTileIndex = (int)DAT_UnitsState::instance.units[param_1].tribeID;
            _searchRadiusOrTargetUnitID = 4;
            if (0x6e < DAT_UnitsState::instance.units[param_1].terrainOrClimbHeight) {
                _searchRadiusOrTargetUnitID = 5;
            }
            if (_tribeIDOrTileIndex < 1) {
                return 0;
            }
            if (0x50 < DAT_UnitsState::instance.units[param_1].closestEnemyMicroDistance
                || (_playerIDOrUnitID = (int)DAT_UnitsState::instance.units[param_1].owner,
                    DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerIDOrUnitID] != -1
                        && DAT_TribesState::instance.tribes[_tribeIDOrTileIndex].unitStance
                            == Map::Units::Behavior::USE_STAND_GROUND)) {
                return 0;
            }
            // The pointer stays: assigning through units[param_1].updateTickTracker cost 0.1%.
            _pUpdateTickTracker = &DAT_UnitsState::instance.units[param_1].updateTickTracker;
            *_pUpdateTickTracker = *_pUpdateTickTracker + 1;
            if (7 < DAT_UnitsState::instance.units[param_1].updateTickTracker) {
                _tileOrTroopValue = DAT_UnitsState::instance.units[param_1].tile;
                DAT_UnitsState::instance.units[param_1].updateTickTracker = 0;
                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::computeTotalUnitsWithinDistance,
                    DAT_PathFindingState::ptr)(_playerIDOrUnitID, 0, 0, _tileOrTroopValue, _searchRadiusOrTargetUnitID);
                _searchRadiusOrTargetUnitID = DAT_PathFindingState::instance.field34_0x64;
                if (DAT_TribesState::instance.tribes[_tribeIDOrTileIndex].unitStance
                    == Map::Units::Behavior::USE_AGGRESSIVE) {
                    if (DAT_PathFindingState::instance.ALGO_TotalTroopCount < 1) {
                        return 0;
                    }
                } else if ((DAT_PathFindingState::instance.ALGO_TotalTroopCount <= 3)
                    && (DAT_PathFindingState::instance.ALGO_TotalTroopValue < 0x14)) {
                    return 0;
                }
                if (DAT_PathFindingState::instance.field34_0x64) {
                    _buildingID
                        = DAT_TileMapState::instance.BuildingLayer
                              [DAT_UnitsState::instance.units[DAT_PathFindingState::instance.field34_0x64].tile];
                    if (_buildingID) {
                        _buildingSize = 0;
                        switch (DAT_BuildingsState::instance.buildings[_buildingID].buildingType) {
                        case Map::Buildings::BT_CAMPGROUND:
                            _buildingSize = 7;
                            break;
                        case Map::Buildings::BT_PARADEGROUND:
                        case Map::Buildings::BT_PARADEGROUND2:
                        case Map::Buildings::BT_PARADEGROUND3:
                        case Map::Buildings::BT_PARADEGROUND4:
                        case Map::Buildings::BT_PARADEGROUND5:
                            _buildingSize = 5;
                            break;
                        default:
                            break;
                        case Map::Buildings::BT_CAMPFIRE:
                            _buildingSize = 4;
                            break;
                        }
                        if (_buildingSize) {
                            _buildingX = DAT_BuildingsState::instance.buildings[_buildingID].x;
                            _buildingY = DAT_BuildingsState::instance.buildings[_buildingID].y;
                            _tribeIDOrTileIndex = 0;
                            _friendlyTroopValue = 0;
                            _enemyTroopValue = 0;
                            do {
                                MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeIndexMappingData,
                                    DAT_TileMapState::ptr)(_tribeIDOrTileIndex, _buildingSize);
                                _tileUnitID = DAT_TileMapState::instance
                                                  .UnitLayer[DAT_ViewportRenderState::instance
                                                                 .translationMatrix[DAT_TileMapState::instance.buildingY
                                                                     + (short)_buildingY]
                                                                 .addXgetTile
                                                      + DAT_TileMapState::instance.buildingX + (int)(short)_buildingX];
                                while (_playerIDOrUnitID = (int)(short)_tileUnitID, _playerIDOrUnitID) {
                                    if (DAT_UnitsState::instance.units[_playerIDOrUnitID].isSelectable_OR_matchTime
                                        != 0) {
                                        if (DAT_GameState::instance.mapAndTime
                                                .playerTeams[DAT_UnitsState::instance.units[param_1].owner]
                                            == DAT_GameState::instance.mapAndTime
                                                .playerTeams[DAT_UnitsState::instance.units[_playerIDOrUnitID].owner]) {
                                            _tileOrTroopValue = MACRO_CALL_MEMBER(
                                                Map::Units::TroopValueState_Func::getValueOfTroopType,
                                                DAT_TroopValueState::ptr)(
                                                (Map::Units::UnitType)DAT_UnitsState::instance.units[_playerIDOrUnitID]
                                                    .unitType);
                                            _friendlyTroopValue = _friendlyTroopValue + _tileOrTroopValue;
                                        } else {
                                            _tileOrTroopValue = MACRO_CALL_MEMBER(
                                                Map::Units::TroopValueState_Func::getValueOfTroopType,
                                                DAT_TroopValueState::ptr)(
                                                (Map::Units::UnitType)DAT_UnitsState::instance.units[_playerIDOrUnitID]
                                                    .unitType);
                                            _enemyTroopValue = _enemyTroopValue + _tileOrTroopValue;
                                        }
                                    }
                                    _tileUnitID
                                        = DAT_UnitsState::instance.units[_playerIDOrUnitID].nextUnitOnTheSameTile;
                                }
                                _tribeIDOrTileIndex = _tribeIDOrTileIndex + 1;
                            } while (_tribeIDOrTileIndex < DAT_TileMapState::instance.constructionTileCount);
                            if (_enemyTroopValue < _friendlyTroopValue) {
                                return 0;
                            }
                        }
                    }
                    DAT_UnitsState::instance.units[param_1].targetingType = Map::Units::UIT_THROW_OIL;
                    DAT_UnitsState::instance.units[param_1].attackAtTileX
                        = DAT_UnitsState::instance.units[_searchRadiusOrTargetUnitID].x;
                    DAT_UnitsState::instance.units[param_1].attackAtTileY
                        = DAT_UnitsState::instance.units[_searchRadiusOrTargetUnitID].y;
                    DAT_UnitsState::instance.units[param_1].animationFrame = 4;
                    return 1;
                }
            }
            return 0;
        }

    }
}
}
