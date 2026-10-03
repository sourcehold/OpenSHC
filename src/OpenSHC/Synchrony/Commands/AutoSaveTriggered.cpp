#include "../../Synchrony.func.hpp"
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
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00489880
    void Commands::AutoSaveTriggered()
    {
        WCHAR WVar1;
        int iVar2;
        WCHAR* pWVar3;
        undefined1 auStack_5c[3];
        char local_59;
        Base64State _base64State;
        WCHAR local_4c;
        undefined1 local_4a[70];
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)auStack_5c;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 0x4b;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 1,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::multiByteToWideCharWithSize,
                DAT_WideCharMultiByteState::ptr)(
                &local_4c, (LPCSTR)((int)(DAT_GameSynchronyState::instance.shortMapName)), (int)((int)(33)));
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&local_4c, (size_t)((int)(66)),
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            iVar2 = 1;
            do {
                if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar2] == -1)
                    || (iVar2 == DAT_GameSynchronyState::instance.currentPlayerSlotID)) {
                    DAT_GameSynchronyState::instance.announcementReceivedByPlayer[iVar2] = 1;
                } else {
                    DAT_GameSynchronyState::instance.announcementReceivedByPlayer[iVar2] = 0;
                }
                iVar2 = iVar2 + 1;
            } while (iVar2 < 9);
            ;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&local_59, 1, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = (int)local_59;
            if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&local_4c, 0x42, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL(OpenSHC::IO_Func::Base64EncodeInit)(&_base64State);
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_IntegerValue, DAT_LowLevelMemory::ptr)(
                    120, 0, (void*)((int)(DAT_GameSynchronyState::instance.shortMapName)));
                pWVar3 = &local_4c;
                do {
                    WVar1 = *pWVar3;
                    pWVar3 = pWVar3 + 1;
                } while (WVar1 != L'\0');
                MACRO_CALL(OpenSHC::IO_Func::Base64Encode)((char*)&local_4c,
                    (int)((int)((pWVar3 - (WCHAR*)local_4a >> 1) * 2)),
                    (char*)((int)(DAT_GameSynchronyState::instance.shortMapName)), &_base64State);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&local_4c, 0x42, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                    DAT_WideCharMultiByteState::ptr)(DAT_GameSynchronyState::instance.shortMapName, &local_4c, 1000);
            }
            DAT_GameSynchronyState::instance.savedMapTimeInTicks
                = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
            DAT_GameSynchronyState::instance.savedUnitsCRC32Hash
                = DAT_GameSynchronyState::instance.DAT_GameCommandParam1;
            MACRO_CALL(OpenSHC::UI::Helpers_Func::ShowProgressBarSaveLoadDialog)(
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2);
            DAT_GameSynchronyState::instance.field75_0xbe4 = timeGetTime();
            DAT_GameSynchronyState::instance.saveRelated = 1;
            if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                DAT_GameSynchronyState::instance.shouldSendAnnouncementUnk = 1;
                ;
            }
            DAT_GameSynchronyState::instance.announcementReceiveTime = timeGetTime();
            DAT_GameSynchronyState::instance.announcementReceivedBool = FALSE;
        };
    }

}
}
