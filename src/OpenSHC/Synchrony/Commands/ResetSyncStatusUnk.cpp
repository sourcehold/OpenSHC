#include "../Commands.func.hpp"

#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00484450
    void Commands::ResetSyncStatusUnk()
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
        DAT_GameSynchronyState::instance.syncStatus = 0;
        DAT_GameSynchronyState::instance.flag_0xbec = 0;
        MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
            OpenSHC::UI::Enums::DEID_SOME_MULTIPLAYER_INFO_Unk_19, 0);
    }

}
}
