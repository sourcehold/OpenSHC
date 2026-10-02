#include "../SendReceiveMap.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

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
        // FUNCTION: STRONGHOLDCRUSADER 0x004B10D0
        void SendReceiveMap::MenuItemActionHandler_SendReceiveMap_Main(int param_1, ...)
        {
            char cVar1;
            char* pcVar2;
            char* _fileName;
            FILE* _fileHandle;
            char* pcVar3;
            int _addressee;
            FILE** ppFVar4;
            char local_3f4[4];
            char local_3f0[1004];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)local_3f4;
            if (param_1 != 3) {
                if ((param_1 == 0x44) && (DAT_GameSynchronyState::instance.DAT_MapFileReceivingState == 0)) {
                    DAT_GameSynchronyState::instance.DAT_MapFileReceivingState = 1;
                    pcVar2 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                        DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                            .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                                + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + -1]);
                    pcVar3 = local_3f4;
                    do {
                        cVar1 = *pcVar2;
                        *pcVar3 = cVar1;
                        pcVar2 = pcVar2 + 1;
                        pcVar3 = pcVar3 + 1;
                    } while (cVar1 != '\0');
                    pcVar3 = (local_3f4 - 1);
                    do {
                        pcVar2 = pcVar3;
                        pcVar3 = pcVar2 + 1;
                    } while (pcVar2[1] != '\0');
                    strcpy(pcVar2 + 1, ".map");
                    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                        DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_MAPS, (char const*)((int)(local_3f4)));
                    DAT_GameSynchronyState::instance.mapSendingFileSize = MACRO_CALL_MEMBER(
                        OpenSHC::IO::ResourceManager_Func::getCurrentResourceSize, DAT_ResourceManager::ptr)();
                    DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile = (FILE*)0x0;
                    /*
                      Open the same file 8 times, for each lobby player once
                     */
                    _addressee = 1;
                    do {
                        DAT_GameSynchronyState::instance.field290_0x109e20[_addressee] = 0;
                        DAT_GameSynchronyState::instance.mapSendingByteBufferAddress[_addressee] = 0;
                        DAT_GameSynchronyState::instance.field289_0x109dfc[_addressee] = 0;
                        if (DAT_GameSynchronyState::instance.field282_0x109d98[_addressee] == 1) {
                            _fileName = MACRO_CALL_MEMBER(
                                OpenSHC::IO::ResourceManager_Func::getFileNameOfCurrentActiveResource,
                                DAT_ResourceManager::ptr)();
                            _fileHandle = MACRO_CALL(OpenSHC::OS_Func::_fopen)(_fileName, "rb");
                            DAT_GameSynchronyState::instance.mapSendingFileHandles[_addressee] = _fileHandle;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                                = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices
                                      [DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                                          + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + -1];
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                                = DAT_GameSynchronyState::instance.mapSendingFileSize;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _addressee;
                            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_RECEIVE_SENT_MAPPARTUnk);
                        }
                        _addressee = _addressee + 1;
                    } while (_addressee < 9);
                    ;
                }
                goto LAB_004b12ab;
            }
            if (DAT_GameSynchronyState::instance.DAT_MapFileReceivingState == 1) {
                ppFVar4 = DAT_GameSynchronyState::instance.mapSendingFileHandles + 1;
                do {
                    if (*ppFVar4 != (FILE*)0x0) {
                        MACRO_CALL(OpenSHC::OS_Func::_fclose)(*ppFVar4);
                        *ppFVar4 = (FILE*)0x0;
                    }
                    ppFVar4 = ppFVar4 + 1;
                } while ((int)ppFVar4 < 0x1a27560);
            LAB_004b1298:
                DAT_GameSynchronyState::instance.DAT_MapFileReceivingState = 0;
            } else if (DAT_GameSynchronyState::instance.DAT_MapFileReceivingState == 2) {
                if (DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile != (FILE*)0x0) {
                    MACRO_CALL(OpenSHC::OS_Func::_fclose)(DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile);
                    DAT_GameSynchronyState::instance.FILEPTR_ReceivedMapFile = (FILE*)0x0;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (OpenSHC::Commands::GameCommandType)(OpenSHC::Commands::GCT_START_OR_STOP_SEND_MAP_FILEUnk
                            | OpenSHC::Commands::GCT_MULTIPLAYER_ANNOUNCE_HOST));
                }
                goto LAB_004b1298;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
        LAB_004b12ab:;
        }

    }
}
}
