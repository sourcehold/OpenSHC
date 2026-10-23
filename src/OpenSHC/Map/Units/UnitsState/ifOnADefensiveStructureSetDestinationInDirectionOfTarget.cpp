#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00540040
        BOOLEnum UnitsState::ifOnADefensiveStructureSetDestinationInDirectionOfTarget(int unitID)
        {
            int _buildingID = DAT_TileMapState::instance.BuildingLayer[DAT_UnitsState::instance.units[unitID].tile];
            if (_buildingID == 0) {
                return FALSE;
            }
            switch (DAT_BuildingsState::instance.buildings[_buildingID].buildingType) {
            case OpenSHC::Map::Buildings::BT_MANORHOUSE:
            case OpenSHC::Map::Buildings::BT_STONEKEEP:
            case OpenSHC::Map::Buildings::BT_STRONGHOLD:
            case OpenSHC::Map::Buildings::BT_KEEPFOUR:
            case OpenSHC::Map::Buildings::BT_KEEPFIVE:
            case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
            case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
            case OpenSHC::Map::Buildings::BT_WOODGATE1:
            case OpenSHC::Map::Buildings::BT_TOWER1:
            case OpenSHC::Map::Buildings::BT_TOWER2:
            case OpenSHC::Map::Buildings::BT_TOWER3:
            case OpenSHC::Map::Buildings::BT_TOWER4:
            case OpenSHC::Map::Buildings::BT_TOWER5:
                break;
            default:
                return FALSE;
            }
            int _targetX;
            int _targetY;
            if (DAT_UnitsState::instance.units[unitID].targetingType == OpenSHC::Map::Units::UIT_LIGHT_PITCH) {
                _targetX = DAT_TileMapState::instance
                               .pitchDitches[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                               .x;
                _targetY = DAT_TileMapState::instance
                               .pitchDitches[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                               .y;
            } else if (DAT_UnitsState::instance.units[unitID].targetingType
                == OpenSHC::Map::Units::UIT_ATTACK_BUILDING) {
                _targetX = (short)DAT_BuildingsState::instance
                               .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                               .x;
                _targetY = (short)DAT_BuildingsState::instance
                               .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                               .y;
            } else if (DAT_UnitsState::instance.units[unitID].targetingType == OpenSHC::Map::Units::UIT_ATTACK_LAND
                || DAT_UnitsState::instance.units[unitID].shootTargetedUnit == -2) {
                _targetX = DAT_UnitsState::instance.units[unitID].shootTargetMicroX / 8;
                _targetY = DAT_UnitsState::instance.units[unitID].shootTargetMicroY / 8;
            } else {
                _targetX = DAT_UnitsState::instance.units[DAT_UnitsState::instance.units[unitID].shootTargetedUnit].x;
                _targetY = DAT_UnitsState::instance.units[DAT_UnitsState::instance.units[unitID].shootTargetedUnit].y;
            }
            int _freeTileX = -1;
            int _freeTileY = -1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findClosestFreeTileNearUnitOnBuilding,
                DAT_PathFindingState::ptr)(_buildingID, unitID, _targetX, _targetY, &_freeTileX, &_freeTileY);
            if (DAT_UnitsState::instance.units[unitID].x == _freeTileX
                && DAT_UnitsState::instance.units[unitID].y == _freeTileY) {
                return FALSE;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                unitID, _freeTileX, _freeTileY, 0);
            DAT_UnitsState::instance.units[unitID].state.generic
                = (OpenSHC::Map::Units::States::US_APPEAR | OpenSHC::Map::Units::States::US_IDLEUnk);
            return TRUE;
        }

    }
}
}
