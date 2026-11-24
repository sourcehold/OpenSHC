#include "../Commands.func.hpp"

#include "OpenSHC/IO.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/IO/Base64State.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00489880
    void Commands::AutoSaveTriggered()
    {
        WCHAR wideName[36]; // the size of the original's buffer
        // the save's time, the hash of its units, whether the game is being saved (one byte), and the short map name
        // (33 wide characters)
        DAT_GameSynchronyState::instance.DAT_CommandSize = 75;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0,
                sizeof(DAT_GameSynchronyState::instance.DAT_GameCommandParam0),
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1,
                sizeof(DAT_GameSynchronyState::instance.DAT_GameCommandParam1),
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 1,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::multiByteToWideCharWithSize,
                DAT_WideCharMultiByteState::ptr)(wideName, DAT_GameSynchronyState::instance.shortMapName, 33);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(wideName, 66, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            // every other player still has to answer; empty slots and this machine's own count as answered
            for (int slot = 1; slot < countof(DAT_GameSynchronyState::instance.announcementReceivedByPlayer); ++slot) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[slot] == -1
                    || slot == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    DAT_GameSynchronyState::instance.announcementReceivedByPlayer[slot] = 1;
                } else {
                    DAT_GameSynchronyState::instance.announcementReceivedByPlayer[slot] = 0;
                }
            }
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0,
            sizeof(DAT_GameSynchronyState::instance.DAT_GameCommandParam0),
            OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1,
            sizeof(DAT_GameSynchronyState::instance.DAT_GameCommandParam1),
            OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        char isSaving;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&isSaving, sizeof(isSaving),
            OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = isSaving;
        if (DAT_GameSynchronyState::instance.isHost) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(wideName, 66, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                DAT_WideCharMultiByteState::ptr)(DAT_GameSynchronyState::instance.shortMapName, wideName, 1000);
        } else {
            // a client keeps the name Base64 encoded
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(wideName, 66, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            OpenSHC::IO::Base64State base64State;
            MACRO_CALL(OpenSHC::IO_Func::Base64EncodeInit)(&base64State);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_IntegerValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_GameSynchronyState::instance.shortMapName), 0,
                DAT_GameSynchronyState::instance.shortMapName);
            MACRO_CALL(OpenSHC::IO_Func::Base64Encode)((char*)wideName, wcslen(wideName) * sizeof(WCHAR),
                DAT_GameSynchronyState::instance.shortMapName, &base64State);
        }
        DAT_GameSynchronyState::instance.savedMapTimeInTicks = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
        DAT_GameSynchronyState::instance.savedUnitsCRC32Hash = DAT_GameSynchronyState::instance.DAT_GameCommandParam1;
        MACRO_CALL(OpenSHC::UI::Helpers_Func::ShowProgressBarSaveLoadDialog)(
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2);
        DAT_GameSynchronyState::instance.lastAutoSaveTime = timeGetTime();
        DAT_GameSynchronyState::instance.saveRelated = 1;
        // a client announces its save; the host waits for the announcements
        if (!DAT_GameSynchronyState::instance.isHost) {
            DAT_GameSynchronyState::instance.shouldSendAnnouncementUnk = 1;
            return;
        }
        DAT_GameSynchronyState::instance.announcementReceiveTime = timeGetTime();
        DAT_GameSynchronyState::instance.announcementReceivedBool = FALSE;
    }

}
}
