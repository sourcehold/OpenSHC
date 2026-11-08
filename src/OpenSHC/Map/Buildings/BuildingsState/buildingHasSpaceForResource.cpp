#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040BE70
        BOOLEnum BuildingsState::buildingHasSpaceForResource(int buildingID, ResourceType resourceType)
        {
            if (this->buildings[buildingID].currentNumberOfResource != 0
                && this->buildings[buildingID].resources[resourceType] == 0) {
                return FALSE;
            }
            if (this->buildings[buildingID].currentNumberOfResource == 0) {
                return TRUE;
            }
            return this->buildings[buildingID].resources[resourceType]
                < DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[resourceType];
        }

    }
}
}
