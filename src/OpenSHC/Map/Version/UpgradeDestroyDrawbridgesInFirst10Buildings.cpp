#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::Building;
    using OpenSHC::Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A460
    void Version::UpgradeDestroyDrawbridgesInFirst10Buildings()
    {
        for (int buildingID = 1; buildingID < 2000; ++buildingID) {
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState != (BuildingLogicalState)0
                && DAT_BuildingsState::instance.buildings[buildingID].buildingType == Buildings::BT_DRAWBRIDGE) {
                MACRO_CALL_MEMBER(TileMapState_Func::clearDrawBridgeWater, DAT_TileMapState::ptr)(
                    DAT_BuildingsState::instance.buildings[buildingID].x,
                    DAT_BuildingsState::instance.buildings[buildingID].y);
                MACRO_CALL_MEMBER(TileMapState_Func::clearBuildingDisplayFlagsAndEntities, DAT_TileMapState::ptr)(
                    buildingID, 1);
                int x = DAT_BuildingsState::instance.buildings[buildingID].x;
                int y = DAT_BuildingsState::instance.buildings[buildingID].y;
                int orientation = DAT_BuildingsState::instance.buildings[buildingID].buildingVariation;
                int owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(Building), 0, &DAT_BuildingsState::instance.buildings[buildingID]);
                DAT_TileMapState::instance.buildingPlacementFail = 0;
                DAT_TileMapState::instance.skipPlacementCheck = 1;
                MACRO_CALL_MEMBER(TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                    owner, x, y, Commands::M_MAPPER_DRAWBRIDGE, 5, orientation);
            }
        }
    }

}
}
