#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::IO::FileResourceType;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x0048B6C0
    void Commands::ShareMapHashForMapName()
    {
        char cVar1;
        char* pcVar2;
        char* pcVar3;
        int iVar4;
        int _mapHash_2;
        size_t size;
        GameCommandParameterLocation srcSwitch;
        GameCommandParameterReadWrite destSwitch;
        undefined4 _mapHash;
        char mapName[1008];
        DAT_GameSynchronyState::instance.DAT_CommandSize = 0x3ec;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            destSwitch = OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1;
            srcSwitch = OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS;
            size = 1000;
            pcVar2 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                DAT_ResourceManager::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(pcVar2, size, srcSwitch, destSwitch);
            pcVar3 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                DAT_ResourceManager::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
            pcVar2 = mapName;
            do {
                cVar1 = *pcVar3;
                *pcVar2 = cVar1;
                pcVar3 = pcVar3 + 1;
                pcVar2 = pcVar2 + 1;
            } while (cVar1 != '\0');
            pcVar2 = mapName + -1;
            do {
                pcVar3 = pcVar2;
                pcVar2 = pcVar3 + 1;
            } while (pcVar3[1] != '\0');
            strcpy(pcVar3 + 1, ".map");
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                OpenSHC::IO::FRT_MAPS, mapName);
            _mapHash = MACRO_CALL_MEMBER(
                OpenSHC::IO::ResourceManager_Func::fileHashFunctionByteByByte, DAT_ResourceManager::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&_mapHash, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            iVar4 = 1;
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            do {
                if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar4] == -1)
                    || (iVar4 == DAT_GameSynchronyState::instance.currentPlayerSlotID)) {
                    DAT_GameSynchronyState::instance.field282_0x109d98[iVar4] = 2;
                } else {
                    DAT_GameSynchronyState::instance.field282_0x109d98[iVar4] = 0;
                }
                iVar4 = iVar4 + 1;
            } while (iVar4 < 9);
            ;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(mapName, 1000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&_mapHash, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                iVar4 = 0;
                do {
                    cVar1 = mapName[iVar4];
                    DAT_GameSynchronyState::instance.unknownMapName_01[iVar4] = cVar1;
                    iVar4 = iVar4 + 1;
                } while (cVar1 != '\0');
                pcVar2 = mapName + -1;
                do {
                    pcVar3 = pcVar2;
                    pcVar2 = pcVar3 + 1;
                } while (pcVar3[1] != '\0');
                /*
                  .map in reverse
                 */
                strcpy(pcVar3 + 1, ".map");
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    OpenSHC::IO::FRT_MAPS, mapName);
                _mapHash_2 = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::fileHashFunctionByteByByte, DAT_ResourceManager::ptr)();
                if (_mapHash_2 != _mapHash) {
                    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 2000;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                        DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_QUIT_DIALOG);
                    ;
                }
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_START_OR_STOP_SEND_MAP_FILEUnk);
            }
        };
    }

}
}
