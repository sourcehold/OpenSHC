#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C130
        uint BuildingsState::computeResourceSumForBuilding(int buildingID)
        {
            this->buildings[buildingID].currentNumberOfResource = 0;
            this->buildings[buildingID].currentLimitOfResource = 0;
            for (int i = 1; i < 25; ++i) {
                this->buildings[buildingID].currentNumberOfResource += this->buildings[buildingID].resources[i];
                if (this->buildings[buildingID].resources[i] != 0
                    && this->buildings[buildingID].currentLimitOfResource == 0) {
                    this->buildings[buildingID].currentLimitOfResource
                        = DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[i];
                    this->buildings[buildingID].currentStoredResourceType = i;
                }
            }
            return this->buildings[buildingID].currentNumberOfResource;
        }

    }
}
}
