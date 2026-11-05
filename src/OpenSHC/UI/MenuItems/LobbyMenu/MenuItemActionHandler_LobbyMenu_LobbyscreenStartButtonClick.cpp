#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Actions.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00b95960.hpp"
#include "OpenSHC/Globals/INT_00b95b74.hpp"
#include "OpenSHC/Globals/INT_00b95f64.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00442640
        void LobbyMenu::MenuItemActionHandler_LobbyMenu_LobbyscreenStartButtonClick(int action, ...)
        {
            if (DAT_00b960dc::instance != 0) {
                return;
            }
            if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU) {
                return;
            }
            switch (action) {
            case -1:
                // chat scroll up
                if (DAT_GameSynchronyState::instance.chatScrollOffset < 15) {
                    ++DAT_GameSynchronyState::instance.chatScrollOffset;
                }
                break;
            case -2:
                // chat scroll down
                if (DAT_GameSynchronyState::instance.chatScrollOffset > 0) {
                    --DAT_GameSynchronyState::instance.chatScrollOffset;
                }
                break;
            case 1:
                // load game: only when every occupied slot is ready
                if (!DAT_GameSynchronyState::instance.isHost) {
                    break;
                }
                for (int player = 1; player < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray);
                    ++player) {
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] != -1
                        && DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[player] == 0) {
                        return;
                    }
                }
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::checkPlayerSetValid, DAT_GameSynchronyState::ptr)()
                    >= 2) {
                    DAT_MenuTextInputState::instance.field_0x9c = 1;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::MenuTextInputState_Func::loadOrSaveGame, DAT_MenuTextInputState::ptr)(9);
                    DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                }
                break;
            case 2:
                // leave the lobby
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
                    if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_ROUNDTABLE
                        || DAT_MenuModalComposition1::instance.activeModalDialogID
                            == OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT
                        || DAT_MenuModalComposition1::instance.activeModalDialogID
                            == OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT) {
                        DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
                    }
                } else {
                    DAT_GameSynchronyState::instance.currentGameMode = OpenSHC::Game::GM_MULTIPLAYER_END_OF_GAME;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
                    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 7;
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk)(22);
                    if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_ROUNDTABLE
                        || DAT_MenuModalComposition1::instance.activeModalDialogID
                            == OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT
                        || DAT_MenuModalComposition1::instance.activeModalDialogID
                            == OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT) {
                        DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                            DAT_GameSynchronyState::ptr)();
                    }
                }
                break;
            case -20:
            case 3:
                // ready button
                if (DAT_GameSynchronyState::instance.flag_0x7aad8
                    && DAT_GameSynchronyState::instance.DAT_TwoIfNotHost == 2) {
                    DAT_GameSynchronyState::instance
                        .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.currentPlayerSlotID] ^= 1;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS);
                }
                if (DAT_GameSynchronyState::instance.isHost
                    && DAT_GameSynchronyState::instance
                            .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
                }
                break;
            case 4:
                // start the game: only when every occupied slot is ready
                if (!DAT_GameSynchronyState::instance.isHost) {
                    break;
                }
                for (int player = 1; player < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray);
                    ++player) {
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] != -1
                        && DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[player] == 0) {
                        return;
                    }
                }
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::checkPlayerSetValid, DAT_GameSynchronyState::ptr)()
                        >= 2
                    && DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                            + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        >= 0
                    && DAT_GameSynchronyState::instance
                            .unknownMapRelatedReceivedDataArray[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices
                                    [DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                                        + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset]]
                        > 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::setTimeBasedSeed, SEC_RNG::ptr)();
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_TRIGGER_LOBBY_PLAYER_INFORMATION_REFRESH);
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
                    if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                        DAT_GameCore::instance.isSkirmishTrail = FALSE;
                        MACRO_CALL(OpenSHC::UI::Actions_Func::LaunchSkirmishGame)(0);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_START_MULTIPLAYER_GAME);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                break;
            case -10:
                // map list scroll up
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset > 0) {
                    --DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                    if (DAT_GameSynchronyState::instance.isHost) {
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_CHANGE_MAP_SELECTION);
                    }
                }
                break;
            case -11:
                // map list scroll down
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 8) {
                    ++DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                    if (DAT_GameSynchronyState::instance.isHost) {
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_CHANGE_MAP_SELECTION);
                    }
                }
                break;
            case -100:
                // map description scroll up
                DAT_00b960f4::instance -= 14;
                if (DAT_00b960f4::instance < -19) {
                    DAT_00b960f4::instance = -19;
                }
                break;
            case -101: {
                // map description scroll down
                int const limit = INT_00b95b74::instance - 114;
                if (DAT_00b960f4::instance < limit) {
                    DAT_00b960f4::instance += 14;
                    if (DAT_00b960f4::instance > limit) {
                        DAT_00b960f4::instance = limit;
                    }
                }
                break;
            }
            case -200:
                // pick up the keep position under the mouse
                if (!DAT_GameSynchronyState::instance.isHost) {
                    break;
                }
                for (int position = 0; position < countof(DAT_GameCore::instance.keepPositions); ++position) {
                    int const x = DAT_GameCore::instance.keepPositions[position].x;
                    if (x < 0
                        || DAT_MouseState::instance.screenSpaceX
                            < x + 572 + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                        || DAT_MouseState::instance.screenSpaceX
                            > x + 595 + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth) {
                        continue;
                    }
                    int const y = DAT_GameCore::instance.keepPositions[position].y
                        + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                    if (DAT_MouseState::instance.screenSpaceY < y + 3
                        || DAT_MouseState::instance.screenSpaceY > y + 35) {
                        continue;
                    }
                    INT_00b95960::instance = DAT_GameSynchronyState::instance.playerPositionsArray[position];
                    INT_00b95f64::instance = position;
                    return;
                }
                break;
            case -201:
                // drop it on the keep position under the mouse: swap the two players' positions
                if (!DAT_GameSynchronyState::instance.isHost) {
                    break;
                }
                if (INT_00b95960::instance >= 0) {
                    for (int position = 0; position < countof(DAT_GameCore::instance.keepPositions); ++position) {
                        int const x = DAT_GameCore::instance.keepPositions[position].x;
                        if (x < 0
                            || DAT_MouseState::instance.screenSpaceX
                                < x + 572 + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                            || DAT_MouseState::instance.screenSpaceX
                                > x + 595 + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth) {
                            continue;
                        }
                        int const y = DAT_GameCore::instance.keepPositions[position].y
                            + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                        if (DAT_MouseState::instance.screenSpaceY < y + 3
                            || DAT_MouseState::instance.screenSpaceY > y + 35) {
                            continue;
                        }
                        int const dragged
                            = DAT_GameSynchronyState::instance.playerPositionsArray[INT_00b95f64::instance];
                        DAT_GameSynchronyState::instance.playerPositionsArray[INT_00b95f64::instance]
                            = DAT_GameSynchronyState::instance.playerPositionsArray[position];
                        DAT_GameSynchronyState::instance.playerPositionsArray[position] = dragged;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS);
                        break;
                    }
                }
                INT_00b95960::instance = -1;
                break;
            case 105:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                    = DAT_MenuTextInputState::instance
                          .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                              + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset];
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_UNKNOWN_103);
                break;
            case 413:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_UNKNOWN_0xFD);
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_RANKING_GAMES, 0);
                break;
            }
        }

    }
}
}
