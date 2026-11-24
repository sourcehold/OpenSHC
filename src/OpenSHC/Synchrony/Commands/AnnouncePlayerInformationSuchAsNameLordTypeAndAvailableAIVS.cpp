// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../Commands.func.hpp"

#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00480710
    void Commands::AnnouncePlayerInformationSuchAsNameLordTypeAndAvailableAIVS()
    {
        WCHAR wideName[500]; // the size of the original's buffer
        // the sender's slot, lord icon and lord type, the name (250 wide characters) and which AIV files it has
        DAT_GameSynchronyState::instance.DAT_CommandSize = 592;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.currentPlayerSlotID,
                sizeof(DAT_GameSynchronyState::instance.currentPlayerSlotID),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameCore::instance.lordIconUnk,
                sizeof(DAT_GameCore::instance.lordIconUnk), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameCore::instance.selectedLordTypeUnk,
                sizeof(DAT_GameCore::instance.selectedLordTypeUnk), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::multiByteToWideCharWithSize,
                DAT_WideCharMultiByteState::ptr)(wideName,
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                    DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_ZERO),
                250);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(wideName, 500, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(DAT_AIVState::instance.aivFileAvailabilityPerAIArray,
                sizeof(DAT_AIVState::instance.aivFileAvailabilityPerAIArray),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        int senderSlot;
        int lordIcon;
        int lordType;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&senderSlot, sizeof(senderSlot),
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&lordIcon, sizeof(lordIcon),
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&lordType, sizeof(lordType),
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        if (senderSlot == 0) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(wideName, 500, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        MACRO_CALL_MEMBER(
            OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize, DAT_WideCharMultiByteState::ptr)(
            DAT_GameSynchronyState::instance.DAT_PlayerNames[senderSlot], wideName, 250);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(
            DAT_GameSynchronyState::instance.DAT_ReceivedAIVFileAvailabilityPerAIArray[senderSlot],
            sizeof(DAT_GameSynchronyState::instance.DAT_ReceivedAIVFileAvailabilityPerAIArray[senderSlot]),
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        strcpy(DAT_GameSynchronyState::instance.finalResults.names[senderSlot],
            DAT_GameSynchronyState::instance.DAT_PlayerNames[senderSlot]);
        DAT_GameSynchronyState::instance.isIncludedPlayer[senderSlot] = TRUE;
        // this machine's own name is refreshed too
        strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[DAT_GameSynchronyState::instance.currentPlayerSlotID],
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(
                OpenSHC::Text::TAIT_ZERO));
        strcpy(
            DAT_GameSynchronyState::instance.finalResults.names[DAT_GameSynchronyState::instance.currentPlayerSlotID],
            DAT_GameSynchronyState::instance.DAT_PlayerNames[DAT_GameSynchronyState::instance.currentPlayerSlotID]);
        DAT_GameCore::instance.lordIcons[senderSlot] = lordIcon;
        DAT_GameCore::instance.selectedLordTypes[senderSlot] = lordType;
        if (DAT_GameSynchronyState::instance.isHost) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AIVState_Func::hostChecksLobbyAIVAvailability, DAT_AIVState::ptr)();
        }
    }

}
}
