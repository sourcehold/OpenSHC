#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00482C80
    void Commands::ShareDesyncedHashes()
    {
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 0;
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[0] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize = 10000;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[1] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize += 8000;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[2] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize += 8000;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[3] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize += 5000;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[4] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize += 36;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[5] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize += 80;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[6] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize += 15360;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[7] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize += 12000;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[8] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize += 640;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[9] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize += 800;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[10] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize += 160;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[12] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize += 36;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[13] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize += 320;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[11] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize += 160;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[0] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    DAT_GameSynchronyState::instance.HASH_Units + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_Units[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[1] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Buildings
                        + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_Buildings[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[2] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    DAT_GameSynchronyState::instance.HASH_Trees + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_Trees[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[3] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    DAT_GameSynchronyState::instance.HASH_Tribes + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_Tribes[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[4] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_PlayerDatas
                        + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_PlayerDatas[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[5] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Section1023
                        + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_Section1023[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[6] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_LogicalTileMap
                        + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_LogicalTileMap[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[7] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    DAT_GameSynchronyState::instance.HASH_Entities[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        + 25,
                    sizeof(DAT_GameSynchronyState::instance.HASH_Entities[0]) - 25 * sizeof(int),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[8] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    DAT_GameSynchronyState::instance.HASH_Moats + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_Moats[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[9] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_ClimbData
                        + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_ClimbData[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[10] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_PitchDitches
                        + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_PitchDitches[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[12] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    DAT_GameSynchronyState::instance.HASH_AIVS + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_AIVS[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[13] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_HeatMaps
                        + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_HeatMaps[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[11] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Unknown2
                        + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_Unknown2[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
        } else if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[0] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Units
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_Units[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[1] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Buildings
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_Buildings[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[2] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Trees
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_Trees[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[3] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Tribes
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_Tribes[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[4] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_PlayerDatas
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_PlayerDatas[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[5] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Section1023
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_Section1023[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[6] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_LogicalTileMap
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_LogicalTileMap[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[7] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    DAT_GameSynchronyState::instance
                            .HASH_Entities[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]
                        + 25,
                    sizeof(DAT_GameSynchronyState::instance.HASH_Entities[0]) - 25 * sizeof(int),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[8] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Moats
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_Moats[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[9] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_ClimbData
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_ClimbData[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[10] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_PitchDitches
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_PitchDitches[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[12] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_AIVS
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_AIVS[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[13] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_HeatMaps
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_HeatMaps[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[11] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Unknown2
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    sizeof(DAT_GameSynchronyState::instance.HASH_Unknown2[0]),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.isHost) {
                DAT_GameSynchronyState::instance
                    .receivedSyncStatusByPlayerUnk[DAT_GameSynchronyState::instance.protocolInvokerPlayerID] = 1;
                DAT_GameSynchronyState::instance.announcementReceivedBool = TRUE;
                DAT_GameSynchronyState::instance.announcementReceiveTime = timeGetTime();
            }
            DAT_GameSynchronyState::instance.currentPacketTotalSize = 0;
            DAT_GameSynchronyState::instance.resyncTransferTotalSize = 0;
            return;
        }
    }

}
}
