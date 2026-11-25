#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {
    namespace Commands {

        // FUNCTION: STRONGHOLDCRUSADER 0x00480B10
        void __cdecl CommandCheckSync()
        {
            DAT_GameSynchronyState::instance.DAT_CommandSize = 10;
            DAT_GameSynchronyState::instance
                .DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
                .time = 0;

            // Sending serializes the local player's lag indicator, hash total and match time;
            // executing deserializes the same three values for the player who sent the command.
            // Early returns with the player index held in a const local measured 51% instead of 100%, keep the
            // if/else-if.
            if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
                MACRO_CALL_MEMBER(
                    GameSynchronyState_Func::serializeOrDeserializeCommandParameter, DAT_GameSynchronyState::ptr)(
                    &DAT_GameSynchronyState::instance
                        .DAT_LagIndicatorPerPlayer[DAT_GameSynchronyState::instance.currentPlayerSlotID],
                    sizeof(DAT_GameSynchronyState::instance
                            .DAT_LagIndicatorPerPlayer[DAT_GameSynchronyState::instance.currentPlayerSlotID]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                MACRO_CALL_MEMBER(
                    GameSynchronyState_Func::serializeOrDeserializeCommandParameter, DAT_GameSynchronyState::ptr)(
                    &DAT_GameSynchronyState::instance
                        .HASH_HashTotal[DAT_GameSynchronyState::instance.currentPlayerSlotID],
                    sizeof(DAT_GameSynchronyState::instance
                            .HASH_HashTotal[DAT_GameSynchronyState::instance.currentPlayerSlotID]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                MACRO_CALL_MEMBER(
                    GameSynchronyState_Func::serializeOrDeserializeCommandParameter, DAT_GameSynchronyState::ptr)(
                    &DAT_GameSynchronyState::instance
                        .DAT_PlayerMatchTimes[DAT_GameSynchronyState::instance.currentPlayerSlotID],
                    sizeof(DAT_GameSynchronyState::instance
                            .DAT_PlayerMatchTimes[DAT_GameSynchronyState::instance.currentPlayerSlotID]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            } else if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
                MACRO_CALL_MEMBER(
                    GameSynchronyState_Func::serializeOrDeserializeCommandParameter, DAT_GameSynchronyState::ptr)(
                    &DAT_GameSynchronyState::instance
                        .DAT_LagIndicatorPerPlayer[DAT_GameSynchronyState::instance.protocolInvokerPlayerID],
                    sizeof(DAT_GameSynchronyState::instance
                            .DAT_LagIndicatorPerPlayer[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(
                    GameSynchronyState_Func::serializeOrDeserializeCommandParameter, DAT_GameSynchronyState::ptr)(
                    &DAT_GameSynchronyState::instance
                        .HASH_HashTotal[DAT_GameSynchronyState::instance.protocolInvokerPlayerID],
                    sizeof(DAT_GameSynchronyState::instance
                            .HASH_HashTotal[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(
                    GameSynchronyState_Func::serializeOrDeserializeCommandParameter, DAT_GameSynchronyState::ptr)(
                    &DAT_GameSynchronyState::instance
                        .DAT_PlayerMatchTimes[DAT_GameSynchronyState::instance.protocolInvokerPlayerID],
                    sizeof(DAT_GameSynchronyState::instance
                            .DAT_PlayerMatchTimes[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
        }

    } // namespace Commands
} // namespace Synchrony
} // namespace OpenSHC
