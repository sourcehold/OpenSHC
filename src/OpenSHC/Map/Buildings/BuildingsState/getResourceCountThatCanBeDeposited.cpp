#include "../BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040BFA0
        int BuildingsState::getResourceCountThatCanBeDeposited(
            int buildingID, undefined4 resourceType, int storageLimit)
        {
            int uVar1 = this->buildings[buildingID].currentNumberOfResource;
            if (storageLimit <= uVar1) {
                return 0;
            }
            return storageLimit - uVar1;
        }

    }
}
}
