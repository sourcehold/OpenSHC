#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048DA60
    void GameSynchronyState::checkLagAndSyncStatus()
    {
        DWORD _now;
        int _player;
        int _domain;
        this->syncStatus10Related[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
        for (_player = 1; _player < 9; _player = _player + 1) {
            if ((this->currentPlayerFullIDArray[_player] != -1) && (this->syncStatus10Related[_player] == 0)) {
                if (this->announcementReceivedBool) {
                    _now = timeGetTime();
                    if (_now - this->announcementReceiveTime <= 45000) {
                        return;
                    }
                    for (_player = 1; _player < 9; _player = _player + 1) {
                        if ((this->currentPlayerFullIDArray[_player] != -1)
                            && (this->syncStatus10Related[_player] == 0)) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _player;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 63;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(Commands::GCT_LEAVE_GAME);
                            this->syncStatus10Related[_player] = 1;
                        }
                    }
                    break;
                }
                _now = timeGetTime();
                if (_now - this->announcementReceiveTime <= 60000) {
                    return;
                }
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_KILL_GAME);
                return;
            }
        }
        int _hash = 0;
        DAT_GameSynchronyState::instance.syncStatus = 1;
        DAT_GameSynchronyState::instance.field76_0xbe8 = DAT_GameSynchronyState::instance.resyncStartTime;
        DAT_GameSynchronyState::instance.announcementReceiveTime = DAT_GameSynchronyState::instance.resyncStartTime;
        DAT_GameSynchronyState::instance.announcementReceivedBool = FALSE;
        // The original runs 14 domains over a 12-slot-per-player block, so a domain above 11
        // deliberately reads into the next player's slots; keep the bounds exactly as they are.
        for (_domain = 0; _domain < 14; _domain = _domain + 1) {
            this->sharedDesyncFlags[_domain] = 0;
            for (_player = 1; _player < 9; _player = _player + 1) {
                if (this->currentPlayerFullIDArray[_player] != -1) {
                    _hash = this->HASH_PartialHashPerPlayer.player[_player].domain[_domain];
                    break;
                }
            }
            for (_player = 1; _player < 9; _player = _player + 1) {
                if (this->currentPlayerFullIDArray[_player] != -1
                    && _hash != this->HASH_PartialHashPerPlayer.player[_player].domain[_domain]) {
                    this->sharedDesyncFlags[_domain] = 1;
                }
            }
        }
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            Commands::GCT_SHARE_SYNC_STATUS);
    }

}
}
