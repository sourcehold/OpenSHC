#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00480BE0
    void Commands::AnnounceTeamsAndPositions()
    {
        // three values of the sender's slot, whether the sender is the host, the nine teams and the eight positions
        DAT_GameSynchronyState::instance.DAT_CommandSize = 33;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_GameSynchronyState::instance
                    .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.currentPlayerSlotID],
                sizeof(DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[0]),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_GameSynchronyState::instance.currentAIArray[DAT_GameSynchronyState::instance.currentPlayerSlotID],
                sizeof(DAT_GameSynchronyState::instance.currentAIArray[0]),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_GameSynchronyState::instance
                    .aiVariationArray[DAT_GameSynchronyState::instance.currentPlayerSlotID],
                sizeof(DAT_GameSynchronyState::instance.aiVariationArray[0]),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.isHost,
                sizeof(DAT_GameSynchronyState::instance.isHost), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_PlayerGroupArray,
                sizeof(DAT_GameSynchronyState::instance.DAT_PlayerGroupArray),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.playerPositionsArray,
                sizeof(DAT_GameSynchronyState::instance.playerPositionsArray),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE
            || DAT_GameSynchronyState::instance.protocolInvokerPlayerID < 1
            || DAT_GameSynchronyState::instance.protocolInvokerPlayerID > 8) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(
            &DAT_GameSynchronyState::instance
                .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.protocolInvokerPlayerID],
            sizeof(DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[0]),
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(
            &DAT_GameSynchronyState::instance.currentAIArray[DAT_GameSynchronyState::instance.currentPlayerSlotID],
            sizeof(DAT_GameSynchronyState::instance.currentAIArray[0]),
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(
            &DAT_GameSynchronyState::instance.aiVariationArray[DAT_GameSynchronyState::instance.currentPlayerSlotID],
            sizeof(DAT_GameSynchronyState::instance.aiVariationArray[0]),
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        BOOLEnum senderIsHost;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&senderIsHost, sizeof(senderIsHost),
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        char receivedGroups[9];
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(receivedGroups, sizeof(receivedGroups),
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.playerPositionsArray,
            sizeof(DAT_GameSynchronyState::instance.playerPositionsArray),
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        // only the host's teams are taken over
        if (senderIsHost) {
            memcpy(DAT_GameSynchronyState::instance.DAT_PlayerGroupArray, receivedGroups,
                sizeof(DAT_GameSynchronyState::instance.DAT_PlayerGroupArray));
        }
    }

}
}
