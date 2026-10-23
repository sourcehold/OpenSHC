#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040BFA0
        int BuildingsState::getResourceCountThatCanBeDeposited(
            int buildingID, undefined4 resourceType, int storageLimit)
        {
            if (this->buildings[buildingID].currentNumberOfResource >= storageLimit) {
                return 0;
            }
            return storageLimit - this->buildings[buildingID].currentNumberOfResource;
        }

    }
}
}
