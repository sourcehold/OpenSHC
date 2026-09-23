#include "../AICState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D39B0
    void AICState::buyRequiredGoods(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL)
            return;
        int aicIndex = aiType - 1;

        for (int i = 0; i < 25; i++) {
            int resourceType = DAT_SkirmishDefinedData::instance.ResourceAcquisitionPreferenceOrder[i];
            if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker > 0 && i < 12)
                continue;

            if (DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker != 0
                && DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_WOOD] < 20)
                resourceType = Game::Resources::RT_WOOD;

            int amount = DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[resourceType];
            if (amount == 0)
                continue;
            if ((i > 3
                    || DAT_GameState::instance.playerDataArray[playerID].popularity
                        >= this->aics[aicIndex].criticalPopularity)
                && DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker <= 0
                && DAT_GameState::instance.playerDataArray[playerID].canStartSpending == 0)
                continue;

            if (DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD]
                < MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getBuyPrice, DAT_GameState::ptr)(
                    playerID, resourceType, amount)) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::requestGoods, this)(
                    playerID, (ResourceType)resourceType, amount * 2);
                continue;
            }

            if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::buyGoods, this)(
                    playerID, (ResourceType)resourceType, amount)
                != FALSE) {
                DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[resourceType] = 0;
                return;
            }
        }
    }

}
}
