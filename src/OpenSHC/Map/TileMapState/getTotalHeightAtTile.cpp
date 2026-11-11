#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004FFB10
    uint TileMapState::getTotalHeightAtTile(int tile)
    {
        int buildingID = this->BuildingLayer[tile];
        if (buildingID != 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE) {
                return MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                           DAT_BuildingsState::ptr)(buildingID)
                    + this->DefaultHeightLayer[tile];
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL) {
                return MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                           DAT_BuildingsState::ptr)(buildingID)
                    + this->DefaultHeightLayer[tile];
            }
            return MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                       DAT_BuildingsState::ptr)(buildingID)
                + this->HeightLayer[tile];
        }
        return this->HeightLayer[tile];
    }

}
}
