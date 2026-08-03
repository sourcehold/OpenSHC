#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::Game::GameMode;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names */

    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names */

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D10B0
    void AICState ::someChatMessageSelection()

    {

        BOOLEnum BVar1;

        DWORD DVar2;

        int iVar3;

        int iVar4;

        int iVar5;

        int iVar6;

        int aiStack_24[9];

        BVar1 = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();

        if ((BVar1 != FALSE)
            && (DAT_GameSynchronyState::instance.DAT_CurrentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {

            if (this->aiTauntResponseTimeWindow == 0) {

                return;
            }

            DVar2 = timeGetTime();

            if (DVar2 - this->aiTauntResponseTimeWindow < 2000) {

                return;
            }

            iVar6 = 0;

            iVar3 = 0;

            iVar4 = 3;

            do {

                if ((*(int*)((int)DAT_GameSynchronyState::instance.currentAIArray + iVar3 + 4) != 0)
                    && (*(int*)((int)DAT_GameState::instance.mapAndTime.playerTeams + iVar3 + 4)
                        != DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])) {

                    aiStack_24[iVar6] = iVar4 + -2;

                    iVar6 = iVar6 + 1;
                }

                if ((*(int*)((int)DAT_GameSynchronyState::instance.currentAIArray + iVar3 + 8) != 0)
                    && (*(int*)((int)DAT_GameState::instance.mapAndTime.playerTeams + iVar3 + 8)
                        != DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])) {

                    aiStack_24[iVar6] = iVar4 + -1;

                    iVar6 = iVar6 + 1;
                }

                if ((*(int*)((int)DAT_GameSynchronyState::instance.currentAIArray + iVar3 + 0xc) != 0)
                    && (*(int*)((int)DAT_GameState::instance.mapAndTime.playerTeams + iVar3 + 0xc)
                        != DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])) {

                    aiStack_24[iVar6] = iVar4;

                    iVar6 = iVar6 + 1;
                }

                if ((*(int*)((int)DAT_GameSynchronyState::instance.currentAIArray + iVar3 + 0x10) != 0)
                    && (*(int*)((int)DAT_GameState::instance.mapAndTime.playerTeams + iVar3 + 0x10)
                        != DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])) {

                    aiStack_24[iVar6] = iVar4 + 1;

                    iVar6 = iVar6 + 1;
                }

                iVar5 = iVar4 + 2;

                iVar3 = iVar3 + 0x10;

                iVar4 = iVar4 + 4;

            } while (iVar5 < 9);

            if (0 < iVar6) {

                iVar3 = 0;

                iVar4 = 0;

                if (0 < iVar6) {

                    do {

                        iVar3 = iVar3
                            + DAT_SkirmishDefinedData::instance
                                  .MaxBreachTribes[DAT_GameState::instance.playerDataArray[aiStack_24[iVar4]].aiType
                                      + OpenSHC::AI::AIT_FREDERICK]
                                  .tribeType;

                        iVar4 = iVar4 + 1;

                    } while (iVar4 < iVar6);

                    if (iVar3 != 0) {

                        iVar5 = (int)SEC_RNG::instance.currentNumber1;

                        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();

                        iVar5 = iVar5 % iVar3;

                        iVar4 = 0;

                        do {

                            iVar3 = aiStack_24[iVar4];

                            iVar5 = iVar5
                                - DAT_SkirmishDefinedData::instance
                                      .MaxBreachTribes[DAT_GameState::instance.playerDataArray[iVar3].aiType
                                          + OpenSHC::AI::AIT_FREDERICK]
                                      .tribeType;

                            if (iVar5 < 0) {

                                DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = -2
                                    - DAT_SkirmishDefinedData::instance
                                          .MaxBreachTribes[DAT_GameState::instance.playerDataArray[iVar3].aiType
                                              + OpenSHC::AI::AIT_FREDERICK]
                                          .tribeCount;

                                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;

                                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;

                                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;

                                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;

                                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;

                                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;

                                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;

                                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;

                                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = iVar3;

                                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_TAUNT_OR_CHAT);

                                this->aiTauntResponseTimeWindow = 0;

                                return;
                            }

                            iVar4 = iVar4 + 1;

                        } while (iVar4 < iVar6);
                    }
                }
            }
        }

        this->aiTauntResponseTimeWindow = 0;

        return;
    }

}
}
