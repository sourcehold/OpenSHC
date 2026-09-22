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
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == AITA_NULL)
            return TRUE;
        if (resourceType == Game::Resources::RT_GOLD)
            return FALSE;
        if (DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType]
            < this->aics[DAT_GameState::instance.playerDataArray[playerID].aiType - 1].minimumGoodsRequiredAfterTrade
                + buffer)
            return FALSE;
        return TRUE;
    }
}
}
