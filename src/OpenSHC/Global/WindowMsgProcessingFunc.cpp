#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A // WinUser.h gates this behind _WIN32_WINNT >= 0x0400
#endif

#include "../Global.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/MenuItems/IdentityOptions.func.hpp"
#include "OpenSHC/UI/MenuItems/NewEventCondition.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Coordinates/XYPairShort.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Input/Mouse/MouseClickInteraction.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_00df5538.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CheatCodeStringTrackerIndex.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_InsertKeyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ModifierKeyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_ShortcutDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {

using Commands::GameCommandType;
using Commands::MappersEnum;
using Coordinates::XYPairShort;
using Game::GameMode;
using Game::GameMode2;
using Input::Mouse::MouseClickInteraction;
using Map::MapType2;
using Map::Buildings::BuildingType;
using Map::Units::UnitLogicState;
using Map::Units::UnitType;
using Text::TextArrayIndexType;
using UI::Enums::BuildingsAndStatusMenuTabType;
using UI::Enums::DisplayElementID;
using UI::Enums::MenuModalType;
using UI::Enums::MenuViewType;
using WindowsHelper::Enums::BOOLEnum;

/*
  This is the WindowProc   LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
  https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ms633573(v=vs.85)      It handles input and
  is in theory the main communication point with the OS. SHC however also   gathers input data using other C functions.
  - TheRedDaemon   decompilerscript: committed: 2025-01-30 21:57:43.216000
 */
