#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00485E80
    void Commands::MapSendingRelated()
    {
        DAT_GameSynchronyState::instance.DAT_CommandSize = 1;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 1,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        char readBuffer;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&readBuffer, 1, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        if (!DAT_GameSynchronyState::instance.isHost) {
            return;
        }
        DAT_GameSynchronyState::instance
            .mapSendRequestStatePerPlayer[DAT_GameSynchronyState::instance.protocolInvokerPlayerID] = 2;
        if (readBuffer == 1
            && DAT_GameSynchronyState::instance
                    .mapSendingFileHandles[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]
                != NULL) {
            DAT_GameSynchronyState::instance
                .mapSendingByteBufferAddress[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]
                = DAT_GameSynchronyState::instance.mapSendingFileSize;
        }
    }

}
}
