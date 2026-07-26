#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Game::Resources::ResourceTypeInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      Walks the AIC resource acquisition preference order (up to 25 entries in
       DAT_ResourceAcquisitionPreferenceOrder) and attempts to buy the first resource for which the
       player has a non-zero resourcesToAcquireArray entry and meets one of the spending conditions:
       popularity is below the AIC minimum threshold (only checked for the first 4 entries), the AI is
       nervous, or the canStartSpending flag is set. If the AI is nervous, entries 0-11 (non-weapon
       resources) are skipped entirely so it only buys weapons. A special override fires first inside
       the loop: if the building-destroy tracker is non-zero AND the player has fewer than 20 wood, the
       resource type is forced to RT_WOOD regardless of the preference order. Before calling buyGoods()
       the required gold is computed via getBuyPrice(); if the AI cannot afford the purchase it calls
       requestGoods() from a teammate at double the desired amount instead. On a successful purchase
       resourcesToAcquireArray for that resource is cleared and the function returns immediately,
       buying at most one resource type per call. */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D39B0
    void AICState ::buyRequiredGoods(int param_1)

    {

        AITypeInt AVar1;

        int amount;

        int playerID;

        int iVar2;

        BOOLEnum BVar3;

        ResourceTypeInt resourceType;

        playerID = param_1;

        /*
            buying */

        AVar1 = DAT_GameState::instance.playerDataArray[param_1].aiType;

        if (AVar1 == OpenSHC::AI::AIT_NULL) {

            return;
        }

        /*
            reused! playerID now means a counter */

        param_1 = 0;

        do {

            resourceType = DAT_SkirmishDefinedData::instance.DAT_ResourceAcqusitionPreferenceOrder[param_1];

            /*
                  If nervous, only buy from entry 12 onwards, which are weapons */

            if ((DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker < 1) || (12 < param_1)) {

                if ((DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker != 0)
                    && (DAT_GameState::instance.playerDataArray[playerID].currentResources[2] < 20)) {

                    /*
                              if short on wood, buy wood! */

                    resourceType = OpenSHC::Game::Resources::RT_WOOD;
                }

                amount = DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[resourceType];

                if ((amount != 0)
                    && ((((param_1 < 4
                              && (DAT_GameState::instance.playerDataArray[playerID].popularity
                                  < *(int*)((int)this + (AVar1 + ~OpenSHC::AI::AIT_NULL) * 0x2a4 + 0x18)))
                             || (0 < DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker))
                        || (DAT_GameState::instance.playerDataArray[playerID].canStartSpending != 0)))) {

                    iVar2 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getBuyPrice, DAT_GameState::ptr)(
                        playerID, (int)((int)(resourceType)), amount);

                    if (DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf] < iVar2) {

                        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::requestGoods, this)(
                            playerID, (ResourceType)((int)(resourceType)), amount * 2);

                    }

                    else {

                        BVar3 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::buyGoods, this)(
                            playerID, (ResourceType)((int)(resourceType)), amount);

                        if (BVar3 != FALSE) {

                            DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[resourceType] = 0;

                            return;
                        }
                    }
                }
            }

            param_1 = param_1 + 1;

        } while (param_1 < 25);

        return;
    }

}
}
