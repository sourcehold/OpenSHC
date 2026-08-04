#include "OpenSHC/AI/AICState.func.hpp"
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
    void AICState ::sellExcessGoods(int param_1)
    {
        AITypeInt aiType = DAT_GameState::instance.playerDataArray[param_1].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL)
            return;

        int aicIndex = aiType - 1;
        AICSpecification& aic = this->aics[aicIndex];
        int nervousActions = DAT_GameState::instance.playerDataArray[param_1].aiNervousActionsTracker;
        int& goldResource = DAT_GameState::instance.playerDataArray[param_1].currentResources[0xf];
        int& popularity = DAT_GameState::instance.playerDataArray[param_1].popularity;

        for (int entryIndex = 0; entryIndex < 20; entryIndex = entryIndex + 1) {
            ResourceType resourceType = (OpenSHC::Game::Resources::ResourceType)DAT_SkirmishDefinedData::instance
                                            .AIResourceTradeAICMapping[entryIndex]
                                            .game;
            AIResourceTradeCategoryInt category
                = DAT_SkirmishDefinedData::instance.AIResourceTradeAICMapping[entryIndex].aic;
            int variance = aic.maxResourceVariance;
            int& currentResource = DAT_GameState::instance.playerDataArray[param_1].currentResources[resourceType];

            int amount;
            if (category == OpenSHC::AI::Trading::AIRTC_WOOD) {
                amount = aic.maxWood;
            } else if (category == OpenSHC::AI::Trading::AIRTC_FOOD) {
                amount = aic.maxFood;
            } else if (category == OpenSHC::AI::Trading::AIRTC_STONE) {
                amount = aic.maxStone;
            } else if (category == OpenSHC::AI::Trading::AIRTC_WEAPONS) {
                amount = aic.maxEquipment;
            } else if (category == OpenSHC::AI::Trading::AIRTC_ALE) {
                amount = aic.maxBeer;
            } else {
                amount = aic.maxResourceOther;
            }

            amount = amount + variance;

            if ((nervousActions > 0) && (goldResource < 0x1f4)) {

                if (category == OpenSHC::AI::Trading::AIRTC_FOOD) {
                    amount = amount / 4;
                } else {
                    amount = ((category != OpenSHC::AI::Trading::AIRTC_WEAPONS) - 1) & 10000;
                }
                variance = 0;

            } else {
                if (popularity < aic.criticalPopularity) {
                    if (category != OpenSHC::AI::Trading::AIRTC_FOOD) {
                        if (category == OpenSHC::AI::Trading::AIRTC_WEAPONS) {
                            amount = 0;
                        } else {
                            amount = amount / 4;
                        }
                    }
                    variance = 0;
                } else {
                    amount = amount
                        + DAT_GameState::instance.playerDataArray[param_1].resourcesToAcquireArray[resourceType];
                }
            }

            int* sellResourceList = &aic.sellResource01;
            for (int sellResourceIndex = 0; sellResourceIndex < 0xf; sellResourceIndex = sellResourceIndex + 1) {
                if (resourceType == sellResourceList[sellResourceIndex]) {
                    amount = 0;
                    variance = 0;
                    break;
                }
            }

            if (currentResource > amount) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sellGoods, this)(param_1, resourceType,
                    (DAT_GameState::instance.playerDataArray[param_1].currentResources[resourceType] - amount)
                        + variance);
                return;
            }
        }
    }
}
}
