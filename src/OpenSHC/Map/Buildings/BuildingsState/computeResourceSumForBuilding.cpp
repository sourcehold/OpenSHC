#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C130
        uint BuildingsState::computeResourceSumForBuilding(int buildingID)
        {
            this->buildings[buildingID].currentNumberOfResource = 0;
            this->buildings[buildingID].currentLimitOfResource = 0;
            for (int resourceType = 1; resourceType < 25; ++resourceType) {
                this->buildings[buildingID].currentNumberOfResource
                    += this->buildings[buildingID].resources[resourceType];
                if (this->buildings[buildingID].resources[resourceType] != 0
                    && this->buildings[buildingID].currentLimitOfResource == 0) {
                    this->buildings[buildingID].currentLimitOfResource
                        = DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[resourceType];
                    this->buildings[buildingID].currentStoredResourceType = resourceType;
                }
            }
            return this->buildings[buildingID].currentNumberOfResource;
        }

    }
}
}
