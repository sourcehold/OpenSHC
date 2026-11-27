#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C0D0
        int BuildingsState::computeArmoryRemainingCapacity(int buildingID, int param_2)
        {
            int capacity = 50;
            if (this->buildings[buildingID].logicalState == BLS_NORMAL
                && this->buildings[buildingID].buildingType == BT_ARMORY) {
                for (int resourceType = 0; resourceType < 25; ++resourceType) {
                    capacity -= this->buildings[buildingID].resources[resourceType];
                }
                if (capacity >= 0) {
                    return capacity;
                }
            }
            return 0;
        }

    }
}
}
