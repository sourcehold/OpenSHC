// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00485380
    void Commands::SomePlayerNameUpdateCommand()
    {
        WCHAR wideName[MAX_PATH];
        // the sender's name (250 wide characters)
        DAT_GameSynchronyState::instance.DAT_CommandSize = 500;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::multiByteToWideCharWithSize,
                DAT_WideCharMultiByteState::ptr)(wideName,
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                    DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_ZERO),
                250);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(wideName, 500, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(wideName, 500, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        MACRO_CALL_MEMBER(
            OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize, DAT_WideCharMultiByteState::ptr)(
            DAT_GameSynchronyState::instance.DAT_PlayerNames[DAT_GameSynchronyState::instance.protocolInvokerPlayerID],
            wideName, 250);
        strcpy(DAT_GameSynchronyState::instance.finalResults
                   .names[DAT_GameSynchronyState::instance.protocolInvokerPlayerID],
            DAT_GameSynchronyState::instance.DAT_PlayerNames[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]);
        // the chat lines that name the player get the new name
        for (int line = 0; line < countof(DAT_GameSynchronyState::instance.DAT_ChatEventArray); ++line) {
            // compared with TRUE: the original tests the flag == 1
            if (DAT_GameSynchronyState::instance.DAT_ChatEventArray[line].flag != TRUE) {
                continue;
            }
            if (DAT_GameSynchronyState::instance.DAT_ChatEventArray[line].subjectPlayer
                == DAT_GameSynchronyState::instance.protocolInvokerPlayerID) {
                strcpy(DAT_GameSynchronyState::instance.DAT_ChatMessageSubjectPlayerNameArray[line],
                    DAT_GameSynchronyState::instance
                        .DAT_PlayerNames[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]);
            }
            if (DAT_GameSynchronyState::instance.DAT_ChatEventArray[line].objectPlayer
                == DAT_GameSynchronyState::instance.protocolInvokerPlayerID) {
                strcpy(DAT_GameSynchronyState::instance.DAT_ChatMessageObjectPlayerNameArray[line],
                    DAT_GameSynchronyState::instance
                        .DAT_PlayerNames[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]);
            }
        }
    }

}
}
