#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00533630
        BOOLEnum UnitsState::findAndAttackNearbyEnemyLaddermanInPosition(int unitID)
        {
            int _owner = this->units[unitID].owner;
            int _unitX = this->units[unitID].x;
            int _unitY = this->units[unitID].y;
            int _tile = this->units[unitID].tile;
            int _bestEnemyUnitID = 0;
            int _minDistance = 1000;
            dword _areaOfUnit = (short)DAT_TileMapState::instance.PathConnectionLayer[_tile];
            if ((DAT_TileMapState::instance.LogicLayer[_tile] & LogicHelpers::L_WALL_OR_GATEHOUSE) == 0) {
                return FALSE;
            }
            for (int i = 0; i < DAT_GameState::instance.playerDataArray[_owner].enemies; ++i) {
                int _enemyUnitID = DAT_GameState::instance.playerDataArray[_owner].enemyIDArray[i];
                if (this->units[_enemyUnitID].unitType != OpenSHC::Map::Units::UT_E_LADDER) {
                    continue;
                }
                if (this->units[_enemyUnitID].state.generic != (UnitState)3) {
                    continue;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isUsableClimbWithinArea,
                        DAT_PathFindingState::ptr)(_areaOfUnit, this->units[_enemyUnitID].wallDataID)
                    == FALSE) {
                    continue;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findPositionForGivenClimbArea,
                    DAT_PathFindingState::ptr)(_areaOfUnit, this->units[_enemyUnitID].x, this->units[_enemyUnitID].y);
                int _distanceX;
                if (_unitX > DAT_PathFindingState::instance.climbX) {
                    _distanceX = _unitX - DAT_PathFindingState::instance.climbX;
                } else {
                    _distanceX = DAT_PathFindingState::instance.climbX - _unitX;
                }
                int _distanceY;
                if (_unitY > DAT_PathFindingState::instance.climbY) {
                    _distanceY = _unitY - DAT_PathFindingState::instance.climbY;
                } else {
                    _distanceY = DAT_PathFindingState::instance.climbY - _unitY;
                }
                if (_distanceX < _distanceY) {
                    /* stores the largest distance into _distanceX */
                    _distanceX = _distanceY;
                }
                if (this->units[_enemyUnitID].targetShootRelated != 0) {
                    _distanceX = _distanceX + 10;
                }
                if (_distanceX < _minDistance) {
                    this->climbX2 = DAT_PathFindingState::instance.climbX;
                    _bestEnemyUnitID = _enemyUnitID;
                    _minDistance = _distanceX;
                    this->climbY2 = DAT_PathFindingState::instance.climbY;
                }
            }
            if (_bestEnemyUnitID == 0) {
                return FALSE;
            }
            this->units[unitID].shootTargetedUnit = (short)_bestEnemyUnitID;
            this->units[unitID].targetUID = this->units[_bestEnemyUnitID].uid;
            this->units[unitID].distanceToEnemyUnitLadders = (short)_minDistance;
            this->units[_bestEnemyUnitID].targetShootRelated = 0x19;
            return TRUE;
        }

    }
}
}
