#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0054C4F0
        int UnitsState::handleUnitMovementWhenTargetingBuildings(int unitID)
        {
            if (this->units[unitID].targetedBuildingTile == 0) {
                return 0;
            }
            int _directionStep = 1;
            if ((DAT_TileMapState::instance.LogicLayer[this->units[unitID].targetedBuildingTile] & 0x100U) != 0) {
                _directionStep = 2;
            }
            uint _buildingTile = 0;
            int _directionOfBuilding = 0;
            for (; _directionOfBuilding <= 7; _directionOfBuilding += _directionStep) {
                _buildingTile
                    = DAT_TileMapState::instance.directionTranslationMatrix[this->units[unitID].y][_directionOfBuilding]
                    + this->units[unitID].tile;
                if (_buildingTile == this->units[unitID].targetedBuildingTile) {
                    break;
                }
            }
            if (_directionOfBuilding > 7) {
                return 0;
            }
            uint _isDefensiveStructure = DAT_TileMapState::instance.LogicLayer[_buildingTile] & 0x100;
            if (_isDefensiveStructure == 0 && (DAT_TileMapState::instance.LogicLayer[_buildingTile] & 0x40000000U) == 0
                && DAT_TileMapState::instance.BuildingLayer[_buildingTile] == 0) {
                return -1;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::ifAnyUnitOnSameTileIsLadder, this)(
                    this->units[unitID].tile)
                == FALSE) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState, this)(unitID);
                if (this->units[unitID].movementRelated > 7) {
                    this->units[unitID].destinationX_2Unk = this->units[unitID].x;
                    this->units[unitID].destinationY_2Unk = this->units[unitID].y;
                    return 1;
                }
            } else if (_isDefensiveStructure != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationNearTargetedBuilding, this)(
                    unitID, 0);
            }
            return 0;
        }

    }
}
}
