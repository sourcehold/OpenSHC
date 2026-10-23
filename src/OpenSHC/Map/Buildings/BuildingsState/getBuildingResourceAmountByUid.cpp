#include "../BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00409330
        int BuildingsState::getBuildingResourceAmountByUid(int buildingID, int buildingUID, ResourceType resourceType)
        {
            if (this->buildings[buildingID].uid != buildingUID) {
                return 0;
            }
            return this->buildings[buildingID].resources[resourceType];
        }

    }
}
}
