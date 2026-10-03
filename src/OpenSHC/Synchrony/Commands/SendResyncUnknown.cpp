#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnumShort": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0048A510
    void Commands::SendResyncUnknown()
    {
        char local_3ec[1000];
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 14570;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 < 0x12) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)((void*)((int)&DAT_GameState::instance.mapAndTime.field192_0x194
                                                     + DAT_GameSynchronyState::instance.DAT_GameCommandParam0 * 14566),
                    (size_t)((int)(14566)), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                return;
            }
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 0x12) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameState::instance.mapAndTime.startingTroops[7] + 0x10, 0x10,
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                return;
            }
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 0x13) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&DAT_AIVState::instance.mapExtraInfo, 0x330,
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                return;
            }
            return;
        } else if ((DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE)
            && (DAT_GameSynchronyState::instance.isHost == FALSE)) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 < 0x12) {
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                    local_3ec, "Glob %d", DAT_GameSynchronyState::instance.DAT_GameCommandParam0 * 0x38e6 + 0x194);
                MACRO_CALL(OpenSHC::Synchrony_Func::MemCopyFromParameter)(
                    (char*)((int)&DAT_GameState::instance.mapAndTime.field192_0x194
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam0 * 0x38e6),
                    (size_t)((int)(14566)), DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
                ;
            }
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 0x12) {
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_3ec, "Glob %d", 0x401c0);
                MACRO_CALL(OpenSHC::Synchrony_Func::MemCopyFromParameter)(
                    (char*)((int)&DAT_GameState::instance.mapAndTime.field192_0x194
                        + DAT_GameSynchronyState::instance.DAT_GameCommandParam0 * 0x38e6),
                    (size_t)((int)(16)), DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
                ;
            }
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 0x13) {
                MACRO_CALL(OpenSHC::Synchrony_Func::MemCopyFromParameter)(
                    (char*)&DAT_AIVState::instance.mapExtraInfo, (size_t)((int)(816)), 0x13);
            }
        };
    }

}
}
