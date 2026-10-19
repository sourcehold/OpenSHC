#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048F4C0
    void GameSynchronyState::checkGameLagStatusAndKickAccordingly()
    {
        for (int _slot = 1; _slot < 9; _slot = _slot + 1) {
            if (DAT_GameSynchronyState::instance.announcementReceivedByPlayer[_slot] == 0) {
                if (this->announcementReceivedBool) {
                    DWORD _now = timeGetTime();
                    if (_now - this->announcementReceiveTime <= 45000) {
                        return;
                    }
                    for (int _player = 1; _player < 9; _player = _player + 1) {
                        if (DAT_GameSynchronyState::instance.announcementReceivedByPlayer[_player] == 0) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _player;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 63;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(Commands::GCT_LEAVE_GAME);
                            this->receivedSyncStatusByPlayerUnk[_player] = 2;
                        }
                    }
                    break;
                }
                DWORD _now = timeGetTime();
                if (_now - this->announcementReceiveTime <= 45000) {
                    return;
                }
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_KILL_GAME);
                return;
            }
        }
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            Commands::GCT_CLOSE_MODAL_DIALOG_FOR_ALL);
    }

}
}
