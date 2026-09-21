#include "../AICState.func.hpp"

#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/AI/Trading/AIResourceTradeCategory.hpp"
#include "OpenSHC/AI/Trading/AIResourceTradeCategoryInt.hpp"
#include "OpenSHC/AI/Trading/ResourceAICResourceMappingEntry.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::AI::AIC::AICSpecification;
    using OpenSHC::AI::Trading::AIResourceTradeCategory;
    using OpenSHC::AI::Trading::AIResourceTradeCategoryInt;
    using OpenSHC::AI::Trading::ResourceAICResourceMappingEntry;
    using OpenSHC::Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D1D60
    void AICState::sellExcessGoods(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL) {
            return;
        }

        int aicIndex = aiType - 1;
        int nervousActions = DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker;
        for (int i = 0; i < 20; i++) {
            ResourceType resourceType
                = (ResourceType)DAT_SkirmishDefinedData::instance.AIResourceTradeAICMapping[i].game;
            int category = DAT_SkirmishDefinedData::instance.AIResourceTradeAICMapping[i].aic;
            int variance = this->aics[aicIndex].maxResourceVariance;

            int amount;
            if (category == OpenSHC::AI::Trading::AIRTC_WOOD) {
                amount = this->aics[aicIndex].maxWood;
            } else if (category == OpenSHC::AI::Trading::AIRTC_FOOD) {
                amount = this->aics[aicIndex].maxFood;
            } else if (category == OpenSHC::AI::Trading::AIRTC_STONE) {
                amount = this->aics[aicIndex].maxStone;
            } else if (category == OpenSHC::AI::Trading::AIRTC_WEAPONS) {
                amount = this->aics[aicIndex].maxEquipment;
            } else if (category == OpenSHC::AI::Trading::AIRTC_ALE) {
                amount = this->aics[aicIndex].maxBeer;
            } else {
                amount = this->aics[aicIndex].maxResourceOther;
            }
            amount += variance;

            if (nervousActions > 0 && DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf] < 500) {
                // Nervous and low on gold: keep a quarter of the food and up to 10000 weapons, sell everything else
                if (category == OpenSHC::AI::Trading::AIRTC_FOOD) {
                    amount = amount / 4;
                } else if (category == OpenSHC::AI::Trading::AIRTC_WEAPONS) {
                    amount = 10000;
                } else {
                    amount = 0;
                }
                variance = 0;
            } else if (DAT_GameState::instance.playerDataArray[playerID].popularity
                < this->aics[aicIndex].criticalPopularity) {
                // Critical popularity: keep all food, sell all weapons, keep a quarter of everything else
                if (category != OpenSHC::AI::Trading::AIRTC_FOOD) {
                    if (category == OpenSHC::AI::Trading::AIRTC_WEAPONS) {
                        amount = 0;
                    } else {
                        amount = amount / 4;
                    }
                }
                variance = 0;
            } else {
                amount += DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[resourceType];
            }

            // Resources the AIC always sells are kept at zero
            for (int j = 0; j < 15; j++) {
                if (resourceType == (&this->aics[aicIndex].sellResource01)[j]) {
                    amount = 0;
                    variance = 0;
                    break;
                }
            }

            if (DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType] > amount) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sellGoods, this)(playerID, resourceType,
                    DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType] - amount
                        + variance);
                return;
            }
        }
    }
}
}
