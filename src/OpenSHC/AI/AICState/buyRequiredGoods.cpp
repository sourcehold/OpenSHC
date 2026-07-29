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

        AVar1 = DAT_GameState::instance.playerDataArray[param_1].aiType;

        if (AVar1 == OpenSHC::AI::AIT_NULL) {

            return;
        }

        param_1 = 0;

        do {

            resourceType = DAT_SkirmishDefinedData::instance.ResourceAcquisitionPreferenceOrder[param_1];

            if ((DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker <= 0) || (0xb < param_1)) {

                if ((DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker != 0)
                    && (DAT_GameState::instance.playerDataArray[playerID].currentResources[2] < 20)) {

                    resourceType = OpenSHC::Game::Resources::RT_WOOD;
                }

                amount = DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[resourceType];

                if ((amount != 0)
                    && ((((param_1 <= 3
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
