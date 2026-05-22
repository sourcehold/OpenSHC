#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AITypeA;
    using OpenSHC::Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB060
    void AICState::setFoodBuyPlan(int playerID)
    {

        int const aiType = DAT_GameState::ptr->playerDataArray[playerID].aiType;

        // Early return if not an AI player (human player has aiType == 0)
        if (aiType == AITypeA::AITA_NULL) {
            return;
        }

        // Get AI configuration index (convert 1-based to 0-based index)
        int const aiConfigIndex = aiType - 1;

        // Check each food type and queue purchase if current stock is below minimum

        // Apples: special handling with >= 0 check (allows -1 to disable)
        int const minimumApples = this->DAT_AICArray[aiConfigIndex].minimumApples;
        int* currentResources = DAT_GameState::ptr->playerDataArray[playerID].currentResources;
        if (minimumApples >= 0 && currentResources[ResourceType::RT_APPLE] < minimumApples) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_APPLE]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }

        // Cheese: standard check with > 0
        int const minimumCheese = this->DAT_AICArray[aiConfigIndex].minimumCheese;
        if (minimumCheese > 0 && currentResources[ResourceType::RT_CHEESE] < minimumCheese) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_CHEESE]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }

        // Bread: standard check with > 0
        int const minimumBread = this->DAT_AICArray[aiConfigIndex].minimumBread;
        if (minimumBread > 0 && currentResources[ResourceType::RT_BREAD] < minimumBread) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_BREAD]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }

        // Wheat: standard check with > 0
        int const minimumWheat = this->DAT_AICArray[aiConfigIndex].minimumWheat;
        if (minimumWheat > 0 && currentResources[ResourceType::RT_WHEAT] < minimumWheat) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_WHEAT]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }

        // Hops: standard check with > 0
        int const minimumHop = this->DAT_AICArray[aiConfigIndex].minimumHop;
        if (minimumHop > 0 && currentResources[ResourceType::RT_HOPS] < minimumHop) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_HOPS]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }
    }
}
}
