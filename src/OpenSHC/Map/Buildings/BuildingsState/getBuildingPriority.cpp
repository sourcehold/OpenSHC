#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F700
        int BuildingsState::getBuildingPriority(int buildingType, int hasBurningBuilding)
        {
            // Low number means high priority
            if (hasBurningBuilding != 0) {
                for (int i = 0; i < 30; ++i) {
                    if (DAT_BuildingDefinedData::instance.BuildingPrioritiesWhenFire[i] == buildingType) {
                        return i;
                    }
                }
                return 30;
            }

            for (int i = 0; i < 30; ++i) {
                if (DAT_BuildingDefinedData::instance.BuildingPrioritiesWhenNoFire[i] == buildingType) {
                    return i;
                }
            }
            return 30;
        }

    }
}
}
