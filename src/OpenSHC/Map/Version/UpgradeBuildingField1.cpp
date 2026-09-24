#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::Building;
    using OpenSHC::Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A0D0
    void Version::UpgradeBuildingField1()
    {
        for (int _buildingID = 1; _buildingID < 2000; _buildingID++) {
            if (DAT_BuildingsState::instance.buildings[_buildingID].logicalState != ((BuildingLogicalState)0)) {
                DAT_BuildingsState::instance.buildings[_buildingID].uidWhenPlaced
                    = DAT_BuildingsState::instance.buildings[_buildingID].uidPlaced;
            }
        }
    }

}
}
