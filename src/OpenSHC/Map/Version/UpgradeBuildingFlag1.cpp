#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A100
    void Version::UpgradeBuildingFlag1()
    {
        for (int buildingID = 1; buildingID < 2000; ++buildingID) {
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState != (BuildingLogicalState)0) {
                DAT_BuildingsState::instance.buildings[buildingID].flag1
                    = DAT_BuildingDefinedData::instance
                          .BuildingFlag1Defaults[DAT_BuildingsState::instance.buildings[buildingID].buildingType]
                          .shortValue;
                DAT_BuildingsState::instance.buildings[buildingID].flag2
                    = DAT_BuildingDefinedData::instance
                          .BuildingFlag2Defaults[DAT_BuildingsState::instance.buildings[buildingID].buildingType]
                          .shortValue;
            }
        }
    }

}
}
