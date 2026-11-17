#include "../Commands.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048A510
    void Commands::SendResyncUnknown()
    {
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        // the part's number and one part of the data, 14566 bytes at most
        DAT_GameSynchronyState::instance.DAT_CommandSize = 14570;
        // parts 0 to 17 are the map and time state from syncedStateBase on, part 18 is its last 16 bytes and part 19
        // is the AIV state's map info
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 < 18) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)((char*)&DAT_GameState::instance.mapAndTime.syncedStateBase
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam0 * 14566,
                    14566, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            } else if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 18) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)((char*)&DAT_GameState::instance.mapAndTime.syncedStateBase
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam0 * 14566,
                    16, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            } else if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 19) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&DAT_AIVState::instance.mapExtraInfo,
                    sizeof(DAT_AIVState::instance.mapExtraInfo), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            return;
        }
        // only the clients take the host's copy
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE
            || DAT_GameSynchronyState::instance.isHost) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        // the text names the part by its offset in the map and time state; nothing reads it
        char partName[1000];
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 < 18) {
            // "Glob %d"
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(partName, s_Glob__d_005a74a0,
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 * 14566
                    + offsetof(OpenSHC::Game::State::MapAndTimeState, syncedStateBase));
            MACRO_CALL(OpenSHC::Synchrony_Func::MemCopyFromParameter)(
                (char*)&DAT_GameState::instance.mapAndTime.syncedStateBase
                    + DAT_GameSynchronyState::instance.DAT_GameCommandParam0 * 14566,
                14566, DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
        } else if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 18) {
            // "Glob %d"
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(partName, s_Glob__d_005a74a0,
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 * 14566
                    + offsetof(OpenSHC::Game::State::MapAndTimeState, syncedStateBase));
            MACRO_CALL(OpenSHC::Synchrony_Func::MemCopyFromParameter)(
                (char*)&DAT_GameState::instance.mapAndTime.syncedStateBase
                    + DAT_GameSynchronyState::instance.DAT_GameCommandParam0 * 14566,
                16, DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
        } else if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 19) {
            MACRO_CALL(OpenSHC::Synchrony_Func::MemCopyFromParameter)((char*)&DAT_AIVState::instance.mapExtraInfo,
                sizeof(DAT_AIVState::instance.mapExtraInfo), DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
        }
    }

}
}
