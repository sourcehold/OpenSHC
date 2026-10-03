#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

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
      WARNING: Enum "MappersEnumShort": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00480710
    void Commands::AnnouncePlayerInformationSuchAsNameLordTypeAndAvailableAIVS()
    {
        char cVar1;
        char* pcVar2;
        char (*pacVar3)[250];
        char (*pacVar4)[90];
        bool bVar5;
        int iVar6;
        int _receivedCurrentPlayerSlotID;
        int local_3f4;
        int local_3f0;
        WCHAR local_3ec[500];
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)&_receivedCurrentPlayerSlotID;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 0x250;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.currentPlayerSlotID, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameCore::instance.lordIconUnk, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameCore::instance.selectedLordTypeUnk, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            iVar6 = 0xfa;
            /*
              get player name?
             */
            pcVar2 = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
            MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::multiByteToWideCharWithSize,
                DAT_WideCharMultiByteState::ptr)(local_3ec, (LPCSTR)((int)(pcVar2)), iVar6);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(local_3ec, 500, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(DAT_AIVState::instance.aivFileAvailabilityPerAIArray, 0x50,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            ;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&_receivedCurrentPlayerSlotID, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&local_3f4, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&local_3f0, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            if (_receivedCurrentPlayerSlotID != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(local_3ec, 500, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                    DAT_WideCharMultiByteState::ptr)(
                    DAT_GameSynchronyState::instance.DAT_PlayerNames[_receivedCurrentPlayerSlotID],
                    (LPWSTR)((int)(local_3ec)), 0xfa);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    DAT_GameSynchronyState::instance.DAT_ReceivedAIVFileAvailabilityPerAIArray
                        + _receivedCurrentPlayerSlotID,
                    0x50, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                pacVar3 = DAT_GameSynchronyState::instance.DAT_PlayerNames + _receivedCurrentPlayerSlotID;
                iVar6 = (int)DAT_GameSynchronyState::instance.finalResults.names[_receivedCurrentPlayerSlotID]
                    - (int)pacVar3;
                do {
                    cVar1 = (*pacVar3)[0];
                    *(char*)((int)pacVar3 + iVar6) = cVar1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                DAT_GameSynchronyState::instance.isIncludedPlayer[_receivedCurrentPlayerSlotID] = TRUE;
                pcVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
                pacVar3 = DAT_GameSynchronyState::instance.DAT_PlayerNames
                    + DAT_GameSynchronyState::instance.currentPlayerSlotID;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                pacVar3 = DAT_GameSynchronyState::instance.DAT_PlayerNames
                    + DAT_GameSynchronyState::instance.currentPlayerSlotID;
                pacVar4 = DAT_GameSynchronyState::instance.finalResults.names
                    + DAT_GameSynchronyState::instance.currentPlayerSlotID;
                do {
                    cVar1 = (*pacVar3)[0];
                    (*pacVar4)[0] = cVar1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                    pacVar4 = (char (*)[90])(*pacVar4 + 1);
                } while (cVar1 != '\0');
                bVar5 = DAT_GameSynchronyState::instance.isHost != FALSE;
                DAT_GameCore::instance.lordIcons[_receivedCurrentPlayerSlotID] = local_3f4;
                DAT_GameCore::instance.selectedLordTypes[_receivedCurrentPlayerSlotID] = local_3f0;
                if (bVar5) {
                    MACRO_CALL_MEMBER(OpenSHC::AI::AIVState_Func::hostChecksLobbyAIVAvailability, DAT_AIVState::ptr)();
                }
            }
        };
    }

}
}
