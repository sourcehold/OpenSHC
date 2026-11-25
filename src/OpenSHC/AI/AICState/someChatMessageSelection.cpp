#include "../AICState.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D10B0
    void AICState::someChatMessageSelection()
    {
        if (!MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()
            || (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
            this->aiTauntResponseTimeWindow = 0;
            return;
        }

        if (this->aiTauntResponseTimeWindow == 0) {
            return;
        }

        if (timeGetTime() - this->aiTauntResponseTimeWindow <= 2000) {
            return;
        }

        int candidates[9];
        int candidateCount = 0;
        // four players a step, the inner four left to the compiler (a plain 1..8 loop loses the match: 61%)
        for (int playerID = 1; playerID < countof(DAT_GameSynchronyState::instance.currentAIArray); playerID += 4) {
            for (int offset = 0; offset < 4; ++offset) {
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
            int total = 0;
            // from total, which keeps the original's redundant entry test
            for (int i = total; i < candidateCount; ++i) {
                total += DAT_SkirmishDefinedData::instance
                             .MaxBreachTribes[DAT_GameState::instance.playerDataArray[candidates[i]].aiType
                                 + OpenSHC::AI::AIT_FREDERICK]
                             .tribeType;
            }

            if (total != 0) {
                int roll = (int)SEC_RNG::instance.currentNumber1;
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                roll %= total;

                for (int i = 0; i < candidateCount; ++i) {
                    int const playerID = candidates[i];
                    roll -= DAT_SkirmishDefinedData::instance
                                .MaxBreachTribes[DAT_GameState::instance.playerDataArray[playerID].aiType
                                    + OpenSHC::AI::AIT_FREDERICK]
                                .tribeType;
                    if (roll < 0) {
                        for (int receiver = 1;
                            receiver < countof(DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray);
                            ++receiver) {
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[receiver] = 1;
                        }
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

        this->aiTauntResponseTimeWindow = 0;
    }

}
}
