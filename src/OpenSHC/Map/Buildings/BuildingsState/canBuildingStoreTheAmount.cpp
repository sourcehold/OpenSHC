#include "../BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040BF40
        int BuildingsState::canBuildingStoreTheAmount(int buildingID, ResourceType resourceType, int storageLimit)
        {
            int const storedAmount = this->buildings[buildingID].resources[resourceType];
            for (int otherType = 1; otherType < 25; ++otherType) {
                if (this->buildings[buildingID].resources[otherType] != 0 && otherType != resourceType) {
                    return 0;
                }
            }
            if (storedAmount >= storageLimit) {
                return 0;
            }
            return storageLimit - storedAmount;
        }

    }
}
}
