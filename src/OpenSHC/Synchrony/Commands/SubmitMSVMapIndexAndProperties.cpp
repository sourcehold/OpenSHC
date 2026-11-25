// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../Commands.func.hpp"

#include "OpenSHC/IO.func.hpp"
#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/IO/Base64State.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00489E30
    void Commands::SubmitMSVMapIndexAndProperties()
    {
        char saveName[2008]; // the size of the original's buffer
        WCHAR wideName[2006]; // the size of the original's buffer
        // the map's name (1000 wide characters), its index, and the time and the units' hash of its save
        DAT_GameSynchronyState::instance.DAT_CommandSize = 2012;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::multiByteToWideCharWithSize,
                DAT_WideCharMultiByteState::ptr)(wideName,
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                    DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                        .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]),
                1000);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(wideName, 2000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0,
                sizeof(DAT_GameSynchronyState::instance.DAT_GameCommandParam0),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            // the save of the map: its name with ".msv"
            strcpy(saveName,
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                    DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                        .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]));
            // ".msv"
            strcat(saveName, S__MSV_005A7498);
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                OpenSHC::IO::FRT_UNKNOWN, saveName);
            MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeader, FilePackagerObj::ptr)(FALSE);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.savedMapTimeInTicks,
                sizeof(DAT_GameSynchronyState::instance.savedMapTimeInTicks),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.savedUnitsCRC32Hash,
                sizeof(DAT_GameSynchronyState::instance.savedUnitsCRC32Hash),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(wideName, 2000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        // the save's name on this machine: the received name, Base64 encoded, with ".msv"
        OpenSHC::IO::Base64State base64State;
        MACRO_CALL(OpenSHC::IO_Func::Base64EncodeInit)(&base64State);
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_IntegerValue, DAT_LowLevelMemory::ptr)(
            1010, 0, saveName);
        MACRO_CALL(OpenSHC::IO_Func::Base64Encode)(
            (char*)wideName, wcslen(wideName) * sizeof(WCHAR), saveName, &base64State);
        int mapIndex;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&mapIndex, sizeof(mapIndex),
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        int mapTime;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&mapTime, sizeof(mapTime), OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        int unitsHash;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&unitsHash, sizeof(unitsHash),
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        if (DAT_GameSynchronyState::instance.isHost) {
            return;
        }
        // ".msv"
        strcat(saveName, S__MSV_005A7498);
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
            OpenSHC::IO::FRT_UNKNOWN, saveName);
        // a client without the save, or with a save of another time or with other units, answers with the map's
        // index; the answer is written in both places (written once, it loses the match)
        if (!MACRO_CALL_MEMBER(
                OpenSHC::IO::ResourceManager_Func::doesFileOfActiveResourceExist, DAT_ResourceManager::ptr)()) {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = mapIndex;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_UNKNOWN_51);
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeader, FilePackagerObj::ptr)(FALSE);
        if (DAT_GameSynchronyState::instance.savedMapTimeInTicks != mapTime
            || DAT_GameSynchronyState::instance.savedUnitsCRC32Hash != unitsHash) {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = mapIndex;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_UNKNOWN_51);
        }
    }

}
}
