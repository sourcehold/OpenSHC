#include "../BuildingsState.func.hpp"

#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040BFD0
        BuildingType BuildingsState::getBuildingStorageTypeForResourceType(ResourceType resourceType)
        {
            return (BuildingType)(DAT_BuildingDefinedData::instance.StorageBuildingTypeArray[resourceType]);
        }

    }
}
}
