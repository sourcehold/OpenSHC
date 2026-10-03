#include "../../Synchrony.func.hpp"
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
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::UI::Enums::MenuModalType;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x0048B8F0
    void Commands::ShareMapPart()
    {
        undefined1 auStack_40c[2];
        char local_40a;
        char local_409;
        size_t _buffer2;
        undefined1 _buffer[1024];
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)auStack_40c;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 1029;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        local_40a = '\0';
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(_buffer, (size_t)((int)(1024)),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&_buffer2, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&local_409, 1, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                local_40a = local_409;
                if (DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile != (FILE*)0x0) {
                    if (-1 < (int)_buffer2) {
                        MACRO_CALL(OpenSHC::OS_Func::_fwrite)(
                            _buffer, 1, _buffer2, DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile);
                        DAT_GameSynchronyState::instance.mapSendingByteBufferAddress[0]
                            = DAT_GameSynchronyState::instance.mapSendingByteBufferAddress[0] + _buffer2;
                    }
                    if ((DAT_GameSynchronyState::instance.mapSendingFileSize
                            <= DAT_GameSynchronyState::instance.mapSendingByteBufferAddress[0])
                        || (_buffer2 == 0xffffffff)) {
                        MACRO_CALL(OpenSHC::OS_Func::_fclose)(DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile);
                        DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile = (FILE*)0x0;
                        DAT_GameSynchronyState::instance.DAT_MapFileReceivingState = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::loadMapHeaders, DAT_ResourceManager::ptr)(
                            FALSE);
                        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                    }
                }
                if (local_40a != '\0') {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (OpenSHC::Commands::GameCommandType)(OpenSHC::Commands::GCT_START_OR_STOP_SEND_MAP_FILEUnk
                            | OpenSHC::Commands::GCT_MULTIPLAYER_ANNOUNCE_HOST));
                }
            }
        LAB_0048bbc1:;
            return;
        }
        if (DAT_GameSynchronyState::instance
                .mapSendingFileHandles[DAT_GameSynchronyState::instance.DAT_GameCommandParam1]
            == (FILE*)0x0)
            goto LAB_0048bbc1;
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == -1) {
            MACRO_CALL(OpenSHC::OS_Func::_memset)(_buffer, 0, (size_t)((int)(1024)));
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(_buffer, (size_t)((int)(1024)),
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            local_40a = '\0';
            _buffer2 = 0xffffffff;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&_buffer2, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&local_40a, 1, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            ;
        }
        _buffer2 = MACRO_CALL(OpenSHC::OS_Func::_fread)(_buffer, 1, (size_t)((int)(1024)),
            (FILE*)((int)(DAT_GameSynchronyState::instance
                    .mapSendingFileHandles[DAT_GameSynchronyState::instance.DAT_GameCommandParam1])));
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(_buffer, (size_t)((int)(1024)),
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
        /*
          TODO: by is the address of the buffer shared?
         */
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&_buffer2, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
        DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
        DAT_GameSynchronyState::instance
            .mapSendingByteBufferAddress[DAT_GameSynchronyState::instance.DAT_GameCommandParam1]
            = DAT_GameSynchronyState::instance
                  .mapSendingByteBufferAddress[DAT_GameSynchronyState::instance.DAT_GameCommandParam1]
            + _buffer2;
        DAT_GameSynchronyState::instance.DAT_PlayerIDReceiver
            = DAT_GameSynchronyState::instance
                  .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam1];
        if (DAT_GameSynchronyState::instance
                .mapSendingByteBufferAddress[DAT_GameSynchronyState::instance.DAT_GameCommandParam1]
            < DAT_GameSynchronyState::instance.mapSendingFileSize) {
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 % 10 != 9)
                goto LAB_0048ba65;
            local_40a = '\x01';
        } else {
            local_40a = '\x01';
            MACRO_CALL(OpenSHC::OS_Func::_fclose)(DAT_GameSynchronyState::instance
                    .mapSendingFileHandles[DAT_GameSynchronyState::instance.DAT_GameCommandParam1]);
            DAT_GameSynchronyState::instance
                .mapSendingFileHandles[DAT_GameSynchronyState::instance.DAT_GameCommandParam1] = (FILE*)0x0;
        LAB_0048ba65:
            if (local_40a == '\0')
                goto LAB_0048ba88;
        }
        if ((DAT_GameSynchronyState::instance
                    .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam1]
                != -1)
            && (DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                != DAT_GameSynchronyState::instance.currentPlayerSlotID)) {
            DAT_GameSynchronyState::instance.field290_0x109e20[DAT_GameSynchronyState::instance.DAT_GameCommandParam1]
                = 1;
        }
    LAB_0048ba88:
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&local_40a, 1, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
        ;
    }

}
}
