#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040BFE0
        int BuildingsState::getStorageBuildingForResourceTypeAndAmount(ResourceType resourceType, int amount, int owner)
        {
            BuildingType const storageType
                = MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingStorageTypeForResourceType, this)(resourceType);
            for (int buildingID = this->maxBuildingsCount - 1; buildingID > 0; --buildingID) {
                if (this->buildings[buildingID].logicalState == BLS_NORMAL
                    && this->buildings[buildingID].buildingType == storageType
                    && this->buildings[buildingID].owner == owner
                    && this->buildings[buildingID].resources[resourceType] >= amount) {
                    return buildingID;
                }
            }
            return 0;
        }

    }
}
}
