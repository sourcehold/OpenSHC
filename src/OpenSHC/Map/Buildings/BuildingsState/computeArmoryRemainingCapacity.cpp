#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C0D0
        int BuildingsState::computeArmoryRemainingCapacity(int buildingID, int another)
        {
            int capacity = 50;
            if (this->buildings[buildingID].logicalState == BLS_NORMAL
                && this->buildings[buildingID].buildingType == BT_ARMORY) {
                for (int i = 0; i < 25; ++i) {
                    capacity -= this->buildings[buildingID].resources[i];
                }
            }
            if (capacity < 0) {
                capacity = 0;
            }
            return capacity;
        }

    }
}
}
