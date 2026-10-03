#include "../../Synchrony.func.hpp"
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
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::IO::Base64State;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00489AC0
    void Commands::SetPlayerNameUnk()
    {
        WCHAR WVar1;
        char* pcVar2;
        WCHAR* pWVar3;
        char (*pacVar4)[250];
        int* piVar5;
        char (*pacVar6)[250];
        Base64State local_58;
        WCHAR local_4c;
        undefined1 local_4a[70];
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_58;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 66;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::multiByteToWideCharWithSize,
                DAT_WideCharMultiByteState::ptr)(
                &local_4c, (LPCSTR)((int)(DAT_GameSynchronyState::instance.shortMapName)), (int)((int)(33)));
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&local_4c, (size_t)((int)(66)),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            ;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&local_4c, 0x42, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL(OpenSHC::IO_Func::Base64EncodeInit)(&local_58);
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_IntegerValue, DAT_LowLevelMemory::ptr)(
                    120, 0, (void*)((int)(DAT_GameSynchronyState::instance.shortMapName)));
                pWVar3 = &local_4c;
                do {
                    WVar1 = *pWVar3;
                    pWVar3 = pWVar3 + 1;
                } while (WVar1 != L'\0');
                MACRO_CALL(OpenSHC::IO_Func::Base64Encode)((char*)&local_4c,
                    (int)((int)((pWVar3 - (WCHAR*)local_4a >> 1) * 2)),
                    (char*)((int)(DAT_GameSynchronyState::instance.shortMapName)), &local_58);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&local_4c, (size_t)((int)(66)),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                    DAT_WideCharMultiByteState::ptr)(DAT_GameSynchronyState::instance.shortMapName, &local_4c, 1000);
            }
            pacVar6 = DAT_GameSynchronyState::instance.DAT_PlayerNames;
            piVar5 = DAT_GameSynchronyState::instance.DAT_CurrentPlayerFullIDArray2 + 1;
            do {
                pacVar6 = pacVar6 + 1;
                *piVar5 = piVar5[-9];
                pacVar4 = pacVar6;
                do {
                    pcVar2 = *pacVar4;
                    pacVar4[9][0] = *pcVar2;
                    pacVar4 = (char (*)[250])(*pacVar4 + 1);
                } while (*pcVar2 != '\0');
                piVar5 = piVar5 + 1;
            } while (piVar5 < DAT_GameSynchronyState::instance.DAT_CurrentPlayerFullIDArray2 + 9);
            MACRO_CALL(OpenSHC::OS_Func::_memcpy)(
                (void*)((int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94 + 0x39c00),
                (void*)((int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94 + 0x29400), 0x10800);
            DAT_GameSynchronyState::instance.DAT_SomePlayerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            MACRO_CALL_MEMBER(
                OpenSHC::Synchrony::GameSynchronyState_Func::clearChatEvents, DAT_GameSynchronyState::ptr)();
            MACRO_CALL_MEMBER(
                OpenSHC::Synchrony::GameSynchronyState_Func::setSessionDescription, DAT_GameSynchronyState::ptr)();
            MACRO_CALL(OpenSHC::Synchrony_Func::ProgressBarRelated)();
            DAT_GameSynchronyState::instance.field215_0x106e1c = 0;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                ((GameCommandType)0x35));
        };
    }

}
}
