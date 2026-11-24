#include "../Commands.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048B8F0
    void Commands::ShareMapPart()
    {
        int byteCount;
        char part[1024];
        // a part of the map file (1024 bytes), its length, and whether the receiver has to answer it
        DAT_GameSynchronyState::instance.DAT_CommandSize = 1029;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        bool answerExpected = false;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            if (DAT_GameSynchronyState::instance
                    .mapSendingFileHandles[DAT_GameSynchronyState::instance.DAT_GameCommandParam1]
                == NULL) {
                return;
            }
            // part -1 ends the transfer: an empty part with the length -1
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == -1) {
                MACRO_CALL(OpenSHC::OS_Func::_memset)(part, 0, sizeof(part));
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(part, sizeof(part), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                // cleared again, as in the original (without this line the match is lost)
                answerExpected = false;
                byteCount = -1;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&byteCount, sizeof(byteCount),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&answerExpected, sizeof(answerExpected),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                return;
            }
            byteCount = MACRO_CALL(OpenSHC::OS_Func::_fread)(part, 1, sizeof(part),
                DAT_GameSynchronyState::instance
                    .mapSendingFileHandles[DAT_GameSynchronyState::instance.DAT_GameCommandParam1]);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(part, sizeof(part), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&byteCount, sizeof(byteCount),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            DAT_GameSynchronyState::instance
                .mapSendingByteBufferAddress[DAT_GameSynchronyState::instance.DAT_GameCommandParam1] += byteCount;
            DAT_GameSynchronyState::instance.DAT_PlayerIDReceiver
                = DAT_GameSynchronyState::instance
                      .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam1];
            // the receiver answers the last part and every tenth part, and the sender waits for that answer
            if (DAT_GameSynchronyState::instance
                    .mapSendingByteBufferAddress[DAT_GameSynchronyState::instance.DAT_GameCommandParam1]
                >= DAT_GameSynchronyState::instance.mapSendingFileSize) {
                answerExpected = true;
                MACRO_CALL(OpenSHC::OS_Func::_fclose)(DAT_GameSynchronyState::instance
                        .mapSendingFileHandles[DAT_GameSynchronyState::instance.DAT_GameCommandParam1]);
                DAT_GameSynchronyState::instance
                    .mapSendingFileHandles[DAT_GameSynchronyState::instance.DAT_GameCommandParam1] = NULL;
            } else if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 % 10 == 9) {
                answerExpected = true;
            }
            if (answerExpected
                && DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam1]
                    != -1
                && DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                DAT_GameSynchronyState::instance
                    .mapSendRequestStatePerPlayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1] = 1;
            }
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&answerExpected, sizeof(answerExpected),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(part, sizeof(part), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&byteCount, sizeof(byteCount),
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        bool receivedAnswerExpected;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&receivedAnswerExpected, sizeof(receivedAnswerExpected),
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        answerExpected = receivedAnswerExpected;
        if (DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile != NULL) {
            if (byteCount >= 0) {
                MACRO_CALL(OpenSHC::OS_Func::_fwrite)(
                    part, 1, byteCount, DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile);
                DAT_GameSynchronyState::instance.mapSendingByteBufferAddress[0] += byteCount;
            }
            // the file is complete, or the sender ended the transfer: the maps are read again
            if (DAT_GameSynchronyState::instance.mapSendingByteBufferAddress[0]
                    >= DAT_GameSynchronyState::instance.mapSendingFileSize
                || byteCount == -1) {
                MACRO_CALL(OpenSHC::OS_Func::_fclose)(DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile);
                DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile = NULL;
                DAT_GameSynchronyState::instance.DAT_MapFileReceivingState = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::loadMapHeaders, DAT_ResourceManager::ptr)(FALSE);
                DAT_GameSynchronyState::instance.reparseMaps = TRUE;
            }
        }
        if (answerExpected) {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_UNKNOWN_107);
        }
    }

}
}
