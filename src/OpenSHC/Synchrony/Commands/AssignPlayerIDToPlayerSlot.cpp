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

    // FUNCTION: STRONGHOLDCRUSADER 0x00489410
    void Commands::AssignPlayerIDToPlayerSlot()
    {
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
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.currentPlayerSlotID, 4,
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        int const lordIcon = DAT_GameCore::instance.lordIconUnk;
        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
            = DAT_GameSynchronyState::instance.DPLAYX_PlayerHandle;
        if (lordIcon >= 2) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_SHARE_AIV_HASH);
        }
        // the chosen lord's face goes into the player's own face slot
        MACRO_CALL(OpenSHC::OS_Func::_memcpy)(DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94
                + (DAT_GameSynchronyState::instance.currentPlayerSlotID + 19) * 66 * 64,
            DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94
                + (DAT_GameCore::instance.lordIconUnk - 2) * 66 * 64,
            66 * 64 * sizeof(ushort));
        DAT_TextureRenderCoreObject::instance.bitmapFaceSizes[DAT_GameSynchronyState::instance.currentPlayerSlotID + 19]
            = 66 * 64 * sizeof(ushort);
    }

}
}
