#include "../GameSynchronyState.func.hpp"

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
        this->syncStatus10Related[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
        for (int _player = 1; _player < 9; ++_player) {
            if ((this->currentPlayerFullIDArray[_player] != -1) && (this->syncStatus10Related[_player] == 0)) {
                if (this->announcementReceivedBool) {
                    if (timeGetTime() - this->announcementReceiveTime <= 45000) {
                        return;
                    }
                    for (int _laggard = 1; _laggard < 9; ++_laggard) {
                        if ((this->currentPlayerFullIDArray[_laggard] != -1)
                            && (this->syncStatus10Related[_laggard] == 0)) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _laggard;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 63;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(Commands::GCT_LEAVE_GAME);
                            this->syncStatus10Related[_laggard] = 1;
                        }
                    }
                    break;
                }
                if (timeGetTime() - this->announcementReceiveTime <= 60000) {
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
        // A bug in the original, reproduced on purpose: HashContainerElement is 12 ints wide, so
        // the two domain loops below run 14 domains over a 12-slot-per-player row, and a domain of
        // 12 or 13 reads the next player's first two slots instead of this player's. The desync
        // flag for those two domains therefore compares the wrong values. Redefining HashContainer
        // would not help - the overrun is in the original's loop bound, not in how the field is
        // typed - so the bounds stay exactly as they are and the aliasing stays visible here.
        // Measured: the two loops share this counter because declaring one in each for header
        // costs the match (100.0% -> 97.8%).
        int _player;
        for (int _domain = 0; _domain < 14; ++_domain) {
            this->sharedDesyncFlags[_domain] = 0;
            for (_player = 1; _player < 9; ++_player) {
                if (this->currentPlayerFullIDArray[_player] != -1) {
                    _hash = this->HASH_PartialHashPerPlayer.player[_player].domain[_domain];
                    break;
                }
            }
            for (_player = 1; _player < 9; ++_player) {
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
