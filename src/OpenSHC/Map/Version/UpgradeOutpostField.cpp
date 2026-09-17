#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::Building;
    using OpenSHC::Map::Buildings::BuildingLogicalState;
    using OpenSHC::Map::Buildings::BuildingType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A710
    void Version::UpgradeOutpostField()
    {
        for (int _buildingID = 1; _buildingID < 2000; _buildingID++) {
            if ((DAT_BuildingsState::instance.buildings[_buildingID].logicalState != ((BuildingLogicalState)0))
                && ((DAT_BuildingsState::instance.buildings[_buildingID].buildingType
                        == OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN)
                    || (DAT_BuildingsState::instance.buildings[_buildingID].buildingType
                        == OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN))) {
                DAT_BuildingsState::instance.buildings[_buildingID].randomOutpostField = 0;
            }
        }
    }

}
}
