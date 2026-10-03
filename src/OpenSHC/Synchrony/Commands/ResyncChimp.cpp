#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

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
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0048A0E0
    void Commands::ResyncChimp()
    {
        int sVar1;
        int _unitID;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 1172;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            sVar1 = (short)DAT_UnitsState::instance.units[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                        .isSelected;
            DAT_UnitsState::instance.units[DAT_GameSynchronyState::instance.DAT_GameCommandParam0].isSelected = 0;
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                DAT_UnitsState::instance.units + DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 0x490,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_UnitsState::instance.units[DAT_GameSynchronyState::instance.DAT_GameCommandParam0].isSelected
                = (short)sVar1;
            return;
        }
        if ((DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE)
            && (DAT_GameSynchronyState::instance.isHost == FALSE)) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            _unitID = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
            sVar1 = (short)DAT_UnitsState::instance.units[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                        .isSelected;
            DAT_UnitsState::instance.units[DAT_GameSynchronyState::instance.DAT_GameCommandParam0].isSelected = 0;
            MACRO_CALL(OpenSHC::Synchrony_Func::MemCopyFromParameter)(
                (char*)(DAT_UnitsState::instance.units + _unitID), (size_t)((int)(1168)), (undefined4)((int)(_unitID)));
            DAT_UnitsState::instance.units[DAT_GameSynchronyState::instance.DAT_GameCommandParam0].isSelected
                = (short)sVar1;
        }
    }

}
}
