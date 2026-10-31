#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A2E0
    void Version::UpgradeTowerLogicLayer()
    {
        for (int buildingID = 1; buildingID < 2000; ++buildingID) {
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState != (BuildingLogicalState)0
                && (DAT_BuildingsState::instance.buildings[buildingID].buildingType == Buildings::BT_TOWER2
                    || DAT_BuildingsState::instance.buildings[buildingID].buildingType == Buildings::BT_TOWER3
                    || DAT_BuildingsState::instance.buildings[buildingID].buildingType == Buildings::BT_TOWER4
                    || DAT_BuildingsState::instance.buildings[buildingID].buildingType == Buildings::BT_TOWER5)) {
                MACRO_CALL_MEMBER(TileMapState_Func::upgradeTowerLogicLayer, DAT_TileMapState::ptr)(buildingID);
            }
        }
    }

}
}
