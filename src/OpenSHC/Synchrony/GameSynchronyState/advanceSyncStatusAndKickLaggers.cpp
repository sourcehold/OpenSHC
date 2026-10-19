#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048F3D0
    void GameSynchronyState::advanceSyncStatusAndKickLaggers()
    {
        DWORD _now;
        int _player;
        this->receivedSyncStatusByPlayerUnk[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 2;
        for (_player = 1; _player < 9; _player = _player + 1) {
            if ((this->currentPlayerFullIDArray[_player] != -1)
                && (this->receivedSyncStatusByPlayerUnk[_player] != 2)) {
                if (this->announcementReceivedBool) {
                    _now = timeGetTime();
                    if (_now - this->announcementReceiveTime <= 45000) {
                        return;
                    }
                    for (_player = 1; _player < 9; _player = _player + 1) {
                        if ((this->currentPlayerFullIDArray[_player] != -1)
                            && (this->receivedSyncStatusByPlayerUnk[_player] != 2)) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _player;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 63;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(Commands::GCT_LEAVE_GAME);
                            this->receivedSyncStatusByPlayerUnk[_player] = 2;
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
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(Commands::GCT_SET_SYNC_STATUS_0);
    }

}
}
