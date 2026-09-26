#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040BFD0
        BuildingType BuildingsState::getBuildingStorageTypeForResourceType(ResourceType resourceType)
        {
            return (BuildingType)DAT_BuildingDefinedData::instance.StorageBuildingTypeArray[resourceType];
        }

    }
}
}
