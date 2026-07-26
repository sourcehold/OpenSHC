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

        AITypeInt AVar1;

        ResourceType resourceType;

        AIResourceTradeCategoryInt AVar2;

        int iVar3;

        uint uVar4;

        int iVar5;

        int iVar6;

        ResourceType* pRVar7;

        AIResourceTradeCategoryInt* local_18;

        AVar1 = DAT_GameState::instance.playerDataArray[param_1].aiType;

        if (AVar1 == OpenSHC::AI::AIT_NULL) {
            return;
        }

        iVar3 = (AVar1 + ~OpenSHC::AI::AIT_NULL) * 0x2a4;

        local_18 = &DAT_SkirmishDefinedData::instance.DAT_AIResourceTradeAICMapping[0].aic;

        do {

            resourceType
                = (OpenSHC::Game::Resources::ResourceType)((ResourceAICResourceMappingEntry*)(local_18 + -1))->game;

            AVar2 = *local_18;

            iVar6 = *(int*)((int)this + iVar3 + 0xc0);

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

            uVar4 = iVar5 + iVar6;

            if ((DAT_GameState::instance.playerDataArray[param_1].aiNervousActionsTracker <= 0)
                || (DAT_GameState::instance.playerDataArray[param_1].currentResources[0xf] >= 0x1f4)) {

                if (DAT_GameState::instance.playerDataArray[param_1].popularity < *(int*)((int)this + iVar3 + 0x18)) {

                    if (AVar2 != OpenSHC::AI::Trading::AIRTC_FOOD) {

                        if (AVar2 == OpenSHC::AI::Trading::AIRTC_WEAPONS) {
                            uVar4 = 0;
                            iVar6 = 0;
                            goto LAB_004d1e81;
                        }

                        uVar4 = (int)(uVar4 + ((int)uVar4 >> 0x1f & 3U)) >> 2;
                    }

                    iVar6 = 0;

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

        LAB_004d1e81:
            iVar5 = 0;

            pRVar7 = (ResourceType*)((int)this + iVar3 + 0xd4);

            do {
                if (resourceType == *pRVar7) {
                    uVar4 = 0;
                    iVar6 = 0;
                    break;
                }
                iVar5 = iVar5 + 1;
                pRVar7 = pRVar7 + 1;
            } while (iVar5 < 0xf);

            if ((int)uVar4 < DAT_GameState::instance.playerDataArray[param_1].currentResources[resourceType]) {

                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sellGoods, this)(param_1, resourceType,
                    (DAT_GameState::instance.playerDataArray[param_1].currentResources[resourceType] - uVar4) + iVar6);

                return;
            }

            local_18 = local_18 + 2;

            if (0xb4252b < (int)local_18) {
                return;
            }

        } while (true);
    }

}
}
