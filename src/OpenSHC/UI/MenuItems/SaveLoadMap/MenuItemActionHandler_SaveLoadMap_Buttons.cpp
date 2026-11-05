// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../SaveLoadMap.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004943B0
        void SaveLoadMap::MenuItemActionHandler_SaveLoadMap_Buttons(int action, ...)
        {
            switch (action) {
            case -1:
                // scroll up
                if (DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset > 0) {
                    --DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
                }
                break;
            case -2:
                // scroll down
                if (DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset
                    < DAT_MenuTextInputState::instance.fileListEntryCount
                        - DAT_MenuTextInputState::instance.fileListVisibleRowCount) {
                    ++DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
                }
                break;
            case 2: {
                // The original copies the name and appends the extension inline, so the macros are used here.
                char fileName[1008]; // the size of the original's buffer
                // load
                // An if around the body, so the early exit shares the case's resetMouseState2 call as in the original.
                if (DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex != -1) {
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                        && DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                        && DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices2
                                [DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices
                                        [DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex
                                            + DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset]
                                    - 1]
                            == 0) {
                        break;
                    }
                    int const listIndex = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex
                        + DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
                    strcpy(fileName,
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                            DAT_ResourceManager::ptr)(
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[listIndex]));
                    // One resolve call per arm and != tests with the else arm last: the original lays the chain out
                    // this way.
                    if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_UNUSED_CREATE_SIEGE) {
                        // ".tmp"
                        strcat(fileName, S__TMP_005A75A8);
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                            DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_MAPS, fileName);
                    } else if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS) {
                        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                            && DAT_GameSynchronyState::instance.currentGameMode
                                != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                            // ".msv"
                            strcat(fileName, S__MSV_005A7498);
                            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                                DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_UNKNOWN, fileName);
                        } else {
                            // ".sav"
                            strcat(fileName, S__SAV_005A75A0);
                            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                                DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_UNKNOWN, fileName);
                        }
                    } else {
                        // ".map"
                        strcat(fileName, S__MAP_005A2294);
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                            DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_MAPS, fileName);
                    }
                    if (MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::doesFileOfActiveResourceExist,
                            DAT_ResourceManager::ptr)()) {
                        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                            && DAT_GameSynchronyState::instance.currentGameMode
                                != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs,
                                DAT_MenuTextInputState::ptr)();
                            strcpy(DAT_GameSynchronyState::instance.shortMapName,
                                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                                    DAT_ResourceManager::ptr)(
                                    DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[listIndex]));
                            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_UNKNOWN_40);
                        } else {
                            DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 31;
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                                DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_PROGRESS_BAR_BOX);
                            DAT_GameCore::instance.mapLoadedForEditor = 1;
                        }
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                break;
            }
            case 3: {
                // The original copies the name and appends the extension inline, so the macros are used here.
                char fileName[1008]; // the size of the original's buffer
                // save
                // An if around the body, so the early exit shares the case's resetMouseState2 call as in the original.
                if (DAT_UserTextHandlerState::instance
                        .textContentLengthArray[DAT_UserTextHandlerState::instance.textArrayIndex]
                    != 0) {
                    // One resolve call per arm and != tests with the else arm last: the original lays the chain out
                    // this way.
                    if (DAT_MenuTextInputState::instance.DAT_ArrayOfMapU3EndInt2[0] != 0) {
                        strcpy(fileName,
                            MACRO_CALL_MEMBER(
                                OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)());
                        // ".tmp"
                        strcat(fileName, S__TMP_005A75A8);
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                            DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_MAPS, fileName);
                    } else if (DAT_GameCore::instance.currentMenuViewType
                        != OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES) {
                        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                            && DAT_GameSynchronyState::instance.currentGameMode
                                != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                            strcpy(fileName,
                                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getCurrentText,
                                    DAT_UserTextHandlerState::ptr)());
                            // ".msv"
                            strcat(fileName, S__MSV_005A7498);
                            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                                DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_UNKNOWN, fileName);
                        } else {
                            strcpy(fileName,
                                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getCurrentText,
                                    DAT_UserTextHandlerState::ptr)());
                            // ".sav"
                            strcat(fileName, S__SAV_005A75A0);
                            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                                DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_UNKNOWN, fileName);
                        }
                    } else {
                        strcpy(fileName,
                            MACRO_CALL_MEMBER(
                                OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)());
                        // ".map"
                        strcat(fileName, S__MAP_005A2294);
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                            DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_MAPS, fileName);
                    }
                    if (MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::doesFileOfActiveResourceExist,
                            DAT_ResourceManager::ptr)()) {
                        DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 30;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                            DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_YES_NO_DIALOG);
                    } else if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                        && DAT_GameSynchronyState::instance.currentGameMode
                            != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                        strcpy(DAT_GameSynchronyState::instance.shortMapName,
                            MACRO_CALL_MEMBER(
                                OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)());
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs,
                            DAT_MenuTextInputState::ptr)();
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = DAT_GameCore::instance.mapTimeInTicks;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                            = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::computeSomeHashOnUnitArray,
                                DAT_GameSynchronyState::ptr)();
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = 0;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SAVE);
                    } else {
                        DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 32;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                            DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_PROGRESS_BAR_BOX);
                    }
                    DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex,
                        DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_NINE__FILTER_B);
                    DAT_UserTextHandlerState::instance.allowUserTextInput = 1;
                }
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                break;
            }
            case 17:
                // back
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                DAT_MenuTextInputState::instance.dialogResult = -1;
                break;
            }
        }

    }
}
}
