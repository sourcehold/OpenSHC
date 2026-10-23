#include "../AICState.func.hpp"

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

    // FUNCTION: STRONGHOLDCRUSADER 0x004D10B0
    void AICState::someChatMessageSelection()
    {
        int candidates[9];
        int candidateCount;
        int total;
        int i;
        int playerID;

        if ((MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE)
            && (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {

            if (this->aiTauntResponseTimeWindow == 0) {
                return;
            }

            if (timeGetTime() - this->aiTauntResponseTimeWindow <= 2000) {
                return;
            }

            candidateCount = 0;
            // Players 1..8, unrolled 4 at a time. The outer loop has to step by 4 and the inner 4 can be
            // left to the compiler, which unrolls them into the same instructions as four written-out
            // copies. A plain 1..8 loop does not work (0.92 -> 0.67, and the same for every spelling of
            // it): MSVC unrolls all 8 and, with the trip count known, constant-folds every index into an
            // absolute address and an immediate. The original keeps the index in a register, so its
            // source had an induction variable surviving the unroll - which is what stepping by 4 gives.
            for (playerID = 1; playerID < 9; playerID += 4) {
                for (int offset = 0; offset < 4; offset++) {
                    if (DAT_GameSynchronyState::instance.currentAIArray[playerID + offset] != 0
                        && DAT_GameState::instance.mapAndTime.playerTeams[playerID + offset]
                            != DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
                        candidates[candidateCount] = playerID + offset;
                        candidateCount++;
                    }
                }
            }

            if (candidateCount > 0) {
                total = 0;
                // NOTE: 'i = total' keeps the (redundant) loop entry check of the original.
                for (i = total; i < candidateCount; i++) {
                    total += DAT_SkirmishDefinedData::instance
                                 .MaxBreachTribes[DAT_GameState::instance.playerDataArray[candidates[i]].aiType
                                     + OpenSHC::AI::AIT_FREDERICK]
                                 .tribeType;
                }

                if (total != 0) {
                    int roll = (int)SEC_RNG::instance.currentNumber1;
                    MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                    roll = roll % total;

                    for (i = 0; i < candidateCount; i++) {
                        playerID = candidates[i];
                        roll -= DAT_SkirmishDefinedData::instance
                                    .MaxBreachTribes[DAT_GameState::instance.playerDataArray[playerID].aiType
                                        + OpenSHC::AI::AIT_FREDERICK]
                                    .tribeType;
                        if (roll < 0) {
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                            DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = -2
                                - DAT_SkirmishDefinedData::instance
                                      .MaxBreachTribes[DAT_GameState::instance.playerDataArray[playerID].aiType
                                          + OpenSHC::AI::AIT_FREDERICK]
                                      .tribeCount;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = playerID;
                            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_TAUNT_OR_CHAT);
                            break;
                        }
                    }
                }
            }
        }

        this->aiTauntResponseTimeWindow = 0;
    }

}
}
