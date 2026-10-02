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
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b95960.hpp"
#include "OpenSHC/Globals/DAT_00b95b74.hpp"
#include "OpenSHC/Globals/DAT_00b95f64.hpp"
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
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Rendering::Enums::RenderTarget;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00442640
        void LobbyMenu::MenuItemActionHandler_LobbyMenu_LobbyscreenStartButtonClick(int param_1, ...)
        {
            char cVar1;
            int* piVar2;
            int iVar3;
            int _f1;
            int iVar4;
            int _f0;
            if (DAT_00b960dc::instance != 0) {}
            if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU) {}
            if (0x69 < param_1) {
                if (param_1 != 0x19d) {}
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    (OpenSHC::Audio::SFX::SoundEffectID)(OpenSHC::Audio::SFX::SEID_UNIT_DAMAGE3
                        | OpenSHC::Audio::SFX::SEID_ARROW_SHOOT));
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_RANKING_GAMES, 0);
            }
            if (param_1 == 0x69) {
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                    = DAT_MenuTextInputState::instance
                          .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                              + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + -1];
                MACRO_CALL_MEMBER(
                    OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (OpenSHC::Commands::GameCommandType)(OpenSHC::Commands::GCT_SHARE_GAME_STATE_PARTIAL_HASHES
                        | OpenSHC::Commands::GCT_MULTIPLAYER_ANNOUNCE_HOST));
            }
            switch (param_1) {
            case 1:
                /*
                  click load game
                 */
                if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                    piVar2 = DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue + 1;
                    do {
                        if ((piVar2[-0x419c2] != -1) && (*piVar2 == 0))
                            break;
                        piVar2 = piVar2 + 1;
                    } while ((int)piVar2 < 0x1a2453c);
                    iVar3 = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::checkPlayerSetValid,
                        DAT_GameSynchronyState::ptr)();
                    if (1 < iVar3) {
                        DAT_MenuTextInputState::instance.field42_0x9c = 1;
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::MenuTextInputState_Func::loadOrSaveGame, DAT_MenuTextInputState::ptr)(9);
                        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    }
                }
                break;
            case 2:
                /*
                  leave screen
                 */
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
                    if (((DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_ROUNDTABLE)
                            || (DAT_MenuModalComposition1::instance.activeModalDialogID
                                == OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT))
                        || (DAT_MenuModalComposition1::instance.activeModalDialogID
                            == OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT)) {
                        DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
                    }
                } else {
                    DAT_GameSynchronyState::instance.currentGameMode = OpenSHC::Game::GM_MULTIPLAYER_END_OF_GAME;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
                    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 7;
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk)(0x16);
                    if (((DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_ROUNDTABLE)
                            || (DAT_MenuModalComposition1::instance.activeModalDialogID
                                == OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT))
                        || (DAT_MenuModalComposition1::instance.activeModalDialogID
                            == OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT)) {
                        DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                            DAT_GameSynchronyState::ptr)();
                    }
                }
                break;
            case 4:
                /*
                  start game
                 */
                if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                    piVar2 = DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue + 1;
                    do {
                        if ((piVar2[-0x419c2] != -1) && (*piVar2 == 0))
                            break;
                        piVar2 = piVar2 + 1;
                    } while ((int)piVar2 < 0x1a2453c);
                    iVar3 = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::checkPlayerSetValid,
                        DAT_GameSynchronyState::ptr)();
                    if (((1 < iVar3)
                            && (-1 < DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                                    + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset))
                        && (0 < DAT_GameSynchronyState::instance
                                .unknownMapRelatedReceivedDataArray[DAT_MenuTextInputState::instance
                                        .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance
                                                                   .DAT_MapSelectionRelativeSelected
                                            + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + -1]])) {
                        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::setTimeBasedSeed, SEC_RNG::ptr)();
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                            OpenSHC::Commands::GCT_TRIGGER_LOBBY_PLAYER_INFORMATION_REFRESH);
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
                        if (DAT_GameSynchronyState::instance.currentGameMode
                            == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                            DAT_GameCore::instance.isSkirmishTrail = FALSE;
                            MACRO_CALL(OpenSHC::UI::Actions_Func::LaunchSkirmishGame)(0);
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                        }
                        /*
                          start game by sending seed?   Here: DAT_CurrentGameMode is MULTIPLAYER
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_START_MULTIPLAYER_GAME);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                }
                break;
            case -0xc9:
                if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                    if (-1 < DAT_00b95960::instance) {
                        iVar3 = 0;
                        while (((iVar4 = DAT_GameCore::instance.keepPositions[iVar3].x,
                                    iVar4 < 0
                                        || (DAT_MouseState::instance.screenSpaceX
                                            < iVar4 + 0x23c + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth))
                            || ((iVar4 + 0x253 + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                                    < DAT_MouseState::instance.screenSpaceX
                                || ((iVar4 = DAT_GameCore::instance.keepPositions[iVar3].y
                                        + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight,
                                    DAT_MouseState::instance.screenSpaceY < iVar4 + 3
                                        || (iVar4 + 0x23 < DAT_MouseState::instance.screenSpaceY))))))) {
                            iVar3 = iVar3 + 1;
                            if (7 < iVar3) {
                                DAT_00b95960::instance = 0xffffffff;
                            }
                        }
                        cVar1 = DAT_GameSynchronyState::instance.playerPositionsArray[DAT_00b95f64::instance];
                        DAT_GameSynchronyState::instance.playerPositionsArray[DAT_00b95f64::instance]
                            = DAT_GameSynchronyState::instance.playerPositionsArray[iVar3];
                        DAT_GameSynchronyState::instance.playerPositionsArray[iVar3] = cVar1;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS);
                    }
                    DAT_00b95960::instance = 0xffffffff;
                }
                break;
            case -200:
                if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                    iVar3 = 0;
                    while ((((_f0 = DAT_GameCore::instance.keepPositions[iVar3].x,
                                 _f0 < 0
                                     || (DAT_MouseState::instance.screenSpaceX
                                         < _f0 + 0x23c + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth))
                                || (_f0 + 0x253 + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                                    < DAT_MouseState::instance.screenSpaceX))
                        || ((_f1 = DAT_GameCore::instance.keepPositions[iVar3].y
                                + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight,
                            DAT_MouseState::instance.screenSpaceY < _f1 + 3
                                || (_f1 + 0x23 < DAT_MouseState::instance.screenSpaceY))))) {
                        iVar3 = iVar3 + 1;
                        if (7 < iVar3) {}
                    }
                    DAT_00b95960::instance = (int)DAT_GameSynchronyState::instance.playerPositionsArray[iVar3];
                    DAT_00b95f64::instance = iVar3;
                }
                break;
            case -199:
            case -0xc6:
            case -0xc5:
            case -0xc4:
            case -0xc3:
            case -0xc2:
            case -0xc1:
            case -0xc0:
            case -0xbf:
            case -0xbe:
            case -0xbd:
            case -0xbc:
            case -0xbb:
            case -0xba:
            case -0xb9:
            case -0xb8:
            case -0xb7:
            case -0xb6:
            case -0xb5:
            case -0xb4:
            case -0xb3:
            case -0xb2:
            case -0xb1:
            case -0xb0:
            case -0xaf:
            case -0xae:
            case -0xad:
            case -0xac:
            case -0xab:
            case -0xaa:
            case -0xa9:
            case -0xa8:
            case -0xa7:
            case -0xa6:
            case -0xa5:
            case -0xa4:
            case -0xa3:
            case -0xa2:
            case -0xa1:
            case -0xa0:
            case -0x9f:
            case -0x9e:
            case -0x9d:
            case -0x9c:
            case -0x9b:
            case -0x9a:
            case -0x99:
            case -0x98:
            case -0x97:
            case -0x96:
            case -0x95:
            case -0x94:
            case -0x93:
            case -0x92:
            case -0x91:
            case -0x90:
            case -0x8f:
            case -0x8e:
            case -0x8d:
            case -0x8c:
            case -0x8b:
            case -0x8a:
            case -0x89:
            case -0x88:
            case -0x87:
            case -0x86:
            case -0x85:
            case -0x84:
            case -0x83:
            case -0x82:
            case -0x81:
            case -0x80:
            case -0x7f:
            case -0x7e:
            case -0x7d:
            case -0x7c:
            case -0x7b:
            case -0x7a:
            case -0x79:
            case -0x78:
            case -0x77:
            case -0x76:
            case -0x75:
            case -0x74:
            case -0x73:
            case -0x72:
            case -0x71:
            case -0x70:
            case -0x6f:
            case -0x6e:
            case -0x6d:
            case -0x6c:
            case -0x6b:
            case -0x6a:
            case -0x69:
            case -0x68:
            case -0x67:
            case -0x66:
            case -99:
            case -0x62:
            case -0x61:
            case -0x60:
            case -0x5f:
            case -0x5e:
            case -0x5d:
            case -0x5c:
            case -0x5b:
            case -0x5a:
            case -0x59:
            case -0x58:
            case -0x57:
            case -0x56:
            case -0x55:
            case -0x54:
            case -0x53:
            case -0x52:
            case -0x51:
            case -0x50:
            case -0x4f:
            case -0x4e:
            case -0x4d:
            case -0x4c:
            case -0x4b:
            case -0x4a:
            case -0x49:
            case -0x48:
            case -0x47:
            case -0x46:
            case -0x45:
            case -0x44:
            case -0x43:
            case -0x42:
            case -0x41:
            case -0x40:
            case -0x3f:
            case -0x3e:
            case -0x3d:
            case -0x3c:
            case -0x3b:
            case -0x3a:
            case -0x39:
            case -0x38:
            case -0x37:
            case -0x36:
            case -0x35:
            case -0x34:
            case -0x33:
            case -0x32:
            case -0x31:
            case -0x30:
            case -0x2f:
            case -0x2e:
            case -0x2d:
            case -0x2c:
            case -0x2b:
            case -0x2a:
            case -0x29:
            case -0x28:
            case -0x27:
            case -0x26:
            case -0x25:
            case -0x24:
            case -0x23:
            case -0x22:
            case -0x21:
            case -0x20:
            case -0x1f:
            case -0x1e:
            case -0x1d:
            case -0x1c:
            case -0x1b:
            case -0x1a:
            case -0x19:
            case -0x18:
            case -0x17:
            case -0x16:
            case -0x15:
            case -0x13:
            case -0x12:
            case -0x11:
            case -0x10:
            case -0xf:
            case -0xe:
            case -0xd:
            case -0xc:
            case -9:
            case -8:
            case -7:
            case -6:
            case -5:
            case -4:
            case -3:
            case 0:
                break;
            case -0x65:
                iVar3 = DAT_00b95b74::instance + -0x72;
                if ((DAT_00b960f4::instance < iVar3)
                    && (DAT_00b960f4::instance = DAT_00b960f4::instance + 0xe, iVar3 < DAT_00b960f4::instance)) {
                    DAT_00b960f4::instance = iVar3;
                }
                break;
            case -100:
                DAT_00b960f4::instance = DAT_00b960f4::instance + -0xe;
                if (DAT_00b960f4::instance < -0x13) {
                    DAT_00b960f4::instance = 0xffffffed;
                }
                break;
            case -0x14:
            case 3:
                /*
                  click ready button?
                 */
                if ((DAT_GameSynchronyState::instance.flag_0x7aad8 != FALSE)
                    && (DAT_GameSynchronyState::instance.DAT_TwoIfNotHost == 2)) {
                    DAT_GameSynchronyState::instance
                        .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        = DAT_GameSynchronyState::instance
                              .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        ^ 1;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS);
                }
                if ((DAT_GameSynchronyState::instance.isHost != FALSE)
                    && (DAT_GameSynchronyState::instance
                            .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        != 0)) {
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
                }
                break;
            case -0xb:
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber + -8) {
                    DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + 1;
                LAB_0044291e:
                    if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_CHANGE_MAP_SELECTION);
                    }
                }
                break;
            case -10:
                if (0 < DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset) {
                    DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + -1;
                    goto LAB_0044291e;
                }
                break;
            case -2:
                if (0 < DAT_GameSynchronyState::instance.field237_0x1072f0) {
                    DAT_GameSynchronyState::instance.field237_0x1072f0
                        = DAT_GameSynchronyState::instance.field237_0x1072f0 + -1;
                }
                break;
            case -1:
                if (DAT_GameSynchronyState::instance.field237_0x1072f0 < 0xf) {
                    DAT_GameSynchronyState::instance.field237_0x1072f0
                        = DAT_GameSynchronyState::instance.field237_0x1072f0 + 1;
                }
                break;
            default:
                break;
            }
        }

    }
}
}
