#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040BFE0
        int BuildingsState::getStorageBuildingForResourceTypeAndAmount(ResourceType resourceType, int amount, int owner)
        {
            BuildingType storageType
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingStorageTypeForResourceType,
                    this)(resourceType);
            for (int i = this->maxBuildingsCount - 1; i > 0; --i) {
                if (this->buildings[i].logicalState == BLS_NORMAL && this->buildings[i].buildingType == storageType
                    && this->buildings[i].owner == owner && this->buildings[i].resources[resourceType] >= amount) {
                    return i;
                }
            }
            return 0;
        }

    }
}
}
