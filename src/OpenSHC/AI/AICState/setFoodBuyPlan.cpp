#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB060
    void AICState::setFoodBuyPlan(int playerID)
    {
        int aiType;
        int aiConfigIndex;
        int minimumStock;

        aiType = DAT_GameState::ptr->playerDataArray[playerID].aiType;

        // Early return if not an AI player (human player has aiType == 0)
        if (aiType == 0) {
            return;
        }

        // Get AI configuration index (convert 1-based to 0-based index)
        aiConfigIndex = aiType - 1;

        // Check each food type and queue purchase if current stock is below minimum

        // Apples: special handling with >= 0 check (allows -1 to disable)
        minimumStock = this->DAT_AICArray[aiConfigIndex].minimumApples;
        if (minimumStock >= 0
            && DAT_GameState::ptr->playerDataArray[playerID].currentResources[ResourceType::RT_APPLE] < minimumStock) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_APPLE]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }

        // Cheese: standard check with > 0
        minimumStock = this->DAT_AICArray[aiConfigIndex].minimumCheese;
        if (minimumStock > 0
            && DAT_GameState::ptr->playerDataArray[playerID].currentResources[ResourceType::RT_CHEESE] < minimumStock) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_CHEESE]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }

        // Bread: standard check with > 0
        minimumStock = this->DAT_AICArray[aiConfigIndex].minimumBread;
        if (minimumStock > 0
            && DAT_GameState::ptr->playerDataArray[playerID].currentResources[ResourceType::RT_BREAD] < minimumStock) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_BREAD]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }

        // Wheat: standard check with > 0
        minimumStock = this->DAT_AICArray[aiConfigIndex].minimumWheat;
        if (minimumStock > 0
            && DAT_GameState::ptr->playerDataArray[playerID].currentResources[ResourceType::RT_WHEAT] < minimumStock) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_WHEAT]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }

        // Hops: standard check with > 0
        minimumStock = this->DAT_AICArray[aiConfigIndex].minimumHop;
        if (minimumStock > 0
            && DAT_GameState::ptr->playerDataArray[playerID].currentResources[ResourceType::RT_HOPS] < minimumStock) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_HOPS]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }
    }
}
}
