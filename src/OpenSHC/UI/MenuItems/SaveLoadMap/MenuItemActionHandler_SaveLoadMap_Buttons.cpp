#include "../SaveLoadMap.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Game::GameMode;
        using OpenSHC::IO::FileResourceType;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x004943B0
        void SaveLoadMap::MenuItemActionHandler_SaveLoadMap_Buttons(int param_1, ...)
        {
            int iVar1;
            char cVar2;
            char* _mapName;
            BOOLEnum BVar3;
            undefined4 uVar4;
            undefined4 uVar5;
            char* pcVar6;
            char* pcVar7;
            char* pcVar8;
            FileResourceType FVar9;
            MenuModalType dialogID;
            char local_3f4[4];
            char local_3f0[1004];
            uint local_4;
            pcVar6 = local_3f4;
            _mapName = local_3f4;
            pcVar7 = local_3f4;
            pcVar8 = local_3f4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)local_3f4;
            switch (param_1) {
            case 2:
                /*
                  "Load"
                 */
                if (DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex == -1)
                    goto LAB_0049461b;
                if (((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                        && (DAT_GameSynchronyState::instance.currentGameMode
                            != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER))
                    && (DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices
                            [DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices
                                    [DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex
                                        + DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset + -1]
                                + 499]
                        == 0))
                    break;
                iVar1 = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex
                    + DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset;
                _mapName = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                    DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar1 + -1]);
                pcVar6 = local_3f4;
                do {
                    cVar2 = *_mapName;
                    *pcVar6 = cVar2;
                    _mapName = _mapName + 1;
                    pcVar6 = pcVar6 + 1;
                } while (cVar2 != '\0');
                if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_UNUSED_CREATE_SIEGE) {
                    pcVar6 = (local_3f4 - 1);
                    do {
                        _mapName = pcVar6 + 1;
                        pcVar6 = pcVar6 + 1;
                    } while (*_mapName != '\0');
                    (*(char*)&uVar4) = '.';
                    (*(char*)((char*)&uVar4 + 1)) = 't';
                    (*(char*)((char*)&uVar4 + 2)) = 'm';
                    (*(char*)((char*)&uVar4 + 3)) = 'p';
                LAB_00494566:
                    *(undefined4*)pcVar6 = uVar4;
                    pcVar6[4] = '\0';
                    FVar9 = OpenSHC::IO::FRT_MAPS;
                } else {
                    if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS) {
                        pcVar6 = (local_3f4 - 1);
                        do {
                            _mapName = pcVar6 + 1;
                            pcVar6 = pcVar6 + 1;
                        } while (*_mapName != '\0');
                        (*(char*)&uVar4) = '.';
                        (*(char*)((char*)&uVar4 + 1)) = 'm';
                        (*(char*)((char*)&uVar4 + 2)) = 'a';
                        (*(char*)((char*)&uVar4 + 3)) = 'p';
                        goto LAB_00494566;
                    }
                    if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                        || (DAT_GameSynchronyState::instance.currentGameMode
                            == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                        pcVar6 = (local_3f4 - 1);
                        do {
                            _mapName = pcVar6;
                            pcVar6 = _mapName + 1;
                        } while (_mapName[1] != '\0');
                        strcpy(_mapName + 1, ".sav");
                        FVar9 = OpenSHC::IO::FRT_UNKNOWN;
                    } else {
                        pcVar6 = (local_3f4 - 1);
                        do {
                            _mapName = pcVar6;
                            pcVar6 = _mapName + 1;
                        } while (_mapName[1] != '\0');
                        strcpy(_mapName + 1, ".msv");
                        FVar9 = OpenSHC::IO::FRT_UNKNOWN;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    FVar9, (char const*)((int)(local_3f4)));
                BVar3 = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::doesFileOfActiveResourceExist, DAT_ResourceManager::ptr)();
                if (BVar3 != FALSE) {
                    if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                        && (DAT_GameSynchronyState::instance.currentGameMode
                            != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs,
                            DAT_MenuTextInputState::ptr)();
                        pcVar6 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                            DAT_ResourceManager::ptr)(
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar1 + -1]);
                        _mapName = DAT_GameSynchronyState::instance.shortMapName;
                        do {
                            cVar2 = *pcVar6;
                            *_mapName = cVar2;
                            pcVar6 = pcVar6 + 1;
                            _mapName = _mapName + 1;
                        } while (cVar2 != '\0');
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(((GameCommandType)0x28));
                        MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                        ;
                    }
                    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 0x1f;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                        DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_PROGRESS_BAR_BOX);
                    DAT_GameCore::instance.field115_0x1d98 = 1;
                }
            LAB_0049461b:
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                ;
                return;
            case 3:
                if (DAT_UserTextHandlerState::instance
                        .textContentLengthArray[DAT_UserTextHandlerState::instance.textArrayIndex]
                    == 0)
                    goto LAB_00494849;
                if (DAT_MenuTextInputState::instance.field49_0xac == 0) {
                    if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES) {
                        pcVar6 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                        do {
                            cVar2 = *pcVar6;
                            *pcVar8 = cVar2;
                            pcVar6 = pcVar6 + 1;
                            pcVar8 = pcVar8 + 1;
                        } while (cVar2 != '\0');
                        pcVar6 = (local_3f4 - 1);
                        do {
                            _mapName = pcVar6 + 1;
                            pcVar6 = pcVar6 + 1;
                        } while (*_mapName != '\0');
                        (*(char*)&uVar5) = '.';
                        (*(char*)((char*)&uVar5 + 1)) = 'm';
                        (*(char*)((char*)&uVar5 + 2)) = 'a';
                        (*(char*)((char*)&uVar5 + 3)) = 'p';
                        goto LAB_0049477a;
                    }
                    if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                        || (DAT_GameSynchronyState::instance.currentGameMode
                            == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                        pcVar6 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                        do {
                            cVar2 = *pcVar6;
                            *pcVar7 = cVar2;
                            pcVar6 = pcVar6 + 1;
                            pcVar7 = pcVar7 + 1;
                        } while (cVar2 != '\0');
                        pcVar6 = (local_3f4 - 1);
                        do {
                            _mapName = pcVar6;
                            pcVar6 = _mapName + 1;
                        } while (_mapName[1] != '\0');
                        strcpy(_mapName + 1, ".sav");
                        FVar9 = OpenSHC::IO::FRT_UNKNOWN;
                    } else {
                        pcVar6 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                        do {
                            cVar2 = *pcVar6;
                            *_mapName = cVar2;
                            pcVar6 = pcVar6 + 1;
                            _mapName = _mapName + 1;
                        } while (cVar2 != '\0');
                        pcVar6 = (local_3f4 - 1);
                        do {
                            _mapName = pcVar6;
                            pcVar6 = _mapName + 1;
                        } while (_mapName[1] != '\0');
                        strcpy(_mapName + 1, ".msv");
                        FVar9 = OpenSHC::IO::FRT_UNKNOWN;
                    }
                } else {
                    _mapName = MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                    do {
                        cVar2 = *_mapName;
                        *pcVar6 = cVar2;
                        _mapName = _mapName + 1;
                        pcVar6 = pcVar6 + 1;
                    } while (cVar2 != '\0');
                    pcVar6 = (local_3f4 - 1);
                    do {
                        _mapName = pcVar6 + 1;
                        pcVar6 = pcVar6 + 1;
                    } while (*_mapName != '\0');
                    (*(char*)&uVar5) = '.';
                    (*(char*)((char*)&uVar5 + 1)) = 't';
                    (*(char*)((char*)&uVar5 + 2)) = 'm';
                    (*(char*)((char*)&uVar5 + 3)) = 'p';
                LAB_0049477a:
                    *(undefined4*)pcVar6 = uVar5;
                    pcVar6[4] = '\0';
                    FVar9 = OpenSHC::IO::FRT_MAPS;
                }
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    FVar9, (char const*)((int)(local_3f4)));
                BVar3 = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::doesFileOfActiveResourceExist, DAT_ResourceManager::ptr)();
                if (BVar3 == FALSE) {
                    if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                        || (DAT_GameSynchronyState::instance.currentGameMode
                            == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                        DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 0x20;
                        dialogID = OpenSHC::UI::Enums::MMT_PROGRESS_BAR_BOX;
                        goto LAB_0049481f;
                    }
                    pcVar6 = MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                    _mapName = DAT_GameSynchronyState::instance.shortMapName;
                    do {
                        cVar2 = *pcVar6;
                        *_mapName = cVar2;
                        pcVar6 = pcVar6 + 1;
                        _mapName = _mapName + 1;
                    } while (cVar2 != '\0');
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = DAT_GameCore::instance.mapTimeInTicks;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                        = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::computeSomeHashOnUnitArray,
                            DAT_GameSynchronyState::ptr)();
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SAVE);
                } else {
                    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 0x1e;
                    dialogID = OpenSHC::UI::Enums::MMT_YES_NO_DIALOG;
                LAB_0049481f:
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                        DAT_MenuTextInputState::ptr)(dialogID);
                }
                DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    9);
                DAT_UserTextHandlerState::instance.allowUserTextInput = 1;
            LAB_00494849:
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                ;
                return;
            case 0x11:
                /*
                  "Back"
                 */
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                DAT_MenuTextInputState::instance.dialogResult = 0xffffffff;
                break;
            case -2:
                if (DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset
                    < DAT_MenuTextInputState::instance.field32_0x74 - DAT_MenuTextInputState::instance.field36_0x84) {
                    DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset
                        = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset + 1;
                    ;
                }
                break;
            case -1:
                if (0 < DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset) {
                    DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset
                        = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset + -1;
                    ;
                }
            };
        }

    }
}
}
