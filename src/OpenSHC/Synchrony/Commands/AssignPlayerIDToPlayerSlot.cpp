#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::Commands::GameCommandType;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00489410
    void Commands::AssignPlayerIDToPlayerSlot()
    {
        int iVar1;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 4;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        DAT_GameSynchronyState::instance.DAT_PlayerIDReceiver
            = DAT_GameSynchronyState::instance.DPLAYX_ReceivedPlayerID;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.protocolInvokerPlayerID, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.currentPlayerSlotID, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            iVar1 = DAT_GameCore::instance.lordIconUnk;
            DAT_GameSynchronyState::instance
                .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                = DAT_GameSynchronyState::instance.DPLAYX_PlayerHandle;
            if (iVar1 >= 2) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SHARE_AIV_HASH);
            }
            MACRO_CALL(OpenSHC::OS_Func::_memcpy)(
                (void*)((DAT_GameSynchronyState::instance.currentPlayerSlotID + 0x13) * 0x2100
                    + (int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94),
                (void*)((DAT_GameCore::instance.lordIconUnk + -2) * 0x2100
                    + (int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94),
                0x2100);
            DAT_TextureRenderCoreObject::instance
                .field69_0x98[DAT_GameSynchronyState::instance.currentPlayerSlotID + 0x13] = 0x2100;
        }
    }

}
}
