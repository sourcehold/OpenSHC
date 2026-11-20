#include "../Commands.func.hpp"

#include "OpenSHC/Commands/GameCommandScheduling.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004850E0
    void Commands::BroadCastSyncRelatedStatus()
    {
        DAT_GameSynchronyState::instance.DAT_CommandSize = 0;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        DAT_GameSynchronyState::instance
            .syncRelatedStatusArray[DAT_GameSynchronyState::instance.protocolInvokerPlayerID] = 1;
        if (DAT_GameSynchronyState::instance.isHost) {
            DAT_GameSynchronyState::instance.announcementReceiveTime = timeGetTime();
            DAT_GameSynchronyState::instance.announcementReceivedBool = TRUE;
        }
    }

}
}
