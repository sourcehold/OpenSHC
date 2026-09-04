#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::Building;
    using OpenSHC::Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A3C0
    void Version::UpgradeBuildingField2()
    {
        for (int _buildingID = 1; _buildingID < 2000; _buildingID++) {
            if (DAT_BuildingsState::instance.buildings[_buildingID].logicalState != ((BuildingLogicalState)0)) {
                DAT_BuildingsState::instance.buildings[_buildingID].field206_0x288 = 0;
                DAT_BuildingsState::instance.buildings[_buildingID].field188_0x264 = 0;
            }
        }
    }

}
}
