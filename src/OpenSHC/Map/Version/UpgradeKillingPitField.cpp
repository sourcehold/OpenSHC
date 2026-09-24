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

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A5C0
    void Version::UpgradeKillingPitField()
    {
        for (int _buildingID = 1; _buildingID < 2000; _buildingID++) {
            if ((DAT_BuildingsState::instance.buildings[_buildingID].logicalState != ((BuildingLogicalState)0))
                && (DAT_BuildingsState::instance.buildings[_buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_KILLINGPIT)) {
                DAT_BuildingsState::instance.buildings[_buildingID].killingPitField = 0;
            }
        }
    }

}
}
