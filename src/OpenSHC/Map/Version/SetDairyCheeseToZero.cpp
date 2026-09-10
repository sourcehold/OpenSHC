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

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A2B0
    void Version::SetDairyCheeseToZero()
    {
        for (int _buildingID = 1; _buildingID < 2000; _buildingID++) {
            if ((DAT_BuildingsState::instance.buildings[_buildingID].logicalState != ((BuildingLogicalState)0))
                && (DAT_BuildingsState::instance.buildings[_buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_DAIRYFARM)) {
                DAT_BuildingsState::instance.buildings[_buildingID].flagonsOfAleOrCheeseOrReleaseDogs = 0;
            }
        }
    }

}
}
