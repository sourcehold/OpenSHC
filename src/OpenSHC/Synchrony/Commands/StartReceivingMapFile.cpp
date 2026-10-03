#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
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
      CommandMapSendingRelated1      param 0: index   param 1: addressee   param 2: size   decompilerscript: committed:
      2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00485CC0
    void Commands::StartReceivingMapFile()
    {
        char cVar1;
        char* _mapname;
        char* pcVar2;
        size_t size;
        GameCommandParameterLocation srcSwitch;
        GameCommandParameterReadWrite destSwitch;
        char mapName[1000];
        DAT_GameSynchronyState::instance.DAT_CommandSize = 1004;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            destSwitch = OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1;
            srcSwitch = OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS;
            size = 1000;
            _mapname = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                DAT_ResourceManager::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(_mapname, size, srcSwitch, destSwitch);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.mapSendingFileSize, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            _mapname = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                DAT_ResourceManager::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
            pcVar2 = mapName;
            do {
                cVar1 = *_mapname;
                *pcVar2 = cVar1;
                _mapname = _mapname + 1;
                pcVar2 = pcVar2 + 1;
            } while (cVar1 != '\0');
            _mapname = (mapName - 1);
            do {
                pcVar2 = _mapname;
                _mapname = pcVar2 + 1;
            } while (pcVar2[1] != '\0');
            strcpy(pcVar2 + 1, ".map");
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                OpenSHC::IO::FRT_MAPS, mapName);
            DAT_GameSynchronyState::instance.DAT_PlayerIDReceiver
                = DAT_GameSynchronyState::instance
                      .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam1];
            ;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(mapName, 1000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.mapSendingFileSize, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                _mapname = (mapName - 1);
                do {
                    pcVar2 = _mapname;
                    _mapname = pcVar2 + 1;
                } while (pcVar2[1] != '\0');
                strcpy(pcVar2 + 1, ".map");
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    OpenSHC::IO::FRT_MAPS, mapName);
                _mapname = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)();
                DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile
                    = MACRO_CALL(OpenSHC::OS_Func::_fopen)(_mapname, "wb");
                DAT_GameSynchronyState::instance.DAT_MapFileReceivingState = 2;
                DAT_GameSynchronyState::instance.mapSendingByteBufferAddress[0] = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_RECEIVE_MAP_FROM, FALSE);
            }
        };
    }

}
}
