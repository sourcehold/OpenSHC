#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F700
        int BuildingsState::getBuildingPriority(int buildingType, int hasBurningBuilding)
        {
            if (hasBurningBuilding != 0) {
                for (int priority = 0; priority < 30; ++priority) {
                    if (DAT_BuildingDefinedData::instance.BuildingPrioritiesWhenFire[priority] == buildingType) {
                        return priority;
                    }
                }
                return 30;
            }
            for (int priority = 0; priority < 30; ++priority) {
                if (DAT_BuildingDefinedData::instance.BuildingPrioritiesWhenNoFire[priority] == buildingType) {
                    return priority;
                }
            }
            return 30;
        }

    }
}
}
