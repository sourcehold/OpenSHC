#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/Actions.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Game::GameMode;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00440E50
        void LobbyMenu::MenuItemActionHandler_LobbyMenu_PlayerListAndNpcButtons(int param_1, ...)
        {
            char cVar1;
            int playerID;
            MenuModalType menuModalID;
            if (((DAT_00b960dc::instance == 0)
                    && (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_ROUNDTABLE))
                && (param_1 < 0)) {
                if (param_1 < -9) {
                    if (param_1 == -0x65) {
                        if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                            MACRO_CALL(OpenSHC::UI::Helpers_Func::ClearLobbyHoveredAI)();
                            if (DAT_GameCore::instance.numOfAIsWithCastleUnk < 9) {
                                menuModalID = OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT;
                            } else {
                                menuModalID = OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition1::ptr)(menuModalID,
                                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 4,
                                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xcd);
                            if (DAT_GameCore::instance.genieVoiceActive != FALSE) {
                                /*
                                  "Choose your adversary"
                                 */
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    "Genie_03.wav");
                            }
                        }
                    } else if (param_1 == -0x66) {
                        if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                            if (DAT_MenuModalComposition1::instance.activeModalDialogID
                                != OpenSHC::UI::Enums::MMT_NONE) {
                                if ((DAT_MenuModalComposition1::instance.activeModalDialogID
                                        != OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT)
                                    && (DAT_MenuModalComposition1::instance.activeModalDialogID
                                        != OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT)) {}
                                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                            }
                            MACRO_CALL(OpenSHC::Synchrony_Func::syncPlayerGroupArrays)();
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ROUNDTABLE, FALSE);
                            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                                DAT_GameSynchronyState::ptr)();
                            if (DAT_GameCore::instance.genieVoiceActive != FALSE) {
                                /*
                                  "The round table"
                                 */
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    "Genie_01.wav");
                            }
                        }
                    } else if (param_1 == -0x67) {
                        if (((DAT_GameSynchronyState::instance.currentGameMode
                                 == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)
                                && (DAT_GameSynchronyState::instance.isHost != FALSE))
                            && (DAT_MenuModalComposition1::instance.activeModalDialogID
                                == OpenSHC::UI::Enums::MMT_NONE)) {
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                                (OpenSHC::Audio::SFX::SoundEffectID)(OpenSHC::Audio::SFX::SEID_UNIT_DAMAGE3
                                    | OpenSHC::Audio::SFX::SEID_STOCKS));
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition1::ptr)(
                                OpenSHC::UI::Enums::MMT_CHOOSE_RANDOM_NUMBER_OF_ENEMIES, FALSE);
                            (DAT_MenuHandlerState::instance.currentMenu)->hoveredItem = (MenuItem*)0x0;
                            DAT_BottomLeftTextDisplayState::instance.currentlyDisplayedTextIsDisplayedUnk = 0;
                        }
                    } else if (((DAT_GameSynchronyState::instance.isHost != FALSE)
                                   && (cVar1 = *(char*)((int)DAT_GameSynchronyState::ptr + (0x109d7c - param_1)),
                                       '\0' < cVar1))
                        && (playerID = (int)cVar1, playerID != DAT_GameSynchronyState::instance.currentPlayerSlotID)) {
                        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1) {
                            if (DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
                                MACRO_CALL(OpenSHC::UI::Helpers_Func::PlayAMessageFromAI)(
                                    DAT_GameSynchronyState::instance.currentAIArray[playerID], 0x15);
                                DAT_GameSynchronyState::instance.currentAIArray[playerID] = 0;
                                MACRO_CALL(OpenSHC::Synchrony::Actions_Func::RemovePositionOfPlayer)(playerID);
                                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                                    DAT_GameSynchronyState::ptr)();
                                DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                                if (DAT_GameSynchronyState::instance.currentGameMode
                                    != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = playerID;
                                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_HOST_REMOVE_PLAYER_BY_SLOT);
                                }
                            }
                        } else if (DAT_GameSynchronyState::instance.field294_0x109e5f[playerID] == 0) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = playerID;
                            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(((GameCommandType)0x55));
                            MACRO_CALL_MEMBER(
                                OpenSHC::Audio::SFX::SFXState_Func::scheduleSFXVariation, DAT_SFXState::ptr)(0x60, 2);
                            DAT_GameSynchronyState::instance.field294_0x109e5f[playerID] = 1;
                        }
                    }
                } else if (((*(char*)((int)DAT_GameSynchronyState::ptr + (0x109e44 - param_1))
                                == DAT_GameSynchronyState::instance.currentPlayerSlotID)
                               && (DAT_GameSynchronyState::instance.flag_0x7aad8 != FALSE))
                    && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                    DAT_GameSynchronyState::instance
                        .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        = DAT_GameSynchronyState::instance
                              .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        ^ 1;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS);
                }
            }
        }

    }
}
}
