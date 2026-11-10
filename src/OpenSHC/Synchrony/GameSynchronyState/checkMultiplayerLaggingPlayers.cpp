#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00490480
    void GameSynchronyState::checkMultiplayerLaggingPlayers()
    {
        // the original reads some fields through the global instance rather than this, so they stay that way
        this->currentGameModeCopy_SEC_Section1106 = this->currentGameMode;
        if ((this->currentGameMode == Game::GM_SOLITARY)
            || (this->currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER)) {
            this->commandDelay = 0;
            return;
        }
        if (this->shouldSendAnnouncementUnk) {
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(Commands::GCT_UNKNOWN_93);
            this->shouldSendAnnouncementUnk = FALSE;
        }
        if ((!this->syncStatus) && (!this->saveRelated)) {
            if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
                // Only when every other player in the game has reported in.
                BOOLEnum allReported = TRUE;
                for (int player = 0; player < 9; ++player) {
                    if (this->currentPlayerFullIDArray[player] != -1
                        && player != DAT_GameSynchronyState::instance.currentPlayerSlotID
                        && this->connectionLagInfoArray[player].checkFor0 == 0) {
                        allReported = FALSE;
                    }
                }
                if (allReported) {
                    DWORD const now = timeGetTime();
                    for (int player = 0; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && player != DAT_GameSynchronyState::instance.currentPlayerSlotID
                            && this->connectionLagInfoArray[player].time != 0) {
                            if (15000 < (int)(now - this->connectionLagInfoArray[player].time) && this->isHost
                                && this->laggingPlayerIDUnk == 0) {
                                this->DAT_GameCommandParam0 = player;
                                this->laggingPlayerIDUnk = player;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_UNKNOWN_98);
                            }
                            if (60000 < (int)(now - this->connectionLagInfoArray[player].time)) {
                                this->kickDueToLagStatusUnk = 62;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::removePlayerFromLobby, this)(
                                    player);
                            }
                        }
                    }
                }
            }
            DWORD const currentTime = timeGetTime();
            if (1800 < (int)(currentTime - this->otherTime1)) {
                this->otherTime1 = currentTime;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendSyncPacket126, this)();
            }
            if (180 <= (int)(currentTime - this->now2)) {
                this->now2 = currentTime;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendSomeMultiplayerSyncMessageWithType, this)(0);
                if (0 < this->syncRelatedCountdown) {
                    --this->syncRelatedCountdown;
                }
            }
            return;
        }
        for (int player = 0; player < 9; ++player) {
            this->connectionLagInfoArray[player].time = 0;
        }
    }

}
}
