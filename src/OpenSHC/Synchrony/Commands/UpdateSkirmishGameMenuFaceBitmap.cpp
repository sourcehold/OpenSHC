#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004863A0
    void Commands::UpdateSkirmishGameMenuFaceBitmap()
    {
        void* pvVar1;
        int iVar2;
        int iVar3;
        int local_8c;
        int local_88;
        undefined1 local_84[64];
        undefined1 auStack_44[64];
        DAT_GameSynchronyState::instance.DAT_CommandSize = 0x88;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            iVar3 = DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                + (DAT_GameCore::instance.lordIconUnk + -2) * 0x42;
            iVar2 = 0;
            do {
                local_84[iVar2] = *(undefined1*)((int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94
                    + iVar2 * 2 + iVar3 * 0x80);
                auStack_44[iVar2] = *(undefined1*)((int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94
                    + iVar2 * 2 + iVar3 * 0x80 + 1);
                iVar2 = iVar2 + 1;
            } while (iVar2 < 0x40);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(local_84, (size_t)((int)(128)),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            ;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&local_88, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&local_8c, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            if (local_8c - 1U < 8) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(local_84, (size_t)((int)(128)),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                pvVar1 = DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94;
                local_88 = local_88 + (local_8c + 19) * 0x42;
                iVar3 = 0;
                do {
                    *(undefined1*)((int)pvVar1 + iVar3 * 2 + local_88 * 0x80) = local_84[iVar3];
                    *(undefined1*)((int)pvVar1 + iVar3 * 2 + local_88 * 0x80 + 1) = auStack_44[iVar3];
                    iVar3 = iVar3 + 1;
                } while (iVar3 < 0x40);
                DAT_TextureRenderCoreObject::instance.field69_0x98[local_8c + 0x13] = 0x2100;
            }
        };
    }

}
}
