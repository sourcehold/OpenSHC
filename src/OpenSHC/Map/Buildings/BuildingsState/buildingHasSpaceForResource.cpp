#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040BE70
        BOOLEnum BuildingsState::buildingHasSpaceForResource(int buildingID, ResourceType resourceType)
        {
            // A building only stores a single resource type at a time
            if (this->buildings[buildingID].currentNumberOfResource != 0
                && this->buildings[buildingID].resources[resourceType] == 0) {
                return FALSE;
            }
            if (this->buildings[buildingID].currentNumberOfResource == 0) {
                return TRUE;
            }
            return (BOOLEnum)(this->buildings[buildingID].resources[resourceType]
                < DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[resourceType]);
        }

    }
}
}
