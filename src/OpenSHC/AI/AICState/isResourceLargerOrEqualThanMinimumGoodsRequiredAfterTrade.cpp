#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0520
    BOOLEnum AICState::isResourceLargerOrEqualThanMinimumGoodsRequiredAfterTrade(
        int playerID, ResourceType resourceType, int buffer)
    {
        int _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (_aiType == AITA_NULL) {
            return TRUE;
        }
        if (resourceType == Game::Resources::RT_GOLD) {
            return FALSE;
        }
        return (int)this->aics[_aiType - 1].minimumGoodsRequiredAfterTrade + buffer
            <= DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType];
    }
}
}
