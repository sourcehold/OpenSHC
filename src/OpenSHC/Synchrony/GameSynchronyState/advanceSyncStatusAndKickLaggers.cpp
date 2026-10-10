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
        piVar4 = DAT_GameSynchronyState::instance.receivedSyncStatusByPlayerUnk + 1;
        DAT_GameSynchronyState::instance
            .receivedSyncStatusByPlayerUnk[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 2;
        iVar3 = 1;
        piVar1 = piVar4;
        while (piVar1[-0x404f9] == -1 || *piVar1 == 2) {
            iVar3 = iVar3 + 1;
            piVar1 = piVar1 + 1;
            if (8 < iVar3) {
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                    Commands::GCT_SET_SYNC_STATUS_0);
            }
        }
        if (DAT_GameSynchronyState::instance.announcementReceivedBool) {
            DVar2 = timeGetTime();
            if (DVar2 - DAT_GameSynchronyState::instance.announcementReceiveTime < 0xafc9) {}
            iVar3 = 1;
            do {
                if ((piVar4[-0x404f9] != -1) && (*piVar4 != 2)) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0x3f;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = iVar3;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(Commands::GCT_LEAVE_GAME);
                    *piVar4 = 2;
                }
                iVar3 = iVar3 + 1;
                piVar4 = piVar4 + 1;
            } while (iVar3 < 9);
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(Commands::GCT_SET_SYNC_STATUS_0);
        }
        DVar2 = timeGetTime();
        if (DVar2 - DAT_GameSynchronyState::instance.announcementReceiveTime < 0xea61) {}
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(Commands::GCT_KILL_GAME);
    }

}
}
