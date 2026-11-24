#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048A350
    void Commands::SendResyncTribe()
    {
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 824;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            // the tribe goes out with its time cleared
            int const savedTime
                = DAT_TribesState::instance.tribes[DAT_GameSynchronyState::instance.DAT_GameCommandParam0].time;
            DAT_TribesState::instance.tribes[DAT_GameSynchronyState::instance.DAT_GameCommandParam0].time = 0;
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TribesState::instance.tribes[DAT_GameSynchronyState::instance.DAT_GameCommandParam0],
                sizeof(DAT_TribesState::instance.tribes[0]), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_TribesState::instance.tribes[DAT_GameSynchronyState::instance.DAT_GameCommandParam0].time = savedTime;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE
            || DAT_GameSynchronyState::instance.isHost) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        int const tribeID = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
        // the received tribe keeps this machine's time
        int const savedTime
            = DAT_TribesState::instance.tribes[DAT_GameSynchronyState::instance.DAT_GameCommandParam0].time;
        DAT_TribesState::instance.tribes[DAT_GameSynchronyState::instance.DAT_GameCommandParam0].time = 0;
        MACRO_CALL(OpenSHC::Synchrony_Func::MemCopyFromParameter)(
            (char*)&DAT_TribesState::instance.tribes[tribeID], sizeof(DAT_TribesState::instance.tribes[0]), tribeID);
        DAT_TribesState::instance.tribes[DAT_GameSynchronyState::instance.DAT_GameCommandParam0].time = savedTime;
    }

}
}
