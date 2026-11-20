#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004855C0
    void Commands::NotifyLaggingPlayer()
    {
        DAT_GameSynchronyState::instance.DAT_CommandSize = 2;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 2,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        short readBuffer;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&readBuffer, 2, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.laggingPlayerIDUnk = readBuffer;
        MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
            OpenSHC::UI::Enums::DEID_SOME_MULTIPLAYER_INFO_Unk_28, 1);
        DAT_GameSynchronyState::instance.lagNotificationCode = 0;
    }

}
}
