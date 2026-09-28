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
            if ((DAT_TileMapState::instance.LogicLayer[this->units[unitID].tile] & LogicHelpers::L_WALL_OR_GATEHOUSE)
                == 0) {
                return FALSE;
            }
            short _owner = this->units[unitID].owner;
            dword _areaOfUnit = (short)DAT_TileMapState::instance.PathConnectionLayer[this->units[unitID].tile];
            int _bestEnemyUnitID = 0;
            int _minDistance = 1000;
            for (int i = 0; i < DAT_GameState::instance.playerDataArray[_owner].enemies; ++i) {
                int _enemyUnitID = DAT_GameState::instance.playerDataArray[_owner].enemyIDArray[i];
                if (this->units[_enemyUnitID].unitType != OpenSHC::Map::Units::UT_E_LADDER) {
                    continue;
                }
                if (this->units[_enemyUnitID].state.generic != (UnitState)3) {
                    continue;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isUsableClimbWithinArea,
                        DAT_PathFindingState::ptr)((short)_areaOfUnit, this->units[_enemyUnitID].wallDataID)
                    == FALSE) {
                    continue;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findPositionForGivenClimbArea,
                    DAT_PathFindingState::ptr)(
                    (short)_areaOfUnit, this->units[_enemyUnitID].x, this->units[_enemyUnitID].y);
                int _distanceX;
                if (DAT_PathFindingState::instance.climbX < this->units[unitID].x) {
                    _distanceX = this->units[unitID].x - DAT_PathFindingState::instance.climbX;
                } else {
                    _distanceX = DAT_PathFindingState::instance.climbX - this->units[unitID].x;
                }
                int _distanceY;
                if (DAT_PathFindingState::instance.climbY < this->units[unitID].y) {
                    _distanceY = this->units[unitID].y - DAT_PathFindingState::instance.climbY;
                } else {
                    _distanceY = DAT_PathFindingState::instance.climbY - this->units[unitID].y;
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
                    this->climbY2 = DAT_PathFindingState::instance.climbY;
                    _bestEnemyUnitID = _enemyUnitID;
                    _minDistance = _distanceX;
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
