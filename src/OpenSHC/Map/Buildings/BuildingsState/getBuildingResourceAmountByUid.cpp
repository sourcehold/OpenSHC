#include "../BuildingsState.func.hpp"

#include "OpenSHC/Game/Resources/ResourceType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::Resources::ResourceType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00409330
        int BuildingsState::getBuildingResourceAmountByUid(int buildingID, int param_2, ResourceType param_3)
        {
            if (this->buildings[buildingID].uid != param_2) {
                return 0;
            }
            return this->buildings[buildingID].resources[param_3];
        }

    }
}
}
