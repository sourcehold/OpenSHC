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
        DWORD DVar2;
        int iVar3;
        this->receivedSyncStatusByPlayerUnk[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 2;
        for (iVar3 = 1; iVar3 < 9; iVar3 = iVar3 + 1) {
            if ((this->currentPlayerFullIDArray[iVar3] != -1)
                && (this->receivedSyncStatusByPlayerUnk[iVar3] != 2)) {
                if (this->announcementReceivedBool) {
                    DVar2 = timeGetTime();
                    if (DVar2 - this->announcementReceiveTime <= 0xafc8) {
                        return;
                    }
                    for (iVar3 = 1; iVar3 < 9; iVar3 = iVar3 + 1) {
                        if ((this->currentPlayerFullIDArray[iVar3] != -1)
                            && (this->receivedSyncStatusByPlayerUnk[iVar3] != 2)) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = iVar3;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0x3f;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(Commands::GCT_LEAVE_GAME);
                            this->receivedSyncStatusByPlayerUnk[iVar3] = 2;
                        }
                    }
                    break;
                }
                DVar2 = timeGetTime();
                if (DVar2 - this->announcementReceiveTime <= 0xea60) {
                    return;
                }
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            Commands::GCT_KILL_GAME);
                return;
            }
        }
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
            Commands::GCT_SET_SYNC_STATUS_0);
    }

}
}
