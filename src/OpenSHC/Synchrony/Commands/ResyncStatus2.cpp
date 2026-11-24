#include "../Commands.func.hpp"

#include "OpenSHC/Commands/GameCommandScheduling.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004843F0
    void Commands::ResyncStatus2()
    {
        DAT_GameSynchronyState::instance.DAT_CommandSize = 0;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            return;
        }
        if ((DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE)
            && (DAT_GameSynchronyState::instance.isHost)) {
            DAT_GameSynchronyState::instance
                .receivedSyncStatusByPlayerUnk[DAT_GameSynchronyState::instance.protocolInvokerPlayerID] = 2;
            DAT_GameSynchronyState::instance.announcementReceiveTime = timeGetTime();
            DAT_GameSynchronyState::instance.announcementReceivedBool = TRUE;
        }
    }

}
}
