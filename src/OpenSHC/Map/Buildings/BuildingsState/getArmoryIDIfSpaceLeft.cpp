#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C060
        uint BuildingsState::getArmoryIDIfSpaceLeft(
            uint buildingID, undefined4 resourceID, int playerID, int resourceCount)
        {
            if (this->buildings[buildingID].buildingType != BT_ARMORY) {
                return 0;
            }
            if (this->buildings[buildingID].logicalState != BLS_NORMAL) {
                return 0;
            }
            if (this->buildings[buildingID].owner != playerID) {
                return 0;
            }
            int capacity = 50;
            for (int resourceType = 0; resourceType < 25; ++resourceType) {
                capacity -= this->buildings[buildingID].resources[resourceType];
            }
            if (capacity < resourceCount) {
                return 0;
            }
            return buildingID;
        }

    }
}
}