// FUNCTION: STRONGHOLDCRUSADER 0x004B2AE0
LRESULT __stdcall Global::WindowMsgProcessingFunc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    short _activation;
    uint _cookie;
    int _xScreenSize;
    BOOLEnum _restore;
    BOOL _paintInGameMenuCheck;
    int _newIndex;
    int _tutorialStep;
    BOOL _spaceIngameMenuCheck;
    uint _newMapRotation;
    BOOL _leftKeyIngameMenuCheck;
    char* _pCurrentText;
    BOOL _enterIngameMenuCheck;
    BOOL _escInIngameMenu;
    LRESULT LVar1;
    BOOLEnum _akeyIngameMenuCheck;
    BOOLEnum BVar2;
    int* pSVar7;
    BOOLEnum _addKeyIngameMenu;
    BOOLEnum _subtractKeyIngameMenu;
    BOOL _screenshotInGameMenuCheck;
    BOOL _cheatInGameMenuCheck1;
    BOOL _altNumInGameMenuCheck;
    BOOL _tauntInGameMenuCheck;
    BOOLEnum _fkeyIngameMenuCheck;
    char* _pCurrentText2;
    int iVar3;
    uint uVar10;
    int iVar11;
    int _screenOffset;
    int _textIndex;
    HBINK* _hBinkPtr;
    int iVar4;
    HWND__* _hwnd;
    PAINTSTRUCT _paintstruct;
    int _currentSelectionID;
    int _armoryCtrl;
    uint _buildingID;
    int _barracksCtrl;
    int _currentPlayerSlotID;
    int _yScreenSize;
    short _yMousePos;
    short _xMousePos;
    int* _pGold;
    int _lordID;
    int _playerLordUID;
    int _lordUID;
    int _cheatCharIndex;
    ushort _buildingX;
    ushort _buildingY;
    MouseClickInteraction _clickType;
    XYPairShort _tile;
    char cVar1;
    _currentPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
    _cookie = MSVC_SecurityCookie::instance ^ (uint)&_hwnd;
    _hwnd = windowHandle;
    if (WM_KEYDOWN < message) {
        /*
          param_4 >> 0x10 == y
         */
        _xMousePos = (short)lParam;
        _yMousePos = (short)((uint)lParam >> 0x10);
        if (message < WM_LBUTTONDOWN) {
            if (message == WM_MOUSEMOVE) {
                MACRO_CALL_MEMBER(Input::MouseState_Func::updateMousePositionAndClicks, DAT_MouseState::ptr)(
                    _xMousePos, _yMousePos, Input::Mouse::MCI_MOVE);
                goto switchD_004b4d0c_doDefWindowProcA;
            }
            switch (message) {
            case WM_KEYUP:
                /*
                  WM_KEYUP
                 */
                switch (wParam) {
                case VK_LEFT:
                    /*
                      VK_LEFT
                     */
                    DAT_ScrollingHandler::instance.leftKeyDown_0x1c = FALSE;
                    break;
                case VK_UP:
                    /*
                      VK_UP
                     */
                    DAT_ScrollingHandler::instance.upKeyDown_0x24 = FALSE;
                    break;
                case VK_RIGHT:
                    /*
                      VK_RIGHT
                     */
                    DAT_ScrollingHandler::instance.rightKeyDown_0x18 = FALSE;
                    break;
                case VK_DOWN:
                    /*
                      VK_DOWN
                     */
                    DAT_ModifierKeyState::instance.downArrow = 0;
                    DAT_ScrollingHandler::instance.downKeyDown_0x20 = FALSE;
                }
                break;
            case WM_CHAR:
                /*
                 **** Note that keydown events are translated in char events if not swalloed   ****      WM_CHAR
                 */
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleCharacterCode,
                    DAT_UserTextHandlerState::ptr)((byte)wParam);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleCharacterIntoInputBuffer,
                    DAT_UserTextHandlerState::ptr)(wParam);
                break;
            case WM_SYSKEYDOWN:
                /*
                  WM_SYSKEYDOWN (ALT + ?)
                 */
                DAT_ModifierKeyState::instance.keyDownUnk = 1;
                switch (wParam) {
                case VK_MENU:
                    LVar1 = 1;
                    /*
                      VK_MENU (ALT key)
                     */
                    ;
                    return LVar1;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    goto switchD_004b482b_caseD_30;
                case 'C':
                    /*
                      c was pressed
                     */
                    if ((DAT_GameCore::instance.cheatModeFlag)
                        && (_cheatInGameMenuCheck1
                            = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(),
                            _cheatInGameMenuCheck1 == 0)) {
                        DAT_GameCore::instance.unlockAllHistoricalCampaigns = 1;
                    }
                    break;
                case 'D':
                    /*
                      key: D
                     */
                    if ((DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)
                        || ((DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU
                            && (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR)))) {
                        DAT_ViewportRenderState::instance.DAT_MapEditorDisplayLayer
                            = DAT_ViewportRenderState::instance.DAT_MapEditorDisplayLayer + 1;
                        if (2 < (int)DAT_ViewportRenderState::instance.DAT_MapEditorDisplayLayer) {
                            DAT_ViewportRenderState::instance.DAT_MapEditorDisplayLayer = 0;
                        }
                        MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                            UI::Enums::DEID_CONNECT_AND_PATH_LINKAGE_INFO_TEXT,
                            (dword)((int)(DAT_ViewportRenderState::instance.DAT_MapEditorDisplayLayer)));
                    }
                    break;
                case 'E':
                    /*
                      key E
                     */
                    if (((DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_PROPERTIES)
                            || (DAT_GameCore::instance.currentMenuViewType
                                == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING))
                        || ((DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU
                            && (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR)))) {
                        MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::killAllUnownedUnits, DAT_UnitsState::ptr)();
                    }
                    break;
                case 'H':
                    /*
                      H
                     */
                    if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR) {
                        DAT_GameCore::instance.isTimeHalted = (BOOLEnum)(!DAT_GameCore::instance.isTimeHalted2);
                        DAT_GameCore::instance.isTimeHalted2 = DAT_GameCore::instance.isTimeHalted;
                    }
                    break;
                case 'K':
                    /*
                      K
                     */
                    if ((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)
                        && (DAT_GameCore::instance.cheatModeFlag)) {
                        DAT_GameCore::instance.solitaryAllBuildingsAreFree
                            = (BOOLEnum)(!DAT_GameCore::instance.solitaryAllBuildingsAreFree);
                    }
                    break;
                case 'Q':
                    /*
                      Q
                     */
                    _screenshotInGameMenuCheck
                        = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
                    if (_screenshotInGameMenuCheck) {
                        MACRO_CALL_MEMBER(UI::Rendering::WindowAndDirectDraw_Func::takeScreenshot,
                            DAT_WindowAndDirectDraw::ptr)(DAT_ShortcutDefinedData::instance.ScreenshotFilenameVariant);
                        DAT_ShortcutDefinedData::instance.ScreenshotFilenameVariant
                            = DAT_ShortcutDefinedData::instance.ScreenshotFilenameVariant + 1;
                    }
                    break;
                case 'R':
                    /*
                      R
                     */
                    DAT_GameCore::instance.altRToggleMinimapHideWildlife
                        = DAT_GameCore::instance.altRToggleMinimapHideWildlife == 0;
                    break;
                case 'T':
                    if ((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                        && (DAT_GameSynchronyState::instance.currentGameMode
                            != Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                        MACRO_CALL(UI::DisplayElements_Func::TogglePlayerPingDisplayElementUnk)(
                            UI::Enums::DEID_PLAYER_PING_Unk_19, 1);
                    }
                    break;
                case 'U':
                    /*
                      U
                     */
                    if (((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)
                            && (DAT_GameCore::instance.currentMenuViewType
                                == UI::Enums::MVT_BUILDING_AND_STATUS_MENU))
                        && (DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                                .buildingType
                            == Map::Buildings::BT_DUNGEON)) {
                        DAT_GameCore::instance.solitaryAltUDungeon = TRUE;
                    }
                    break;
                case 'V':
                    /*
                      V
                     */
                    if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR) {
                        _lordID = DAT_GameState::instance
                                      .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                      .lordID;
                        if (_lordID) {
                            _playerLordUID = DAT_GameState::instance
                                                 .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                 .lordUID;
                            _lordUID = DAT_UnitsState::instance.units[_lordID].uid;
                            DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .lordID = 0;
                            DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].lordUID = 0;
                            if (_playerLordUID == _lordUID) {
                                DAT_UnitsState::instance.units[_lordID].logicalState = Map::Units::ULS_REMOVE;
                            }
                        }
                        DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].lordKilledByPlayerID = 0;
                    }
                    break;
                case 'X':
                    /*
                      X
                     */
                    if ((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_MULTIPLAYER)
                        && (DAT_GameCore::instance.cheatModeFlag)) {
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .popularity = 10000;
                        _pGold = DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].currentResources + 0xf;
                        *_pGold = *_pGold + 1000;
                    }
                    break;
                case VK_NUMPAD0:
                case VK_NUMPAD1:
                case VK_NUMPAD2:
                case VK_NUMPAD3:
                case VK_NUMPAD4:
                case VK_NUMPAD5:
                case VK_NUMPAD6:
                case VK_NUMPAD7:
                case VK_NUMPAD8:
                case VK_NUMPAD9:
                    wParam = wParam - '0';
                switchD_004b482b_caseD_30:
                    /*
                      0 - 9
                     */
                    /*
                      ? basically, pressing a number above the letters on keyboard or on the numpad
                     */
                    _altNumInGameMenuCheck
                        = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
                    if (!_altNumInGameMenuCheck)
                        break;
                    goto LAB_004b4af5;
                case VK_F10:
                    goto switchD_004b482b_caseD_79;
                case VK_F11:
                case VK_F12:
                    goto switchD_004b482b_caseD_7a;
                case VK_OEM_COMMA:
                    /*
                      COMMA
                     */
                    if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_PROPERTIES) {
                        if (DAT_MenuModalComposition1::instance.activeModalDialogID
                            == UI::Enums::MMT_EDITOR_MAP_TYPE_QUICK_CHANGE) {
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                        } else if (DAT_MenuModalComposition1::instance.activeModalDialogID
                            == UI::Enums::MMT_NONE) {
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition1::ptr)(
                                UI::Enums::MMT_EDITOR_MAP_TYPE_QUICK_CHANGE, FALSE);
                        }
                    }
                    break;
                case VK_OEM_3:
                case VK_OEM_7:
                    /*
                      ~ or single quote `
                     */
                    if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_EDIT_SCENARIO) {
                        DAT_GameState::instance.mapAndTime.editScenarioExtraOptions
                            = DAT_GameState::instance.mapAndTime.editScenarioExtraOptions ^ 1;
                    }
                }
            }
            goto switchD_004b4d0c_doDefWindowProcA;
        }
        switch (message) {
        case WM_LBUTTONDOWN:
            MACRO_CALL_MEMBER(Input::MouseState_Func::updateMousePositionAndClicks, DAT_MouseState::ptr)(
                _xMousePos, _yMousePos, Input::Mouse::MCI_LEFTDOWN);
            break;
        case WM_LBUTTONUP:
            _clickType = Input::Mouse::MCI_LEFTUP;
            goto LAB_004b4d15;
        case WM_RBUTTONDOWN:
            MACRO_CALL_MEMBER(Input::MouseState_Func::updateMousePositionAndClicks, DAT_MouseState::ptr)(
                _xMousePos, _yMousePos, Input::Mouse::MCI_RIGHTDOWN);
            break;
        case WM_RBUTTONUP:
            _clickType = Input::Mouse::MCI_RIGHTUP;
            goto LAB_004b4d15;
        case WM_MBUTTONDOWN:
            MACRO_CALL_MEMBER(Input::MouseState_Func::updateMousePositionAndClicks, DAT_MouseState::ptr)(
                _xMousePos, _yMousePos, Input::Mouse::MCI_MIDDOWN);
            break;
        case WM_MBUTTONUP:
            _clickType = Input::Mouse::MCI_MIDUP;
        LAB_004b4d15:
            MACRO_CALL_MEMBER(Input::MouseState_Func::updateMousePositionAndClicks, DAT_MouseState::ptr)(
                _xMousePos, _yMousePos, _clickType);
            break;
        case WM_MOUSEWHEEL:
            MACRO_CALL_MEMBER(Input::MouseState_Func::updateMouseWheelStatus, DAT_MouseState::ptr)(
                (int)(short)(wParam >> 0x10));
        }
        goto switchD_004b4d0c_doDefWindowProcA;
    }
    if (message != WM_KEYDOWN) {
        switch (message) {
        case WM_CREATE:
        case WM_MOVE:
            if (DAT_WindowAndDirectDraw::instance.runGameAsExclusiveFullscreen)
                break;
            DAT_WindowAndDirectDraw::instance.windowMoveEventBlitCountdown = 10;
            goto LAB_004b2b45;
        case WM_DESTROY:
            DAT_WindowAndDirectDraw::instance.postWindowCloseMessage = 3;
            DAT_WindowAndDirectDraw::instance.windowHandle = (HWND__*)0x0;
            PostQuitMessage(0);
            break;
        case WM_SIZE:
            if (DAT_WindowAndDirectDraw::instance.runGameAsExclusiveFullscreen) {
                _yScreenSize = GetSystemMetrics(SM_CYSCREEN);
                _xScreenSize = GetSystemMetrics(SM_CXSCREEN);
                SetRect(&DAT_WindowAndDirectDraw::instance.clientOnScreenCoords, 0, 0, _xScreenSize, _yScreenSize);
                break;
            }
        LAB_004b2b45:
            MACRO_CALL_MEMBER(
                UI::Rendering::WindowAndDirectDraw_Func::reinitWindow, DAT_WindowAndDirectDraw::ptr)();
            /*
              The following three calls fill the RECT structure with coords that describe   the client in screen
              coordinates.
             */
            GetClientRect(windowHandle, &DAT_WindowAndDirectDraw::instance.clientOnScreenCoords);
            ClientToScreen(
                windowHandle, (LPPOINT)((int)((tagPOINT*)&DAT_WindowAndDirectDraw::instance.clientOnScreenCoords)));
            ClientToScreen(windowHandle,
                (LPPOINT)((int)((tagPOINT*)&DAT_WindowAndDirectDraw::instance.clientOnScreenCoords.right)));
            break;
        case WM_SETFOCUS:
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::resumeAudioSample, DAT_SoundSystemState::ptr)();
            _hBinkPtr = DAT_BinkControlState::instance.binkObjPtrArray;
            do {
                if (*_hBinkPtr != (HBINK)0x0) {
                    BinkPause(*_hBinkPtr, 0);
                }
                _hBinkPtr = _hBinkPtr + 1;
            } while ((int)_hBinkPtr < 0x2157570);
            break;
        case WM_KILLFOCUS:
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::pauseAudioSample, DAT_SoundSystemState::ptr)();
            _hBinkPtr = DAT_BinkControlState::instance.binkObjPtrArray;
            do {
                if (*_hBinkPtr != (HBINK)0x0) {
                    BinkPause(*_hBinkPtr, 1);
                }
                _hBinkPtr = _hBinkPtr + 1;
            } while ((int)_hBinkPtr < 0x2157570);
            break;
        case WM_PAINT:
            BeginPaint(windowHandle, &_paintstruct);
            EndPaint(windowHandle, &_paintstruct);
            _paintInGameMenuCheck
                = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if (!_paintInGameMenuCheck) {
                DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
                MACRO_CALL_MEMBER(UI::Rendering::WindowAndDirectDraw_Func::renderBltAndFlip,
                    DAT_WindowAndDirectDraw::ptr)(1);
            }
            goto LAB_004b2cfd;
        case WM_CLOSE:
        case WM_QUIT:
            DAT_WindowAndDirectDraw::instance.postWindowCloseMessage = 3;
            break;
        case WM_ACTIVATEAPP:
            _activation = (short)wParam;
            if (_activation == 1) {
                DAT_WindowAndDirectDraw::instance.gameFocused = TRUE;
            } else if (_activation == 2) {
                DAT_WindowAndDirectDraw::instance.gameFocused = TRUE;
            } else if (!_activation) {
                /*
                  app is being deactivated
                 */
                DAT_WindowAndDirectDraw::instance.gameFocused = FALSE;
                DAT_WindowAndDirectDraw::instance.isNotProcessingInputEvents = TRUE;
                MACRO_CALL_MEMBER(
                    Audio::MSS::SoundSystem_Func::endSpeechSoundStreams, DAT_SoundSystemState::ptr)();
            }
            if ((DAT_WindowAndDirectDraw::instance.isNotProcessingInputEvents)
                && (DAT_WindowAndDirectDraw::instance.gameFocused)) {
                /*
                  restore everything
                 */
                _restore = MACRO_CALL_MEMBER(UI::Rendering::WindowAndDirectDraw_Func::restoreDXSurfaces,
                    DAT_WindowAndDirectDraw::ptr)();
                if (_restore) {
                    /*
                      Restoring DirectX succeeded
                     */
                    MACRO_CALL_MEMBER(
                        UI::Rendering::WindowAndDirectDraw_Func::reinitWindow, DAT_WindowAndDirectDraw::ptr)();
                }
                MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                MACRO_CALL_MEMBER(Input::MouseState_Func::storeXYAndResetMouseState, DAT_MouseState::ptr)();
            }
            DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
            break;
        case WM_DISPLAYCHANGE:
            DAT_WindowAndDirectDraw::instance.screenHorizontalResolutionInPixels = lParam & 0xffff;
            DAT_WindowAndDirectDraw::instance.screenVerticalResolutionInPixels = (uint)lParam >> 0x10;
            DAT_WindowAndDirectDraw::instance.depthBitsPerPixel = wParam;
        }
        goto switchD_004b4d0c_doDefWindowProcA;
    }
    /*
      cheat mode activation check
     */
    /*
      assuming WM_KEYDOWN
     */
    DAT_ModifierKeyState::instance.keyDownUnk = 1;
    if ((((DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAIN_MENU)
             && (DAT_ModifierKeyState::instance.ctrl))
            && (!DAT_GameCore::instance.cheatModeFlag))
        && (wParam == (byte)DAT_ShortcutDefinedData::instance.cheatCode[DAT_CheatCodeStringTrackerIndex::instance])) {
        _newIndex = DAT_CheatCodeStringTrackerIndex::instance + 1;
        _cheatCharIndex = DAT_CheatCodeStringTrackerIndex::instance + 1;
        DAT_CheatCodeStringTrackerIndex::instance = _newIndex;
        if (DAT_ShortcutDefinedData::instance.cheatCode[_cheatCharIndex] == '\0') {
            DAT_GameCore::instance.cheatModeFlag = TRUE;
        }
    } else {
        DAT_CheatCodeStringTrackerIndex::instance = 0;
    }
    switch (wParam) {
    case VK_BACK:
        /*
          VK_BACK (Backspace)
         */
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleBackspace, DAT_UserTextHandlerState::ptr)();
        MACRO_CALL_MEMBER(
            Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(0xf8);
        break;
    case VK_TAB:
        /*
          VK_TAB
         */
        if (!(lParam & 0x40000000U)) {
            MACRO_CALL_MEMBER(Game::GameCore_Func::hideOrUnhideUI, DAT_GameCore::ptr)();
        }
        break;
    case VK_RETURN:
        /*
          VK_RETURN
         */
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleReturnKey, DAT_UserTextHandlerState::ptr)();
        MACRO_CALL_MEMBER(
            Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(0xf1);
        if ((((DAT_GameCore::instance.gameMode_2 == Game::GM_SKIRMISH_AND_MULTIPLAYER)
                 && (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_CHAT))
                && (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER))
            || (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_LOBBY_MENU)) {
            if (DAT_UserTextHandlerState::instance.textArrayIndex == ((TextArrayIndexType)4)) {
                _pCurrentText = MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                _pCurrentText2 = _pCurrentText;
                do {
                    cVar1 = *_pCurrentText2;
                    _pCurrentText2 = _pCurrentText2 + 1;
                } while (cVar1 != '\0');
                for (_textIndex = 0; _textIndex < (int)_pCurrentText2 - (int)(_pCurrentText + 1); _textIndex++) {
                    if (_pCurrentText[_textIndex] != ' ') {
                        DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 0;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(Commands::GCT_TAUNT_OR_CHAT);
                        MACRO_CALL_MEMBER(
                            Text::UserTextHandler_Func::clearTextAndCursor, DAT_UserTextHandlerState::ptr)();
                        if (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_LOBBY_MENU) {
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                        }
                        break;
                    }
                }
            }
        } else if (((DAT_GameCore::instance.gameMode_2 == Game::GM_SKIRMISH_AND_MULTIPLAYER)
                       && (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE))
            && (_enterIngameMenuCheck
                = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(),
                _enterIngameMenuCheck != 0)) {
            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_ALLIES, FALSE);
            } else {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_CHAT, FALSE);
                DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    4);
                MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::clearTextAndCursor, DAT_UserTextHandlerState::ptr)();
            }
        } else if (DAT_MenuModalComposition1::instance.activeModalDialogID
            == UI::Enums::MMT_IDENTITY_OPTIONS) {
            MACRO_CALL(UI::MenuItems::IdentityOptions_Func::MenuItemActionHandler_IdentityOptions_Confirm)(
                0x11);
        }
        break;
    case VK_ESCAPE:
        /*
          ESC
         */
        if ((lParam & 0x40000000U))
            break;
        if ((DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_UNKNOWN_26_CAMPAIGN_RELATEDUnk)
            || (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_INTRO_VIDEO)) {
            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                UI::Enums::MVT_GAME_START_ENTER_NAME, 0);
            goto LAB_004b38a3;
        }
        if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_QUIT_DIALOG) {
            if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 0x2f)
                goto LAB_004b38a3;
        } else {
            if (DAT_MenuModalComposition1::instance.activeModalDialogID
                == UI::Enums::MMT_ONLINE_VOTE_QUIT_GAME) {
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                /*
                  Escape ally switching
                 */
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(Commands::GCT_SEND_QUIT_GAME_VOTE);
                goto LAB_004b33a8;
            }
            if (DAT_MenuModalComposition1::instance.activeModalDialogID
                == UI::Enums::MMT_NEW_EVENT_CONDITION) {
                MACRO_CALL(
                    UI::MenuItems::NewEventCondition_Func::MenuItemActionHandler_NewEventCondition_Main)(0x25);
                LVar1 = 0;
                ;
                return LVar1;
            }
            if ((DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_CHAT)
                || (DAT_MenuModalComposition1::instance.activeModalDialogID
                    == UI::Enums::MMT_SKIRMISH_CONNECTION_OPTIONS))
                goto LAB_004b33a8;
        }
        if (DAT_MenuTextInputState::instance.currentModalDialog != UI::Enums::MMT_NO_MENU) {
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_QUIT_DIALOG) {
                if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 2000) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(Commands::GCT_START_OR_STOP_SEND_MAP_FILEUnk);
                }
            } else if (DAT_MenuModalComposition1::instance.activeModalDialogID
                == UI::Enums::MMT_IDENTITY_OPTIONS) {
                MACRO_CALL(UI::MenuItems::IdentityOptions_Func::MenuItemActionHandler_IdentityOptions_Confirm)(
                    0x11);
                LVar1 = 0;
                ;
                return LVar1;
            }
            MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
            LVar1 = 0;
            ;
            return LVar1;
        }
        if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_UNUSED_HELP_TEXT_EDITOR) {
            MACRO_CALL_MEMBER(
                Text::TextEditorState_Func::openUnusedHelpTextEditorDialog, DAT_TextEditorState::ptr)(-1);
            LVar1 = 0;
            ;
            return LVar1;
        }
        if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_CREDITS) {
            MACRO_CALL_MEMBER(
                Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, DAT_TextEditorState::ptr)();
        } else {
            if ((DAT_TextEditorState::instance.helpDialogVariant)
                && (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_SCENARIO_DESCRIPTION)) {
                MACRO_CALL_MEMBER(
                    Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, DAT_TextEditorState::ptr)();
                LVar1 = 0;
                ;
                return LVar1;
            }
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_SELECT_CRUSADE)
                goto LAB_004b34ae;
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
            LAB_004b3517:
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                LVar1 = 0;
                ;
                return LVar1;
            }
            _escInIngameMenu
                = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if (_escInIngameMenu) {
                if (DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR) {
                    if (DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT) {
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            UI::Enums::MVT_UNUSED_CREATE_SIEGE, 0);
                        LVar1 = 0;
                        ;
                        return LVar1;
                    }
                    if (DAT_GameCore::instance.specialMultiplayerState) {
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::disconnectDPlay,
                            DAT_GameSynchronyState::ptr)();
                        DAT_WindowAndDirectDraw::instance.postWindowCloseMessage = 1;
                        LVar1 = 0;
                        ;
                        return LVar1;
                    }
                    if (((DAT_GameCore::instance.menuSwitchDelay == -1)
                            || (DAT_GameCore::instance.menuViewToSwitchTo == UI::Enums::MVT_BUILD_MENU))
                        || (DAT_GameCore::instance.menuViewToSwitchTo
                            == UI::Enums::MVT_BUILDING_AND_STATUS_MENU)) {
                        MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                            DAT_MenuTextInputState::ptr)(UI::Enums::MMT_PAUSE_MENU);
                        LVar1 = 0;
                        ;
                        return LVar1;
                    }
                    goto LAB_004b38a3;
                }
                goto LAB_004b3517;
            }
            if ((DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MP_CONNECTION)
                || (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_LOBBY_MENU)) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(
                    Synchrony::GameSynchronyState_Func::disconnectDPlay, DAT_GameSynchronyState::ptr)();
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_MAIN_MENU, 0);
                LVar1 = 0;
                ;
                return LVar1;
            }
            if (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_SINGLEPLAYER_MAP_CHOICE) {
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_GAME_START_ENTER_NAME)
                    goto LAB_004b38a3;
                if (((DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_HISTORIC_CAMPAIGN_SELECT)
                        && (DAT_GameCore::instance.currentMenuViewType
                            != UI::Enums::MVT_UNUSED_ECONOMIC_GAMETYPE_SELECT))
                    && (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_CUSTOM_SCENARIOS)) {
                    if (DAT_GameCore::instance.currentMenuViewType
                        == (UI::Enums::MVT_UNUSED_HELP_TEXT_EDITOR
                            | UI::Enums::MVT_UNUSED_OLD_TITLE_MENU)) {
                        if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE) {
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                UI::Enums::MVT_INTRO_LOGOS, 0);
                            LVar1 = 0;
                            ;
                            return LVar1;
                        }
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                        LVar1 = 0;
                        ;
                        return LVar1;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == ((MenuViewType)0x18)) {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            (UI::Enums::MenuViewType)(UI::Enums::MVT_UNUSED_HELP_TEXT_EDITOR
                                | UI::Enums::MVT_UNUSED_OLD_TITLE_MENU),
                            0);
                        LVar1 = 0;
                        ;
                        return LVar1;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_PROPERTIES) {
                    LAB_004b33a8:
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                        LVar1 = 0;
                        ;
                        return LVar1;
                    }
                    if ((DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_HISTORIC_MISSION_SELECT)
                        && (DAT_GameCore::instance.currentMenuViewType
                            != UI::Enums::MVT_UNUSED_ECONOMIC_MISSION_SELECTUnk)) {
                        if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_NEW_MAP_MAPTYPE) {
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                UI::Enums::MVT_CUSTOM_SCENARIOS, 0);
                            LVar1 = 0;
                            ;
                            return LVar1;
                        }
                        if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_NEW_MAP_MAPSIZE) {
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                UI::Enums::MVT_NEW_MAP_MAPTYPE, 0);
                            LVar1 = 0;
                            ;
                            return LVar1;
                        }
                        if (DAT_GameCore::instance.currentMenuViewType
                            == UI::Enums::MVT_UNUSED_CHOOSE_AVAILABLE_KEEPS) {
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                        LAB_004b3756:
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                UI::Enums::MVT_NEW_MAP_MAPSIZE, 0);
                            LVar1 = 0;
                            ;
                            return LVar1;
                        }
                        if ((((((DAT_GameCore::instance.currentMenuViewType
                                    != UI::Enums::MVT_UNUSED_SOME_MISSION_STARTUnk)
                                   && (DAT_GameCore::instance.currentMenuViewType
                                       != UI::Enums::MVT_UNKNOWN_26_CAMPAIGN_RELATEDUnk))
                                  && (DAT_GameCore::instance.currentMenuViewType
                                      != UI::Enums::MVT_UNKNOWN_27_CAMPAIGNUnk))
                                 && ((DAT_GameCore::instance.currentMenuViewType
                                         != UI::Enums::MVT_SCENARIO_DESCRIPTION
                                     && (DAT_GameCore::instance.currentMenuViewType
                                         != UI::Enums::MVT_MISSION_FINISHED_TRANSITION))))
                                && (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_GAME_LOSTUnk))
                            && (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_EDIT_SCENARIO)) {
                            if (DAT_GameCore::instance.currentMenuViewType
                                == UI::Enums::MVT_HISTORIC_CAMPAIGN_INTRO) {
                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    UI::Enums::MVT_HISTORIC_MISSION_PICTURE, 0);
                                MACRO_CALL_MEMBER(
                                    Audio::MSS::SoundSystem_Func::endSpeechStreamsAndResetLoopFlags,
                                    DAT_SoundSystemState::ptr)();
                                LVar1 = 0;
                                ;
                                return LVar1;
                            }
                            if ((DAT_GameCore::instance.currentMenuViewType
                                    == UI::Enums::MVT_HISTORIC_MISSION_PICTURE)
                                || (DAT_GameCore::instance.currentMenuViewType
                                    == UI::Enums::MVT_HISTORIC_MISSION_INTRO)) {
                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
                                MACRO_CALL_MEMBER(
                                    Audio::MSS::SoundSystem_Func::endSpeechStreamsAndResetLoopFlags,
                                    DAT_SoundSystemState::ptr)();
                                LVar1 = 0;
                                ;
                                return LVar1;
                            }
                            if (DAT_GameCore::instance.currentMenuViewType
                                == UI::Enums::MVT_UNUSED_CHOOSE_GAME_TYPE)
                                goto LAB_004b3756;
                            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAIN_MENU) {
                                MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                                    DAT_MenuTextInputState::ptr)(UI::Enums::MMT_MAIN_MENU_OPTIONS);
                                LVar1 = 0;
                                ;
                                return LVar1;
                            }
                        }
                    LAB_004b38a3:
                        LVar1 = 0;
                        ;
                        return LVar1;
                    }
                }
            }
        }
        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
            UI::Enums::MMT_NONE, FALSE);
    LAB_004b34ae:
        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
            UI::Enums::MVT_MAIN_MENU, 0);
        LVar1 = 0;
        ;
        return LVar1;
    case VK_SPACE:
        /*
          VK_SPACE
         */
        if (!(lParam & 0x40000000U)) {
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_CRUSADER_TUTORIAL) {
                _tutorialStep = MACRO_CALL(UI::Helpers_Func::GetCurrentTutorialStep)();
                if (0x1c < _tutorialStep) {
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::toggleFlatView, DAT_TileMapState::ptr)(
                        DAT_TileMapState::instance.flatViewToggleValue1 ^ 1);
                }
            } else {
                _spaceIngameMenuCheck
                    = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
                if ((_spaceIngameMenuCheck)
                    && (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE)) {
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::toggleFlatView, DAT_TileMapState::ptr)(
                        DAT_TileMapState::instance.flatViewToggleValue1 ^ 1);
                }
            }
        }
        break;
    case VK_PRIOR:
        /*
          VK_PRIOR (Page Up)
         */
        MACRO_CALL_MEMBER(
            Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(0xfa);
        break;
    case VK_NEXT:
        /*
          VK_NEXT (Page Down)
         */
        MACRO_CALL_MEMBER(
            Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(0xfb);
        break;
    case VK_END:
        /*
          VK_END
         */
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::moveCursorToEnd, DAT_UserTextHandlerState::ptr)();
        MACRO_CALL_MEMBER(
            Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(0xf7);
        break;
    case VK_HOME:
        /*
          VK_HOME
         */
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetCursorToStart, DAT_UserTextHandlerState::ptr)();
        MACRO_CALL_MEMBER(
            Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(0xf6);
        break;
    case VK_LEFT:
        /*
          VK_LEFT
         */
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleLeftKey, DAT_UserTextHandlerState::ptr)();
        _leftKeyIngameMenuCheck
            = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if ((((!_leftKeyIngameMenuCheck)
                 || (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_NONE))
                || (!DAT_ModifierKeyState::instance.ctrl))
            || (DAT_MouseState::instance.rightClickState)) {
            if ((DAT_GameCore::instance.gameMode_2 != Game::GM_SKIRMISH_AND_MULTIPLAYER)
                || (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_CHAT)) {
                DAT_ScrollingHandler::instance.leftKeyDown_0x1c = TRUE;
            }
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleCharacterIntoInputBuffer,
                DAT_UserTextHandlerState::ptr)(0xf2);
        } else {
            uVar10 = DAT_TileMapState::instance.mapOrientation + 2U & 0x80000007;
            if ((int)uVar10 < 0) {
                uVar10 = (uVar10 - 1 | 0xfffffff8) + 1;
            }
            MACRO_CALL_MEMBER(Map::TileMapState_Func::setMapRotation, DAT_TileMapState::ptr)(uVar10);
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleCharacterIntoInputBuffer,
                DAT_UserTextHandlerState::ptr)(0xf2);
        }
        break;
    case VK_UP:
        /*
          VK_UP
         */
        BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if (((BVar2) && (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE))
            && ((DAT_ModifierKeyState::instance.ctrl && (!DAT_MouseState::instance.rightClickState)))) {
            /*
              zoom
             */
            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::resetupViewport, DAT_ViewportRenderState::ptr)(
                (uint)(!DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk));
            DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
            DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
        }
        if ((DAT_GameCore::instance.gameMode_2 != Game::GM_SKIRMISH_AND_MULTIPLAYER)
            || (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_CHAT)) {
            DAT_ScrollingHandler::instance.upKeyDown_0x24 = TRUE;
        }
        MACRO_CALL_MEMBER(
            Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(0xf4);
        break;
    case VK_RIGHT:
        /*
          VK_RIGHT
         */
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleRightKey, DAT_UserTextHandlerState::ptr)();
        BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if ((((!BVar2) || (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_NONE))
                || (!DAT_ModifierKeyState::instance.ctrl))
            || (DAT_MouseState::instance.rightClickState)) {
            if ((DAT_GameCore::instance.gameMode_2 != Game::GM_SKIRMISH_AND_MULTIPLAYER)
                || (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_CHAT)) {
                DAT_ScrollingHandler::instance.rightKeyDown_0x18 = TRUE;
            }
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleCharacterIntoInputBuffer,
                DAT_UserTextHandlerState::ptr)(0xf3);
        } else {
            _newMapRotation = DAT_TileMapState::instance.mapOrientation + 6U & 0x80000007;
            if ((int)_newMapRotation < 0) {
                _newMapRotation = (_newMapRotation - 1 | 0xfffffff8) + 1;
            }
            MACRO_CALL_MEMBER(Map::TileMapState_Func::setMapRotation, DAT_TileMapState::ptr)(_newMapRotation);
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleCharacterIntoInputBuffer,
                DAT_UserTextHandlerState::ptr)(0xf3);
        }
        break;
    case VK_DOWN:
        /*
          VK_DOWN
         */
        BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if (((!BVar2) || (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_NONE))
            || ((!DAT_ModifierKeyState::instance.ctrl || (DAT_MouseState::instance.rightClickState)))) {
            if ((DAT_GameCore::instance.gameMode_2 != Game::GM_SKIRMISH_AND_MULTIPLAYER)
                || (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_CHAT)) {
                DAT_ScrollingHandler::instance.downKeyDown_0x20 = TRUE;
            }
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleCharacterIntoInputBuffer,
                DAT_UserTextHandlerState::ptr)(0xf5);
        } else {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::triggerLoweredView, DAT_TileMapState::ptr)(3);
            DAT_ModifierKeyState::instance.downArrow = 1;
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleCharacterIntoInputBuffer,
                DAT_UserTextHandlerState::ptr)(0xf5);
        }
        break;
    case VK_INSERT:
        /*
          VK_INSERT
         */
        DAT_InsertKeyState::instance.insert = DAT_InsertKeyState::instance.insert ^ 1;
        break;
    case VK_DELETE:
        /*
          VK_DELETE
         */
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::handleDeleteKey, DAT_UserTextHandlerState::ptr)();
        MACRO_CALL_MEMBER(
            Text::UserTextHandler_Func::handleCharacterIntoInputBuffer, DAT_UserTextHandlerState::ptr)(0xf9);
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        goto switchD_004b2d9a_caseD_30;
    case 'A':
        /*
          A
         */
        if ((((lParam & 0x40000000U))
                || (_akeyIngameMenuCheck
                    = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(),
                    !_akeyIngameMenuCheck))
            || (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_NONE))
            break;
        if (DAT_ModifierKeyState::instance.shift) {
            if (DAT_GameCore::instance.viewportFocusBeforeArmoryHotkey != -1) {
                MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                    DAT_ViewportRenderState::ptr)(DAT_GameCore::instance.viewportFocusBeforeArmoryHotkey);
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_BUILD_MENU, 0);
                }
                DAT_GameCore::instance.viewportFocusBeforeArmoryHotkey = -1;
            }
            break;
        }
        if (DAT_ModifierKeyState::instance.ctrl) {
            _armoryCtrl = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .armory.id;
            if (_armoryCtrl) {
                MACRO_CALL_MEMBER(
                    UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                    AlphaAndButtonSurfaceObj::ptr)(_armoryCtrl);
            }
            break;
        }
        _buildingID
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].armory.id;
        if (!_buildingID)
            break;
        DAT_GameCore::instance.viewportFocusBeforeArmoryHotkey
            = MACRO_CALL(Rendering_Func::ViewportBasedTileNumber)();
        goto LAB_004b3b12;
    case 'B':
        /*
          B
         */
        if ((((lParam & 0x40000000U))
                || (BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(), !BVar2))
            || (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_NONE))
            break;
        if (DAT_ModifierKeyState::instance.shift) {
            if (DAT_GameCore::instance.viewportFocusBeforeBarracksHotkey != -1) {
                MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                    DAT_ViewportRenderState::ptr)(DAT_GameCore::instance.viewportFocusBeforeBarracksHotkey);
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_BUILD_MENU, 0);
                }
                DAT_GameCore::instance.viewportFocusBeforeBarracksHotkey = -1;
            }
            break;
        }
        if (DAT_ModifierKeyState::instance.ctrl) {
            _barracksCtrl
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .barracks.id;
            if (_barracksCtrl) {
                MACRO_CALL_MEMBER(
                    UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                    AlphaAndButtonSurfaceObj::ptr)(_barracksCtrl);
            }
            break;
        }
        _buildingID
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].barracks.id;
        if (!_buildingID)
            break;
        DAT_GameCore::instance.viewportFocusBeforeBarracksHotkey
            = MACRO_CALL(Rendering_Func::ViewportBasedTileNumber)();
        goto LAB_004b3b12;
    case 'C':
        /*
          C
         */
        BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if (((BVar2) && (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE))
            && (!DAT_MouseState::instance.rightClickState)) {
            uVar10 = DAT_TileMapState::instance.mapOrientation + 6U & 0x80000007;
            if ((int)uVar10 < 0) {
                uVar10 = (uVar10 - 1 | 0xfffffff8) + 1;
            }
            MACRO_CALL_MEMBER(Map::TileMapState_Func::setMapRotation, DAT_TileMapState::ptr)(uVar10);
        }
        break;
    case 'E':
        /*
          E
         */
        if (((DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE)
                && (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU))
            && ((DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM
                || (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_SIEGETENT_SHIELD)))) {
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::queueUnitStance, DAT_TribesState::ptr)(
                DAT_TribesState::instance.DAT_CurrentTribeID, 2);
        }
        break;
    case 'G':
        /*
          G
         */
        if ((((lParam & 0x40000000U))
                || (BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(), !BVar2))
            || (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_NONE))
            break;
        if (DAT_ModifierKeyState::instance.shift) {
            if (DAT_GameCore::instance.viewportFocusBeforeGranaryHotkey != -1) {
                MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                    DAT_ViewportRenderState::ptr)(DAT_GameCore::instance.viewportFocusBeforeGranaryHotkey);
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_BUILD_MENU, 0);
                }
                DAT_GameCore::instance.viewportFocusBeforeGranaryHotkey = -1;
            }
            break;
        }
        if (DAT_ModifierKeyState::instance.ctrl) {
            iVar4 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .granary.id;
            if (iVar4) {
                MACRO_CALL_MEMBER(
                    UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                    AlphaAndButtonSurfaceObj::ptr)(iVar4);
            }
            break;
        }
        _buildingID
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].granary.id;
        if (!_buildingID)
            break;
        DAT_GameCore::instance.viewportFocusBeforeGranaryHotkey
            = MACRO_CALL(Rendering_Func::ViewportBasedTileNumber)();
        goto LAB_004b3a17;
    case 'H':
        /*
          H
         */
        if ((((lParam & 0x40000000U))
                || (BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(), !BVar2))
            || (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_NONE))
            break;
        if (DAT_ModifierKeyState::instance.shift) {
            if (DAT_GameCore::instance.viewportFocusBeforeKeepHotkey != -1) {
                MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                    DAT_ViewportRenderState::ptr)(DAT_GameCore::instance.viewportFocusBeforeKeepHotkey);
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_BUILD_MENU, 0);
                }
                DAT_GameCore::instance.viewportFocusBeforeKeepHotkey = -1;
            }
            break;
        }
        if (DAT_ModifierKeyState::instance.ctrl) {
            iVar4
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].keep.id;
            if (iVar4) {
                MACRO_CALL_MEMBER(
                    UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                    AlphaAndButtonSurfaceObj::ptr)(iVar4);
            }
            break;
        }
        _buildingID
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].keep.id;
        if (!_buildingID)
            break;
        DAT_GameCore::instance.viewportFocusBeforeKeepHotkey
            = MACRO_CALL(Rendering_Func::ViewportBasedTileNumber)();
        goto LAB_004b3a17;
    case 'I':
        /*
          I
         */
        if ((((lParam & 0x40000000U))
                || (BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(), !BVar2))
            || (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_NONE))
            break;
        if (DAT_ModifierKeyState::instance.shift) {
            if (DAT_GameCore::instance.viewportFocusBeforeEngineersGuildHotkey != -1) {
                MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                    DAT_ViewportRenderState::ptr)(DAT_GameCore::instance.viewportFocusBeforeEngineersGuildHotkey);
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_BUILD_MENU, 0);
                }
                DAT_GameCore::instance.viewportFocusBeforeEngineersGuildHotkey = -1;
            }
            break;
        }
        if (DAT_ModifierKeyState::instance.ctrl) {
            iVar4 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .engineersGuild.id;
            if (iVar4) {
                MACRO_CALL_MEMBER(
                    UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                    AlphaAndButtonSurfaceObj::ptr)(iVar4);
            }
            break;
        }
        _buildingID = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .engineersGuild.id;
        if (!_buildingID)
            break;
        DAT_GameCore::instance.viewportFocusBeforeEngineersGuildHotkey
            = MACRO_CALL(Rendering_Func::ViewportBasedTileNumber)();
        goto LAB_004b3a17;
    case 'L':
        /*
          L
         */
        if (((!(lParam & 0x40000000U))
                && (BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(), BVar2))
            && (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE)) {
            if (!DAT_ModifierKeyState::instance.shift) {
                iVar4 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .lordID;
                if (((iVar4) && (DAT_UnitsState::instance.units[iVar4].unitType == Map::Units::UT_LORD))
                    && ((DAT_UnitsState::instance.units[iVar4].owner
                            == DAT_GameSynchronyState::instance.currentPlayerSlotID
                        && (DAT_UnitsState::instance.units[iVar4].logicalState == Map::Units::ULS_NORMAL)))) {
                    MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                        DAT_ViewportRenderState::ptr)(DAT_UnitsState::instance.units[iVar4].tile);
                }
            } else {
                iVar4 = 0;
                do {
                    iVar3 = DAT_ShortcutDefinedData::instance.CyclingLordID;
                    DAT_ShortcutDefinedData::instance.CyclingLordID
                        = DAT_ShortcutDefinedData::instance.CyclingLordID + 1;
                    if (DAT_ShortcutDefinedData::instance.CyclingLordID == 9) {
                        DAT_ShortcutDefinedData::instance.CyclingLordID = 1;
                    }
                    iVar3 = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(iVar3);
                    if (iVar3) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                            DAT_ViewportRenderState::ptr)(DAT_UnitsState::instance.units[iVar3].tile);
                        break;
                    }
                    iVar4 = iVar4 + 1;
                } while (iVar4 < 8);
            }
        }
        break;
    case 'M':
        /*
          M
         */
        if ((((lParam & 0x40000000U))
                || (BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(), !BVar2))
            || (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_NONE))
            break;
        if (DAT_ModifierKeyState::instance.shift) {
            if (DAT_GameCore::instance.viewportFocusBeforeMarketHotkey != -1) {
                MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                    DAT_ViewportRenderState::ptr)(DAT_GameCore::instance.viewportFocusBeforeMarketHotkey);
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_BUILD_MENU, 0);
                }
                DAT_GameCore::instance.viewportFocusBeforeMarketHotkey = -1;
            }
            break;
        }
        if (DAT_ModifierKeyState::instance.ctrl) {
            iVar4 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .marketplace.id;
            if (iVar4) {
                MACRO_CALL_MEMBER(
                    UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                    AlphaAndButtonSurfaceObj::ptr)(iVar4);
            }
            break;
        }
        _buildingID = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .marketplace.id;
        if (!_buildingID)
            break;
        DAT_GameCore::instance.viewportFocusBeforeMarketHotkey
            = MACRO_CALL(Rendering_Func::ViewportBasedTileNumber)();
        goto LAB_004b3b12;
    case 'N':
        /*
          N
         */
        if ((((lParam & 0x40000000U))
                || (BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(), !BVar2))
            || (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_NONE))
            break;
        if (DAT_ModifierKeyState::instance.shift) {
            if (DAT_GameCore::instance.viewportFocusBeforeMercenaryHotkey != -1) {
                MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                    DAT_ViewportRenderState::ptr)(DAT_GameCore::instance.viewportFocusBeforeMercenaryHotkey);
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_BUILD_MENU, 0);
                }
                DAT_GameCore::instance.viewportFocusBeforeMercenaryHotkey = -1;
            }
            break;
        }
        if (DAT_ModifierKeyState::instance.ctrl) {
            iVar4 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .mercenaryPost.id;
            if (iVar4) {
                MACRO_CALL_MEMBER(
                    UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                    AlphaAndButtonSurfaceObj::ptr)(iVar4);
            }
            break;
        }
        _buildingID = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .mercenaryPost.id;
        if (!_buildingID)
            break;
        DAT_GameCore::instance.viewportFocusBeforeMercenaryHotkey
            = MACRO_CALL(Rendering_Func::ViewportBasedTileNumber)();
    LAB_004b3b12:
        /*
          b press
         */
        _buildingY = DAT_BuildingsState::instance.buildings[_buildingID].y;
        _buildingX = DAT_BuildingsState::instance.buildings[_buildingID].x;
    LAB_004b3a35:
        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnCoordinate,
            DAT_ViewportRenderState::ptr)((short)_buildingX + 2, (int)((short)_buildingY + 2));
        MACRO_CALL_MEMBER(UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
            AlphaAndButtonSurfaceObj::ptr)(_buildingID);
        break;
    case 'P':
        /*
          P
         */
        BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if ((((BVar2) && (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE))
                && (DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR))
            && ((DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT
                && (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_MULTIPLAYER)))) {
            DAT_GameCore::instance.gamePausedLogical = DAT_GameCore::instance.gamePausedLogical ^ 1;
            if (!DAT_GameCore::instance.gamePausedLogical) {
                if (DAT_GameCore::instance.genieVoiceActive) {
                    /*
                      "Game running"
                     */
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        "game_running.wav");
                }
            } else {
                MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    UI::Enums::DEID_GAME_PAUSED_TEXT, 1);
                DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_NULL;
                if (DAT_GameCore::instance.genieVoiceActive) {
                    /*
                      "Game paused"
                     */
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        "game_paused.wav");
                }
            }
        }
        break;
    case 'Q':
        /*
          Q
         */
        if (((DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE)
                && (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU))
            && ((DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM
                || (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_SIEGETENT_SHIELD)))) {
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::queueUnitStance, DAT_TribesState::ptr)(
                DAT_TribesState::instance.DAT_CurrentTribeID, 0);
        }
        break;
    case 'S':
        /*
          S
         */
        if (((!(lParam & 0x40000000U))
                && (BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(), BVar2))
            && (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE)) {
            iVar4 = DAT_GameState::instance.mapAndTime.signpostIDs[DAT_00df5538::instance];
            if (iVar4) {
                MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnCoordinate,
                    DAT_ViewportRenderState::ptr)((short)DAT_BuildingsState::instance.buildings[iVar4].x + 1,
                    (int)((short)DAT_BuildingsState::instance.buildings[iVar4].y + 1));
            }
            DAT_00df5538::instance = DAT_00df5538::instance + 1;
            if (7 < DAT_00df5538::instance) {
                DAT_00df5538::instance = 0;
            }
            iVar3 = 1;
            iVar4 = DAT_GameState::instance.mapAndTime.signpostIDs[DAT_00df5538::instance];
            while (!iVar4) {
                DAT_00df5538::instance = DAT_00df5538::instance + 1;
                if (7 < DAT_00df5538::instance) {
                    DAT_00df5538::instance = 0;
                }
                iVar3 = iVar3 + 1;
                if (7 < iVar3)
                    break;
                iVar4 = DAT_GameState::instance.mapAndTime.signpostIDs[DAT_00df5538::instance];
            }
        }
        break;
    case 'T':
        /*
          T
         */
        if ((((lParam & 0x40000000U))
                || (BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(), !BVar2))
            || (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_NONE))
            break;
        if (DAT_ModifierKeyState::instance.shift) {
            if (DAT_GameCore::instance.field161_0x2364 != -1) {
                MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                    DAT_ViewportRenderState::ptr)(DAT_GameCore::instance.field161_0x2364);
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_BUILD_MENU, 0);
                }
                DAT_GameCore::instance.field161_0x2364 = -1;
            }
            break;
        }
        if (DAT_ModifierKeyState::instance.ctrl) {
            iVar4 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .tunnelersGuild.id;
            if (iVar4) {
                MACRO_CALL_MEMBER(
                    UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                    AlphaAndButtonSurfaceObj::ptr)(iVar4);
            }
            break;
        }
        _buildingID = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .tunnelersGuild.id;
        if (!_buildingID)
            break;
        DAT_GameCore::instance.field161_0x2364 = MACRO_CALL(Rendering_Func::ViewportBasedTileNumber)();
    LAB_004b3a17:
        _buildingY = DAT_BuildingsState::instance.buildings[_buildingID].y;
        _buildingX = DAT_BuildingsState::instance.buildings[_buildingID].x;
        goto LAB_004b3a35;
    case 'V':
        /*
          V
         */
        BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if (((BVar2) && (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE))
            && (!DAT_MouseState::instance.rightClickState)) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::triggerLoweredView, DAT_TileMapState::ptr)(3);
            DAT_ModifierKeyState::instance.v = 1;
        }
        break;
    case 'W':
        /*
          W
         */
        if (((DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE)
                && (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU))
            && ((DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM
                || (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_SIEGETENT_SHIELD)))) {
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::queueUnitStance, DAT_TribesState::ptr)(
                DAT_TribesState::instance.DAT_CurrentTribeID, 1);
        }
        break;
    case 'X':
        /*
          X
         */
        BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if (((BVar2) && (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE))
            && (!DAT_MouseState::instance.rightClickState)) {
            uVar10 = DAT_TileMapState::instance.mapOrientation + 2U & 0x80000007;
            if ((int)uVar10 < 0) {
                uVar10 = (uVar10 - 1 | 0xfffffff8) + 1;
            }
            MACRO_CALL_MEMBER(Map::TileMapState_Func::setMapRotation, DAT_TileMapState::ptr)(uVar10);
        }
        break;
    case 'Z':
        /*
          Z
         */
        if (((((lParam & 0x40000000U))
                 || (BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(),
                     !BVar2))
                || (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_NONE))
            || (DAT_MouseState::instance.rightClickState))
            break;
        if (!DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk) {
            MACRO_CALL_MEMBER(
                Rendering::ViewportRenderState_Func::resetupViewport, DAT_ViewportRenderState::ptr)(1);
        } else {
            MACRO_CALL_MEMBER(
                Rendering::ViewportRenderState_Func::resetupViewport, DAT_ViewportRenderState::ptr)(0);
        }
    LAB_004b2cfd:
        DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
        break;
    case VK_NUMPAD0:
    case VK_NUMPAD1:
    case VK_NUMPAD2:
    case VK_NUMPAD3:
    case VK_NUMPAD4:
    case VK_NUMPAD5:
    case VK_NUMPAD6:
    case VK_NUMPAD7:
    case VK_NUMPAD8:
    case VK_NUMPAD9:
        /*
          numpad numbers
         */
        wParam = wParam - '0';
    switchD_004b2d9a_caseD_30:
        /*
          0-9
         */
        if (((!(lParam & 0x40000000U))
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE))
            && (BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(),
                _currentSelectionID = DAT_TribesState::instance.DAT_CurrentTribeID, BVar2)) {
            if (!DAT_ModifierKeyState::instance.ctrl) {
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                    if (DAT_GameCore::instance.activeMenuTab.tabType
                        == UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM) {
                        switch (wParam) {
                        case '1':
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                Commands::M_MAPPER_PLACE_ASSEMBLY_POINT1);
                            break;
                        case '2':
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                Commands::M_MAPPER_PLACE_ASSEMBLY_POINT3);
                            break;
                        case '3':
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                Commands::M_MAPPER_PLACE_ASSEMBLY_POINT4);
                            break;
                        case '4':
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                Commands::M_MAPPER_PLACE_ASSEMBLY_POINT2);
                            break;
                        case '5':
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                Commands::M_MAPPER_PLACE_ASSEMBLY_POINT5);
                            break;
                        case '6':
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                Commands::M_MAPPER_PLACE_ASSEMBLY_POINT6);
                            break;
                        case '7':
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                Commands::M_MAPPER_PLACE_ASSEMBLY_POINT7);
                        }
                        break;
                    }
                    if (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_MERCENARYPOST) {
                        switch (wParam) {
                        case '1':
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM1);
                            break;
                        case '2':
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM3);
                            break;
                        case '3':
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM5);
                            break;
                        case '4':
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM4);
                            break;
                        case '5':
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM2);
                            break;
                        case '6':
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM7);
                            break;
                        case '7':
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM6);
                        }
                        break;
                    }
                    if (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_ENGINEERSGUILD) {
                        if (wParam - '1' < 2) {
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                (Commands::MappersEnum)(wParam + 0x13e));
                        }
                        break;
                    }
                    if (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_TUNNELERSGUILD) {
                        if (wParam == '1') {
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                Commands::M_MAPPER_PLACE_ASSEMBLY_POINTT1);
                        }
                        break;
                    }
                    if (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_CATHEDRAL) {
                        if (wParam == '1') {
                            MACRO_CALL(UI::MenuItems::General_Func::
                                    MenuItemActionHandler_General_ToolbarButtonPressed)(
                                Commands::M_MAPPER_PLACE_ASSEMBLY_POINTK1);
                        }
                        break;
                    }
                }
                iVar4 = wParam - '0';
                BVar2 = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::isUnitShortcutAvailable, DAT_UnitsState::ptr)(iVar4);
                if (!BVar2) {
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                    MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::makeSelectionBasedOnShortcut, DAT_UnitsState::ptr)(iVar4);
                    if (0 < DAT_UnitsState::instance.totalUnitsInSelection) {
                        if (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                            != UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM) {
                            DAT_GameCore::instance.tabTypeSiegeSubset
                                = DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab;
                        }
                        DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                            = UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM;
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            UI::Enums::MVT_BUILD_MENU, 0);
                        DAT_TileMapState::instance.shiftRelated0or3 = 1;
                        DAT_UnitsState::instance.pendingUnitControlMode = TRUE;
                        DAT_UnitsState::instance.unitControlsRelated = 1;
                        DAT_UnitsState::instance.hasEngineerSelected = FALSE;
                        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                    }
                } else {
                    iVar3 = *(int*)((int)DAT_GameState::ptr + iVar4 * 20000);
                    iVar11 = 0;
                    if (iVar3 == -1) {
                        pSVar7 = (int*)((int)DAT_GameState::ptr + iVar4 * 20000);
                        do {
                            iVar11 = iVar11 + 1;
                            pSVar7 = pSVar7 + 2;
                            if (2500 < iVar11)
                                break;
                            iVar3 = *pSVar7;
                        } while (iVar3 == -1);
                    }
                    if (0 < iVar3) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnCoordinate,
                            DAT_ViewportRenderState::ptr)((int)DAT_UnitsState::instance.units[iVar3].x,
                            (int)(DAT_UnitsState::instance.units[iVar3].y));
                    }
                }
            } else if (!DAT_ModifierKeyState::instance.alt) {
                if (((DAT_TribesState::instance.DAT_CurrentTribeID)
                        && (DAT_TileMapState::instance.shiftRelated0or3 == 1))
                    && (DAT_TribesState::instance.DAT_CurrentTribeID)) {
                    MACRO_CALL_MEMBER(Game::GameStateStructures_Func::clearTribeHotKey, DAT_GameState::ptr)(
                        wParam - '0');
                    MACRO_CALL_MEMBER(Game::GameStateStructures_Func::assignSelectionToKey,
                        DAT_GameState::ptr)(wParam - '0', _currentSelectionID);
                }
            } else {
            LAB_004b4af5:
                /*
                  basically we pressed a number on the keypad or above the letters
                 */
                if (!DAT_ModifierKeyState::instance.ctrl) {
                    _tile = DAT_GameState::instance.playerDataArray[8].engineersAssemblyPoints[wParam - 6];
                    if (-1 < *(int*)&_tile) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnTile,
                            DAT_ViewportRenderState::ptr)(*(int*)&_tile);
                    }
                } else {
                    _screenOffset = 8;
                    if (DAT_TileMapState::instance.mapOrientation) {
                        if (DAT_TileMapState::instance.mapOrientation == 6) {
                            _screenOffset = 0x13a18;
                        } else if (DAT_TileMapState::instance.mapOrientation == 4) {
                            _screenOffset = 0x27428;
                        } else if (DAT_TileMapState::instance.mapOrientation == 2) {
                            _screenOffset = 0x3ae38;
                        }
                    }
                    DAT_GameState::instance.playerDataArray[8].engineersAssemblyPoints[wParam - 6]
                        = *(XYPairShort*)(DAT_ViewportRenderState::instance.screenPointToTileNumber
                            + (DAT_ViewportRenderState::instance.viewportState.viewportX / 32)
                            + ((int)DAT_ViewportRenderState::instance.viewportState.mbr_0xb0 / 2
                                  + (DAT_ViewportRenderState::instance.viewportState.viewportY / 16))
                                * 401
                            + DAT_ViewportRenderState::instance.viewportState.mbr_0xac + _screenOffset + -8);
                }
            }
        }
        break;
    case VK_ADD:
        /*
          VK_ADD
         */
        if ((((lParam & 0x40000000U))
                || (_addKeyIngameMenu
                    = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(),
                    !_addKeyIngameMenu))
            || (((DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_NONE
                     || ((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                         && (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER))))
                || (90 < DAT_GameCore::instance.gameSpeedLevel))))
            break;
        DAT_GameCore::instance.gameSpeedLevel = DAT_GameCore::instance.gameSpeedLevel + 5;
        if (0x5a < DAT_GameCore::instance.gameSpeedLevel) {
            DAT_GameCore::instance.gameSpeedLevel = 0x5a;
        }
        goto LAB_004b4768;
    case VK_SUBTRACT:
        /*
          VK_SUBTRACT
         */
        if ((((lParam & 0x40000000U))
                || (_subtractKeyIngameMenu
                    = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(),
                    !_subtractKeyIngameMenu))
            || ((DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_NONE
                || (((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                         && (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER))
                    || (DAT_GameCore::instance.gameSpeedLevel < 0xb))))))
            break;
        DAT_GameCore::instance.gameSpeedLevel = DAT_GameCore::instance.gameSpeedLevel - 5;
        if (DAT_GameCore::instance.gameSpeedLevel < 0x14) {
            DAT_GameCore::instance.gameSpeedLevel = 0x14;
        }
    LAB_004b4768:
        MACRO_CALL(UI::DisplayElements_Func::ActivateGameSpeedAndResourceLackDisplayElementUnk)(
            UI::Enums::DEID_GAME_SPEED_TEXT, 1, 5000);
        break;
    case VK_F1:
        /*
          VK_F1
         */
        if (DAT_ModifierKeyState::instance.shift) {
            if (((((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                      || (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .playerDeathRelated
                          == 0))
                     && (DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR))
                    && (((((DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT
                               && (DAT_MenuTextInputState::instance.currentModalDialog == UI::Enums::MMT_NO_MENU))
                              && ((DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU
                                  || (DAT_GameCore::instance.currentMenuViewType
                                      == UI::Enums::MVT_BUILDING_AND_STATUS_MENU))))
                             && ((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                                 || (DAT_GameSynchronyState::instance.isHost))))
                        && (!DAT_GameCore::instance.field24_0x6c))))
                && (DAT_GameCore::instance.gameMode_2 != Game::GM_CRUSADER_TUTORIAL)) {
                MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::loadOrSaveGame, DAT_MenuTextInputState::ptr)(
                    10);
            }
            break;
        }
    case VK_F3:
    case VK_F4:
    case VK_F5:
    case VK_F6:
    case VK_F7:
    case VK_F8:
    case VK_F9:
    case VK_F10:
    switchD_004b482b_caseD_79:
        /*
          F1-F10 without F2
         */
        DAT_ModifierKeyState::instance.keyDownUnk = 1;
        if ((DAT_GameCore::instance.gameMode_2 == Game::GM_SKIRMISH_AND_MULTIPLAYER)
            && (_tauntInGameMenuCheck
                = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(),
                _tauntInGameMenuCheck != 0)) {
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
            if (DAT_ModifierKeyState::instance.ctrl) {
                wParam = wParam + (VK_BACK | VK_RBUTTON);
            }
            DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = wParam - VK_DIVIDE;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                Commands::GCT_TAUNT_OR_CHAT);
            if ((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER)
                && (DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage != 6)) {
                MACRO_CALL_MEMBER(AI::AICState_Func::setTriggerForAITauntResponse, DAT_AICState::ptr)();
            }
        } else if (((wParam < VK_F2)
                       && (((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk
                                && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_JUST_BUILD))
                           && (_fkeyIngameMenuCheck
                               = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(),
                               _fkeyIngameMenuCheck))))
            && (!DAT_ModifierKeyState::instance.shift)) {
            MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::openEventTriggerMenu, DAT_MapPropertiesState::ptr)(
                wParam - VK_F1);
            break;
        }
    switchD_004b482b_caseD_7a:
        /*
          F11 or F12
         */
        wParam = VK_SPACE;
        break;
    case VK_F2:
        /*
          VK_F2
         */
        if (DAT_ModifierKeyState::instance.shift) {
            if ((((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                     || (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                             .playerDeathRelated
                         == 0))
                    && ((DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR
                        && ((DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT
                            && (DAT_MenuTextInputState::instance.currentModalDialog
                                == UI::Enums::MMT_NO_MENU))))))
                && ((DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU
                    || (DAT_GameCore::instance.currentMenuViewType
                        == UI::Enums::MVT_BUILDING_AND_STATUS_MENU)))) {
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    if ((!DAT_GameCore::instance.field24_0x6c)
                        && (DAT_GameCore::instance.gameMode_2 != Game::GM_CRUSADER_TUTORIAL)) {
                        MACRO_CALL_MEMBER(
                            UI::MenuTextInputState_Func::loadOrSaveGame, DAT_MenuTextInputState::ptr)(9);
                    }
                } else if (DAT_GameSynchronyState::instance.currentGameMode
                    == Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    MACRO_CALL_MEMBER(
                        UI::MenuTextInputState_Func::loadOrSaveGame, DAT_MenuTextInputState::ptr)(9);
                }
            }
            break;
        }
        goto switchD_004b482b_caseD_79;
    }
switchD_004b4d0c_doDefWindowProcA:
    LVar1 = DefWindowProcA(_hwnd, message, wParam, lParam);
    ;
    return LVar1;
}

}
