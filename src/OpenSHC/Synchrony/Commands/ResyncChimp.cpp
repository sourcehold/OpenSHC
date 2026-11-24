#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048A0E0
    void Commands::ResyncChimp()
    {
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 1172;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            // the unit goes out unselected
            int const wasSelected
                = DAT_UnitsState::instance.units[DAT_GameSynchronyState::instance.DAT_GameCommandParam0].isSelected;
            DAT_UnitsState::instance.units[DAT_GameSynchronyState::instance.DAT_GameCommandParam0].isSelected = 0;
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_UnitsState::instance.units[DAT_GameSynchronyState::instance.DAT_GameCommandParam0],
                sizeof(DAT_UnitsState::instance.units[0]), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_UnitsState::instance.units[DAT_GameSynchronyState::instance.DAT_GameCommandParam0].isSelected
                = wasSelected;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE
            || DAT_GameSynchronyState::instance.isHost) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        int const unitID = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
        // the received unit keeps this machine's selection
        int const wasSelected
            = DAT_UnitsState::instance.units[DAT_GameSynchronyState::instance.DAT_GameCommandParam0].isSelected;
        DAT_UnitsState::instance.units[DAT_GameSynchronyState::instance.DAT_GameCommandParam0].isSelected = 0;
        MACRO_CALL(OpenSHC::Synchrony_Func::MemCopyFromParameter)(
            (char*)&DAT_UnitsState::instance.units[unitID], sizeof(DAT_UnitsState::instance.units[0]), unitID);
        DAT_UnitsState::instance.units[DAT_GameSynchronyState::instance.DAT_GameCommandParam0].isSelected = wasSelected;
    }

}
}
