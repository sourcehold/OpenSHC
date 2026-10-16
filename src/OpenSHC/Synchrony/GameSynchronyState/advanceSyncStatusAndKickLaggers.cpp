#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using WindowsHelper::Enums::BOOLEnum;

    /*
      Marks the current player's receivedSyncStatusByPlayerUnk as 2 and checks whether all connected   players have
      confirmed. If all confirmed, queues GCT_SET_SYNC_STATUS_0. If some players haven't   confirmed within the
      announcement timeout (0xAFC9ms), kicks them via GCT_LEAVE_GAME and then   queues GCT_SET_SYNC_STATUS_0. If the
      announcement itself was never received within a longer   timeout (0xEA61ms), queues GCT_KILL_GAME instead. renamed
      by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0048F3D0
    void GameSynchronyState::advanceSyncStatusAndKickLaggers()
    {
        int* piVar1;
        DWORD DVar2;
        int iVar3;
        int* piVar4;
        piVar4 = this->receivedSyncStatusByPlayerUnk + 1;
        this->receivedSyncStatusByPlayerUnk[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 2;
        iVar3 = 1;
        piVar1 = piVar4;
        while (piVar1[-0x404f9] == -1 || *piVar1 == 2) {
            iVar3 = iVar3 + 1;
            piVar1 = piVar1 + 1;
            if (9 <= iVar3) {
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                    Commands::GCT_SET_SYNC_STATUS_0);
                return;
            }
        }
        if (this->announcementReceivedBool) {
            DVar2 = timeGetTime();
            if (DVar2 - this->announcementReceiveTime <= 0xafc8) {
                return;
            }
            iVar3 = 1;
            do {
                if ((piVar4[-0x404f9] != -1) && (*piVar4 != 2)) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = iVar3;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0x3f;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(Commands::GCT_LEAVE_GAME);
                    *piVar4 = 2;
                }
                iVar3 = iVar3 + 1;
                piVar4 = piVar4 + 1;
            } while (iVar3 < 9);
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                Commands::GCT_SET_SYNC_STATUS_0);
            return;
        }
        DVar2 = timeGetTime();
        if (DVar2 - this->announcementReceiveTime <= 0xea60) {
            return;
        }
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            Commands::GCT_KILL_GAME);
    }

}
}
