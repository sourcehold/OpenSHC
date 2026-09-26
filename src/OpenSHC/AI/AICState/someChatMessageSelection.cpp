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
            // Players 1..8, manually unrolled by 4 in the original.
            for (playerID = 1; playerID < 9; playerID += 4) {
                if ((DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0)
                    && (DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                        != DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])) {
                    candidates[candidateCount] = playerID;
                    candidateCount++;
                }
                if ((DAT_GameSynchronyState::instance.currentAIArray[playerID + 1] != 0)
                    && (DAT_GameState::instance.mapAndTime.playerTeams[playerID + 1]
                        != DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])) {
                    candidates[candidateCount] = playerID + 1;
                    candidateCount++;
                }
                if ((DAT_GameSynchronyState::instance.currentAIArray[playerID + 2] != 0)
                    && (DAT_GameState::instance.mapAndTime.playerTeams[playerID + 2]
                        != DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])) {
                    candidates[candidateCount] = playerID + 2;
                    candidateCount++;
                }
                if ((DAT_GameSynchronyState::instance.currentAIArray[playerID + 3] != 0)
                    && (DAT_GameState::instance.mapAndTime.playerTeams[playerID + 3]
                        != DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])) {
                    candidates[candidateCount] = playerID + 3;
                    candidateCount++;
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
