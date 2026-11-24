// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

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
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048B6C0
    void Commands::ShareMapHashForMapName()
    {
        int mapHash;
        char mapName[1008]; // the size of the original's buffer
        // the map's name (1000 characters) and the hash of the map file
        DAT_GameSynchronyState::instance.DAT_CommandSize = 1004;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                    DAT_ResourceManager::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0),
                1000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            strcpy(mapName,
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                    DAT_ResourceManager::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0));
            // ".map"
            strcat(mapName, S__MAP_005A2294);
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                OpenSHC::IO::FRT_MAPS, mapName);
            mapHash = MACRO_CALL_MEMBER(
                OpenSHC::IO::ResourceManager_Func::fileHashFunctionByteByByte, DAT_ResourceManager::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&mapHash, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            // every other player still has to answer; empty slots and this machine's own count as having the map
            for (int slot = 1; slot < countof(DAT_GameSynchronyState::instance.mapTransferStatePerPlayer); ++slot) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[slot] == -1
                    || slot == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    DAT_GameSynchronyState::instance.mapTransferStatePerPlayer[slot] = 2;
                } else {
                    DAT_GameSynchronyState::instance.mapTransferStatePerPlayer[slot] = 0;
                }
            }
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(mapName, 1000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&mapHash, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        if (DAT_GameSynchronyState::instance.isHost) {
            return;
        }
        strcpy(DAT_GameSynchronyState::instance.unknownMapName_01, mapName);
        // ".map"
        strcat(mapName, S__MAP_005A2294);
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
            OpenSHC::IO::FRT_MAPS, mapName);
        // a client whose own copy of the map hashes differently is asked to quit; one with the same map answers
        if (MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::fileHashFunctionByteByByte, DAT_ResourceManager::ptr)()
            != mapHash) {
            DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 2000;
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_QUIT_DIALOG);
            return;
        }
        // parameter 0 is the flag StartSendingMapFile reads: this machine has the map
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            OpenSHC::Commands::GCT_START_OR_STOP_SEND_MAP_FILEUnk);
    }

}
}
