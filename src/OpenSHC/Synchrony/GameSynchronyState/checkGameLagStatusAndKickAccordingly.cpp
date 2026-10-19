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
        int* piVar1;
        DWORD _now2;
        DWORD _now1;
        int _player;
        for (piVar1 = DAT_GameSynchronyState::instance.announcementReceivedByPlayer + 1;
             (int)piVar1 < (int)(DAT_GameSynchronyState::instance.announcementReceivedByPlayer + 9);
             piVar1 = piVar1 + 1) {
            if (*piVar1 == 0) {
                if (this->announcementReceivedBool) {
                    _now2 = timeGetTime();
                    if (_now2 - this->announcementReceiveTime <= 0xafc8) {
                        return;
                    }
                    for (_player = 1; _player < 9; _player = _player + 1) {
                        if (DAT_GameSynchronyState::instance.announcementReceivedByPlayer[_player] == 0) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _player;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0x3f;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(Commands::GCT_LEAVE_GAME);
                            this->receivedSyncStatusByPlayerUnk[_player] = 2;
                        }
                    }
                    break;
                }
                _now1 = timeGetTime();
                if (_now1 - this->announcementReceiveTime <= 0xafc8) {
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
