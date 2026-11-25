// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../SendReceiveMap.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B10D0
        void SendReceiveMap::MenuItemActionHandler_SendReceiveMap_Main(int action, ...)
        {
            if (action != 3) {
                if (action != 68 || DAT_GameSynchronyState::instance.DAT_MapFileReceivingState != 0) {
                    return;
                }
                DAT_GameSynchronyState::instance.DAT_MapFileReceivingState = 1;
                // The original copies the name and appends the extension inline, so the macro is used here.
                char fileName[1008]; // the size of the original's buffer
                strcpy(fileName,
                    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                        DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                            .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected]));
                // ".map"
                strcat(fileName, S__MAP_005A2294);
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    OpenSHC::IO::FRT_MAPS, fileName);
                DAT_GameSynchronyState::instance.mapSendingFileSize = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::getCurrentResourceSize, DAT_ResourceManager::ptr)();
                DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile = NULL;
                // Open the map file once for each player waiting for it (transfer state 1).
                for (int player = 1; player < 9; ++player) {
                    DAT_GameSynchronyState::instance.mapSendRequestStatePerPlayer[player] = 0;
                    DAT_GameSynchronyState::instance.mapSendingByteBufferAddress[player] = 0;
                    DAT_GameSynchronyState::instance.mapTransferTicksPerPlayer[player] = 0;
                    if (DAT_GameSynchronyState::instance.mapTransferStatePerPlayer[player] == 1) {
                        char* const resourceFileName
                            = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::getFileNameOfCurrentActiveResource,
                                DAT_ResourceManager::ptr)();
                        // "rb"
                        DAT_GameSynchronyState::instance.mapSendingFileHandles[player]
                            = MACRO_CALL(OpenSHC::OS_Func::_fopen)(resourceFileName, S_RB_005A4E18);
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                            = DAT_MenuTextInputState::instance
                                  .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                      + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected];
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                            = DAT_GameSynchronyState::instance.mapSendingFileSize;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = player;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_RECEIVE_SENT_MAPPARTUnk);
                    }
                }
                return;
            }
            if (DAT_GameSynchronyState::instance.DAT_MapFileReceivingState == 1) {
                for (int player = 1; player < 9; ++player) {
                    FILE* const file = DAT_GameSynchronyState::instance.mapSendingFileHandles[player];
                    if (file != NULL) {
                        MACRO_CALL(OpenSHC::OS_Func::_fclose)(file);
                        DAT_GameSynchronyState::instance.mapSendingFileHandles[player] = NULL;
                    }
                }
                DAT_GameSynchronyState::instance.DAT_MapFileReceivingState = 0;
            } else if (DAT_GameSynchronyState::instance.DAT_MapFileReceivingState == 2) {
                if (DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile != NULL) {
                    MACRO_CALL(OpenSHC::OS_Func::_fclose)(DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile);
                    DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile = NULL;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_UNKNOWN_107);
                }
                DAT_GameSynchronyState::instance.DAT_MapFileReceivingState = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
        }

    }
}
}
