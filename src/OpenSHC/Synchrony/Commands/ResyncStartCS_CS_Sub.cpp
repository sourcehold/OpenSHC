#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048FC20
    void Commands::ResyncStartCS_CS_Sub()
    {
        DAT_GameSynchronyState::instance.DAT_CommandSize = 8;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            DAT_GameSynchronyState::instance
                .DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
                .time += 30;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        DAT_GameSynchronyState::instance.syncStatus = 10;
        MACRO_CALL_MEMBER(
            OpenSHC::Synchrony::GameSynchronyState_Func::recomputeHashesAndSendResync, DAT_GameSynchronyState::ptr)(1);
        DAT_GameSynchronyState::instance.resyncStartTime = timeGetTime();
        DAT_GameSynchronyState::instance.currentPacketTotalSize = 0;
        DAT_GameSynchronyState::instance.connectionInfoExpanded = FALSE;
        MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
            OpenSHC::UI::Enums::DEID_SOME_MULTIPLAYER_INFO_Unk_19, 1);
        DAT_GameSynchronyState::instance.field_0xbe8 = DAT_GameSynchronyState::instance.resyncStartTime;
        DAT_GameSynchronyState::instance.announcementReceiveTime = DAT_GameSynchronyState::instance.resyncStartTime;
        DAT_GameSynchronyState::instance.announcementReceivedBool = FALSE;
    }

}
}
