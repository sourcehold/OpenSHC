#include "../../Synchrony.func.hpp"
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
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::IO::Base64State;
    using OpenSHC::IO::FileResourceType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Function: __alloca_probe replaced with injection: alloca_probe
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00489E30
    void Commands::SubmitMSVMapIndexAndProperties()
    {
        char cVar1;
        WCHAR WVar2;
        uint uVar3;
        char* pcVar4;
        char* pcVar5;
        WCHAR* pWVar6;
        BOOLEnum BVar7;
        int numberOfSymbols;
        undefined4 local_17a0;
        int local_179c;
        int local_1798;
        Base64State local_1794;
        char _msvFile[1001];
        WCHAR local_fb0[1001];
        uVar3 = MSVC_SecurityCookie::instance ^ (uint)&local_17a0;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 0x7dc;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            numberOfSymbols = 1000;
            pcVar4 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                    .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_GameCommandParam0 + -1]);
            MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::multiByteToWideCharWithSize,
                DAT_WideCharMultiByteState::ptr)(local_fb0, (LPCSTR)((int)(pcVar4)), numberOfSymbols);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(local_fb0, 2000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            pcVar5 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                    .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_GameCommandParam0 + -1]);
            pcVar4 = _msvFile;
            do {
                cVar1 = *pcVar5;
                *pcVar4 = cVar1;
                pcVar5 = pcVar5 + 1;
                pcVar4 = pcVar4 + 1;
            } while (cVar1 != '\0');
            pcVar4 = (char*)((int)&local_1794.lineCharacterCounter + 3);
            do {
                pcVar5 = pcVar4;
                pcVar4 = pcVar5 + 1;
            } while (pcVar5[1] != '\0');
            strcpy(pcVar5 + 1, ".msv");
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                OpenSHC::IO::FRT_UNKNOWN, (char const*)((int)(_msvFile)));
            MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeader, FilePackagerObj::ptr)(FALSE);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.savedMapTimeInTicks, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.savedUnitsCRC32Hash, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            ;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(local_fb0, 2000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            MACRO_CALL(OpenSHC::IO_Func::Base64EncodeInit)(&local_1794);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_IntegerValue, DAT_LowLevelMemory::ptr)(
                0x3f2, 0, (void*)((int)(_msvFile)));
            pWVar6 = local_fb0;
            do {
                WVar2 = *pWVar6;
                pWVar6 = pWVar6 + 1;
            } while (WVar2 != L'\0');
            MACRO_CALL(OpenSHC::IO_Func::Base64Encode)((char*)local_fb0,
                (int)((int)((pWVar6 - (local_fb0 + 1) >> 1) * 2)), (char*)((int)(_msvFile)), &local_1794);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&local_17a0, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&local_1798, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&local_179c, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                pcVar4 = (char*)((int)&local_1794.lineCharacterCounter + 3);
                do {
                    pcVar5 = pcVar4;
                    pcVar4 = pcVar5 + 1;
                } while (pcVar5[1] != '\0');
                strcpy(pcVar5 + 1, ".msv");
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    OpenSHC::IO::FRT_UNKNOWN, (char const*)((int)(_msvFile)));
                BVar7 = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::doesFileOfActiveResourceExist, DAT_ResourceManager::ptr)();
                if (BVar7 != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeader, FilePackagerObj::ptr)(
                        (OpenSHC::Commands::GameCommandType)FALSE);
                    if ((DAT_GameSynchronyState::instance.savedMapTimeInTicks == local_1798)
                        && (DAT_GameSynchronyState::instance.savedUnitsCRC32Hash == local_179c))
                        goto LAB_0048a0c8;
                }
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = local_17a0;
                MACRO_CALL_MEMBER(
                    OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (OpenSHC::Commands::GameCommandType)(OpenSHC::Commands::GCT_LOAD_MAP_HEADER
                        | OpenSHC::Commands::GCT_MULTIPLAYER_ANNOUNCE_HOST));
            }
        }
    LAB_0048a0c8:;
    }

}
}
