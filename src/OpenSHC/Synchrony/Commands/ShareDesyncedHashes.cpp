#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
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
            DAT_GameSynchronyState::instance.DAT_CommandSize = DAT_GameSynchronyState::instance.DAT_CommandSize + 8000;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[2] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize = DAT_GameSynchronyState::instance.DAT_CommandSize + 8000;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[3] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize = DAT_GameSynchronyState::instance.DAT_CommandSize + 5000;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[4] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize = DAT_GameSynchronyState::instance.DAT_CommandSize + 36;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[5] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize = DAT_GameSynchronyState::instance.DAT_CommandSize + 80;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[6] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize = DAT_GameSynchronyState::instance.DAT_CommandSize + 15360;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[7] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize = DAT_GameSynchronyState::instance.DAT_CommandSize + 12000;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[8] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize = DAT_GameSynchronyState::instance.DAT_CommandSize + 640;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[9] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize = DAT_GameSynchronyState::instance.DAT_CommandSize + 800;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[10] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize = DAT_GameSynchronyState::instance.DAT_CommandSize + 160;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[0xc] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize = DAT_GameSynchronyState::instance.DAT_CommandSize + 36;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[0xd] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize = DAT_GameSynchronyState::instance.DAT_CommandSize + 320;
        }
        if (DAT_GameSynchronyState::instance.sharedDesyncFlags[0xb] != 0) {
            DAT_GameSynchronyState::instance.DAT_CommandSize = DAT_GameSynchronyState::instance.DAT_CommandSize + 160;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[0] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    DAT_GameSynchronyState::instance.HASH_Units + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    (size_t)((int)(10000)), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[1] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Buildings
                        + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    8000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[2] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    DAT_GameSynchronyState::instance.HASH_Trees + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    8000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[3] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    DAT_GameSynchronyState::instance.HASH_Tribes + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    5000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[4] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_PlayerDatas
                        + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    (size_t)((int)(36)), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[5] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Section1023
                        + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    (size_t)((int)(80)), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[6] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_LogicalTileMap
                        + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    (size_t)((int)(15360)), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[7] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    DAT_GameSynchronyState::instance.HASH_Entities[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        + 0x19,
                    (size_t)((int)(11900)), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[8] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    DAT_GameSynchronyState::instance.HASH_Moats + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    (size_t)((int)(640)), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[9] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_ClimbData
                        + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    800, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[10] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_PitchDitches
                        + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    (size_t)((int)(160)), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[0xc] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    DAT_GameSynchronyState::instance.HASH_AIVS + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    (size_t)((int)(36)), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[0xd] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_HeatMaps
                        + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    (size_t)((int)(320)), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[0xb] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Unknown2
                        + DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    (size_t)((int)(160)), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
        } else if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[0] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Units
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    10000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[1] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Buildings
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    8000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[2] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Trees
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    8000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[3] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Tribes
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    5000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[4] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_PlayerDatas
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    0x24, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[5] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Section1023
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    0x50, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[6] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_LogicalTileMap
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    (size_t)((int)(15360)), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[7] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    DAT_GameSynchronyState::instance
                            .HASH_Entities[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]
                        + 0x19,
                    0x2e7c, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[8] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Moats
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    0x280, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[9] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_ClimbData
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    800, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[10] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_PitchDitches
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    0xa0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[0xc] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_AIVS
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    0x24, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[0xd] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_HeatMaps
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    0x140, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.sharedDesyncFlags[0xb] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.HASH_Unknown2
                        + DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
                    0xa0, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            }
            if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                DAT_GameSynchronyState::instance
                    .receivedSyncStatusByPlayerUnk[DAT_GameSynchronyState::instance.protocolInvokerPlayerID] = 1;
                DAT_GameSynchronyState::instance.announcementReceivedBool = TRUE;
                DAT_GameSynchronyState::instance.announcementReceiveTime = timeGetTime();
            }
            DAT_GameSynchronyState::instance.currentPacketTotalSize = 0;
            DAT_GameSynchronyState::instance.field73_0xbdc = 0;
            return;
        }
    }

}
}
