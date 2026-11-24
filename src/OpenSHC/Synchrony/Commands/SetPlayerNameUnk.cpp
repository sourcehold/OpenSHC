// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../Commands.func.hpp"

#include "OpenSHC/IO.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/IO/Base64State.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // one face: 66 rows of 64 pixels of two bytes
    int const FACE_HEIGHT = 66;
    int const FACE_WIDTH = 64;
    int const FACE_SIZE = FACE_HEIGHT * FACE_WIDTH * 2;

    // FUNCTION: STRONGHOLDCRUSADER 0x00489AC0
    void Commands::SetPlayerNameUnk()
    {
        OpenSHC::IO::Base64State base64State;
        WCHAR wideName[36]; // the size of the original's buffer
        // the short map name (33 wide characters)
        DAT_GameSynchronyState::instance.DAT_CommandSize = 66;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::multiByteToWideCharWithSize,
                DAT_WideCharMultiByteState::ptr)(wideName, DAT_GameSynchronyState::instance.shortMapName, 33);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(wideName, 66, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        if (DAT_GameSynchronyState::instance.isHost) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(wideName, 66, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                DAT_WideCharMultiByteState::ptr)(DAT_GameSynchronyState::instance.shortMapName, wideName, 1000);
        } else {
            // a client keeps the name Base64 encoded
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(wideName, 66, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            MACRO_CALL(OpenSHC::IO_Func::Base64EncodeInit)(&base64State);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_IntegerValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_GameSynchronyState::instance.shortMapName), 0,
                DAT_GameSynchronyState::instance.shortMapName);
            MACRO_CALL(OpenSHC::IO_Func::Base64Encode)((char*)wideName, wcslen(wideName) * sizeof(WCHAR),
                DAT_GameSynchronyState::instance.shortMapName, &base64State);
        }
        // the players' IDs and names get a second copy
        for (int slot = 1; slot < countof(DAT_GameSynchronyState::instance.DAT_CurrentPlayerFullIDArray2); ++slot) {
            DAT_GameSynchronyState::instance.DAT_CurrentPlayerFullIDArray2[slot]
                = DAT_GameSynchronyState::instance.currentPlayerFullIDArray[slot];
            strcpy(DAT_GameSynchronyState::instance.playerNames2[slot],
                DAT_GameSynchronyState::instance.DAT_PlayerNames[slot]);
        }
        // and so do the eight players' faces (they follow the 20 lords' faces)
        MACRO_CALL(OpenSHC::OS_Func::_memcpy)(
            DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94 + 28 * FACE_HEIGHT * FACE_WIDTH,
            DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94 + 20 * FACE_HEIGHT * FACE_WIDTH, 8 * FACE_SIZE);
        DAT_GameSynchronyState::instance.DAT_SomePlayerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::clearChatEvents, DAT_GameSynchronyState::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::Synchrony::GameSynchronyState_Func::setSessionDescription, DAT_GameSynchronyState::ptr)();
        MACRO_CALL(OpenSHC::Synchrony_Func::ProgressBarRelated)();
        DAT_GameSynchronyState::instance.lobbyStateReceived = 0;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            OpenSHC::Commands::GCT_UNKNOWN_53);
    }

}
}
