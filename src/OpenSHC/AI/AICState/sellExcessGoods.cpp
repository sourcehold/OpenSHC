#include "../AICState.func.hpp"

#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/Trading/AIResourceTradeCategory.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Game::Player::PlayerData;
    using OpenSHC::Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D1D60
    void AICState::sellExcessGoods(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL) {
            return;
        }

        int aicIndex = aiType - 1;
        for (int i = 0; i < countof(DAT_SkirmishDefinedData::instance.AIResourceTradeAICMapping); ++i) {
            ResourceType resourceType
                = (ResourceType)DAT_SkirmishDefinedData::instance.AIResourceTradeAICMapping[i].game;
            int variance = this->aics[aicIndex].maxResourceVariance;
            // one flat offset from playerDataArray[0] for currentResources and resourcesToAcquireArray: the
            // original computes (the player's ints + the resource) * 4 once and uses it for both arrays
            int resourceOffset = (playerID * (sizeof(PlayerData) / sizeof(int)) + resourceType) * sizeof(int);

            int amount;
            if (DAT_SkirmishDefinedData::instance.AIResourceTradeAICMapping[i].aic
                == OpenSHC::AI::Trading::AIRTC_WOOD) {
                amount = this->aics[aicIndex].maxWood;
            } else if (DAT_SkirmishDefinedData::instance.AIResourceTradeAICMapping[i].aic
                == OpenSHC::AI::Trading::AIRTC_FOOD) {
                amount = this->aics[aicIndex].maxFood;
            } else if (DAT_SkirmishDefinedData::instance.AIResourceTradeAICMapping[i].aic
                == OpenSHC::AI::Trading::AIRTC_STONE) {
                amount = this->aics[aicIndex].maxStone;
            } else if (DAT_SkirmishDefinedData::instance.AIResourceTradeAICMapping[i].aic
                == OpenSHC::AI::Trading::AIRTC_WEAPONS) {
                amount = this->aics[aicIndex].maxEquipment;
            } else if (DAT_SkirmishDefinedData::instance.AIResourceTradeAICMapping[i].aic
                == OpenSHC::AI::Trading::AIRTC_ALE) {
                amount = this->aics[aicIndex].maxBeer;
            } else {
                amount = this->aics[aicIndex].maxResourceOther;
            }
            amount += variance;

            if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker > 0
                && DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD] < 500) {
                // Nervous and low on gold: keep a quarter of the food and up to 10000 weapons, sell everything else
                if (DAT_SkirmishDefinedData::instance.AIResourceTradeAICMapping[i].aic
                    == OpenSHC::AI::Trading::AIRTC_FOOD) {
                    amount /= 4;
                } else if (DAT_SkirmishDefinedData::instance.AIResourceTradeAICMapping[i].aic
                    == OpenSHC::AI::Trading::AIRTC_WEAPONS) {
                    amount = 10000;
                } else {
                    amount = 0;
                }
                variance = 0;
            } else if (DAT_GameState::instance.playerDataArray[playerID].popularity
                < this->aics[aicIndex].criticalPopularity) {
                // Critical popularity: keep all food, sell all weapons, keep a quarter of everything else
                if (DAT_SkirmishDefinedData::instance.AIResourceTradeAICMapping[i].aic
                    != OpenSHC::AI::Trading::AIRTC_FOOD) {
                    if (DAT_SkirmishDefinedData::instance.AIResourceTradeAICMapping[i].aic
                        == OpenSHC::AI::Trading::AIRTC_WEAPONS) {
                        amount = 0;
                    } else {
                        amount /= 4;
                    }
                }
                variance = 0;
            } else {
                amount += *(
                    int*)((char*)DAT_GameState::instance.playerDataArray[0].resourcesToAcquireArray + resourceOffset);
            }

            // Resources the AIC always sells are kept at zero
            for (int j = 0; j < 15; ++j) {
                if (resourceType == (&this->aics[aicIndex].sellResource01)[j]) {
                    amount = 0;
                    variance = 0;
                    break;
                }
            }

            if (*(int*)((char*)DAT_GameState::instance.playerDataArray[0].currentResources + resourceOffset) > amount) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sellGoods, this)(playerID, resourceType,
                    ((int*)DAT_GameState::instance.playerDataArray[0]
                            .currentResources)[playerID * (sizeof(PlayerData) / sizeof(int)) + resourceType]
                        - amount + variance);
                return;
            }
        }
    }
}
}
