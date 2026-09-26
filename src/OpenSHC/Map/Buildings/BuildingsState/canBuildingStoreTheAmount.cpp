#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::Resources::ResourceType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040BF40
        int BuildingsState::canBuildingStoreTheAmount(int buildingID, ResourceType resourceType, int storageLimit)
        {
            int stored = this->buildings[buildingID].resources[resourceType];
            // The building may not store any other resource type
            for (int i = OpenSHC::Game::Resources::RT_LOGS; i < 25; ++i) {
                if (this->buildings[buildingID].resources[i] != 0 && i != resourceType) {
                    return 0;
                }
            }
            if (stored >= storageLimit) {
                return 0;
            }
            return storageLimit - stored;
        }

    }
}
}
