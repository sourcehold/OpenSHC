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
        DWORD DVar3;
        int _player;
        int _domain;
        this->syncStatus10Related[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
        for (_player = 1; _player < 9; _player = _player + 1) {
            if ((this->currentPlayerFullIDArray[_player] != -1) && (this->syncStatus10Related[_player] == 0)) {
                if (this->announcementReceivedBool) {
                    DVar3 = timeGetTime();
                    if (DVar3 - this->announcementReceiveTime <= 0xafc8) {
                        return;
                    }
                    for (_player = 1; _player < 9; _player = _player + 1) {
                        if ((this->currentPlayerFullIDArray[_player] != -1)
                            && (this->syncStatus10Related[_player] == 0)) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _player;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0x3f;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(Commands::GCT_LEAVE_GAME);
                            this->syncStatus10Related[_player] = 1;
                        }
                    }
                    break;
                }
                DVar3 = timeGetTime();
                if (DVar3 - this->announcementReceiveTime <= 0xea60) {
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
        for (_domain = 0; _domain < 14; _domain = _domain + 1) {
            this->sharedDesyncFlags[_domain] = 0;
            for (_player = 1; _player < 9; _player = _player + 1) {
                if (this->currentPlayerFullIDArray[_player] != -1) {
                    _hash = ((int*)&this->HASH_PartialHashPerPlayer)[_player * 12 + _domain];
                    break;
                }
            }
            for (_player = 1; _player < 9; _player = _player + 1) {
                if (this->currentPlayerFullIDArray[_player] != -1
                    && _hash != ((int*)&this->HASH_PartialHashPerPlayer)[_player * 12 + _domain]) {
                    this->sharedDesyncFlags[_domain] = 1;
                }
            }
        }
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            Commands::GCT_SHARE_SYNC_STATUS);
    }

}
}
