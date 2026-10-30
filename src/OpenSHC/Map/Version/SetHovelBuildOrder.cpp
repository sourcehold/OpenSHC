#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A340
    void Version::SetHovelBuildOrder()
    {
        short buildOrder = 0;
        for (int buildingID = 1; buildingID < 2000; ++buildingID) {
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState != (BuildingLogicalState)0
                && DAT_BuildingsState::instance.buildings[buildingID].buildingType == Buildings::BT_HOVEL) {
                DAT_BuildingsState::instance.buildings[buildingID].buildMonthOrBuildOrder = buildOrder;
                buildOrder += 1;
                // hovelVisualStyle is cleared as two 16-bit halves
                ((short*)&DAT_BuildingsState::instance.buildings[buildingID].hovelVisualStyle)[0] = 0;
                ((short*)&DAT_BuildingsState::instance.buildings[buildingID].hovelVisualStyle)[1] = 0;
            }
        }
    }

}
}
