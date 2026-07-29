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
    using OpenSHC::AI::Trading::AIResourceTradeCategory;
    using OpenSHC::AI::Trading::AIResourceTradeCategoryInt;
    using OpenSHC::AI::Trading::ResourceAICResourceMappingEntry;
    using OpenSHC::Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D1D60
    void AICState ::sellExcessGoods(int param_1)
    {
        AITypeInt AVar1 = DAT_GameState::instance.playerDataArray[param_1].aiType;
        if (AVar1 == OpenSHC::AI::AIT_NULL)
            return;

        int iVar3 = (AVar1 + ~OpenSHC::AI::AIT_NULL) * 0x2a4;
        AIResourceTradeCategoryInt* local_18 = &DAT_SkirmishDefinedData::instance.AIResourceTradeAICMapping[0].aic;

        do {
            ResourceType resourceType
                = (OpenSHC::Game::Resources::ResourceType)((ResourceAICResourceMappingEntry*)(local_18 + -1))->game;
            AIResourceTradeCategoryInt AVar2 = *local_18;

            int iVar6 = *(int*)((int)this + iVar3 + 0xc0);
            int iVar5;
            if (AVar2 == OpenSHC::AI::Trading::AIRTC_WOOD) {
                iVar5 = *(int*)((int)this + iVar3 + 0xac);
            } else if (AVar2 == OpenSHC::AI::Trading::AIRTC_FOOD) {
                iVar5 = *(int*)((int)this + iVar3 + 0x80);
            } else if (AVar2 == OpenSHC::AI::Trading::AIRTC_STONE) {
                iVar5 = *(int*)((int)this + iVar3 + 0xb0);
            } else if (AVar2 == OpenSHC::AI::Trading::AIRTC_WEAPONS) {
                iVar5 = *(int*)((int)this + iVar3 + 0xb8);
            } else if (AVar2 == OpenSHC::AI::Trading::AIRTC_ALE) {
                iVar5 = *(int*)((int)this + iVar3 + 0xbc);
            } else {
                iVar5 = *(int*)((int)this + iVar3 + 0xb4);
            }

            uint uVar4 = iVar5 + iVar6;

            if ((DAT_GameState::instance.playerDataArray[param_1].aiNervousActionsTracker <= 0)
                || (DAT_GameState::instance.playerDataArray[param_1].currentResources[0xf] >= 0x1f4)) {

                if (DAT_GameState::instance.playerDataArray[param_1].popularity < *(int*)((int)this + iVar3 + 0x18)) {
                    if (AVar2 != OpenSHC::AI::Trading::AIRTC_FOOD) {
                        if (AVar2 == OpenSHC::AI::Trading::AIRTC_WEAPONS) {
                            uVar4 = 0;
                            iVar6 = 0;
                        } else {
                            uVar4 = (int)(uVar4 + ((int)uVar4 >> 0x1f & 3U)) >> 2;
                            iVar6 = 0;
                        }
                    } else {
                        iVar6 = 0;
                    }
                } else {
                    uVar4 = uVar4
                        + DAT_GameState::instance.playerDataArray[param_1].resourcesToAcquireArray[resourceType];
                }

            } else if (AVar2 == OpenSHC::AI::Trading::AIRTC_FOOD) {
                uVar4 = (int)(uVar4 + ((int)uVar4 >> 0x1f & 3U)) >> 2;
                iVar6 = 0;
            } else {
                uVar4 = (AVar2 != OpenSHC::AI::Trading::AIRTC_WEAPONS) - 1 & 10000;
                iVar6 = 0;
            }

            // Check no-sell list (was LAB_004d1e81)
            {
                int iVar5_2 = 0;
                ResourceType* pRVar7 = (ResourceType*)((int)this + iVar3 + 0xd4);
                do {
                    if (resourceType == *pRVar7) {
                        uVar4 = 0;
                        iVar6 = 0;
                        break;
                    }
                    iVar5_2 = iVar5_2 + 1;
                    pRVar7 = pRVar7 + 1;
                } while (iVar5_2 < 0xf);
            }

            if ((int)uVar4 < DAT_GameState::instance.playerDataArray[param_1].currentResources[resourceType]) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sellGoods, this)(param_1, resourceType,
                    (DAT_GameState::instance.playerDataArray[param_1].currentResources[resourceType] - uVar4) + iVar6);
                return;
            }

            local_18 = local_18 + 2;
            if (0xb4252b < (int)local_18)
                return;

        } while (true);
    }
}
}
