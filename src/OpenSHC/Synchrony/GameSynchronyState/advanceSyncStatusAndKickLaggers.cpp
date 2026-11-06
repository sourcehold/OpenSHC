#include "../GameSynchronyState.func.hpp"

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
        this->receivedSyncStatusByPlayerUnk[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 2;
        for (int _player = 1; _player < 9; ++_player) {
            if ((this->currentPlayerFullIDArray[_player] != -1)
                && (this->receivedSyncStatusByPlayerUnk[_player] != 2)) {
                if (this->announcementReceivedBool) {
                    if (timeGetTime() - this->announcementReceiveTime <= 45000) {
                        return;
                    }
                    for (int _laggard = 1; _laggard < 9; ++_laggard) {
                        if ((this->currentPlayerFullIDArray[_laggard] != -1)
                            && (this->receivedSyncStatusByPlayerUnk[_laggard] != 2)) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _laggard;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 63;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(Commands::GCT_LEAVE_GAME);
                            this->receivedSyncStatusByPlayerUnk[_laggard] = 2;
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
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(Commands::GCT_SET_SYNC_STATUS_0);
    }

}
}
