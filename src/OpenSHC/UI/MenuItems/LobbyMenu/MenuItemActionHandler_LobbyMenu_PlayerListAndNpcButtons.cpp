#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/Actions.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-literals.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x00440E50
        void LobbyMenu::MenuItemActionHandler_LobbyMenu_PlayerListAndNpcButtons(int buttonID, ...)
        {
            if (DAT_00b960dc::instance != 0
                || DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_ROUNDTABLE
                || buttonID >= 0) {
                return;
            }
            // -1 to -9: the rows of the player list; a click on one's own row toggles it
            if (buttonID > -10) {
                if (DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[-buttonID]
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID
                    && DAT_GameSynchronyState::instance.flag_0x7aad8
                    && DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    DAT_GameSynchronyState::instance
                        .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.currentPlayerSlotID] ^= 1;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS);
                }
                return;
            }
            if (buttonID == -101) {
                if (!DAT_GameSynchronyState::instance.isHost) {
                    return;
                }
                MACRO_CALL(OpenSHC::UI::Helpers_Func::ClearLobbyHoveredAI)();
                if (DAT_GameCore::instance.numOfAIsWithCastleUnk <= 8) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 4,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 205);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 4,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 205);
                }
                if (DAT_GameCore::instance.genieVoiceActive) {
                    // "Choose your adversary"
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        SFX_ChooseYourAdversary);
                }
                return;
            }
            if (buttonID == -102) {
                if (!DAT_GameSynchronyState::instance.isHost) {
                    return;
                }
                if (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                    if (DAT_MenuModalComposition1::instance.activeModalDialogID
                            != OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT
                        && DAT_MenuModalComposition1::instance.activeModalDialogID
                            != OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT) {
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                }
                MACRO_CALL(OpenSHC::Synchrony_Func::SyncPlayerGroupArrays)();
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ROUNDTABLE, FALSE);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                    DAT_GameSynchronyState::ptr)();
                if (DAT_GameCore::instance.genieVoiceActive) {
                    // "The round table"
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        SFX_TheRoundTable);
                }
                return;
            }
            if (buttonID == -103) {
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    return;
                }
                if (!DAT_GameSynchronyState::instance.isHost) {
                    return;
                }
                if (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_UNKNOWN_0xFC);
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_CHOOSE_RANDOM_NUMBER_OF_ENEMIES, FALSE);
                DAT_MenuHandlerState::instance.currentMenu->hoveredItem = NULL;
                DAT_BottomLeftTextDisplayState::instance.currentlyDisplayedTextIsDisplayedUnk = 0;
                return;
            }
            // -201 down: the buttons beside each slot of the round table
            if (!DAT_GameSynchronyState::instance.isHost) {
                return;
            }
            // -201 is the round table's first row. The slot is read as a char (an int tested with `< 1` loses
            // the byte test, and the match).
            char const slot = DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[-buttonID - 200];
            if (slot <= 0) {
                return;
            }
            int const playerID = slot;
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                return;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1) {
                if (!DAT_GameSynchronyState::instance.slotActionPending[playerID]) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = playerID;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_UNKNOWN_85);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::scheduleSFXVariation, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_UNKNOWN_0x60, 2);
                    DAT_GameSynchronyState::instance.slotActionPending[playerID] = 1;
                }
                return;
            }
            if (DAT_GameSynchronyState::instance.currentAIArray[playerID] == OpenSHC::AI::AITA_NULL) {
                return;
            }
            // message 21: the lord's line when he is taken out of the lobby (22 is the one when he joins)
            MACRO_CALL(OpenSHC::UI::Helpers_Func::PlayAMessageFromAI)(
                DAT_GameSynchronyState::instance.currentAIArray[playerID], 21);
            DAT_GameSynchronyState::instance.currentAIArray[playerID] = 0;
            MACRO_CALL(OpenSHC::Synchrony::Actions_Func::RemovePositionOfPlayer)(playerID);
            MACRO_CALL_MEMBER(
                OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions, DAT_GameSynchronyState::ptr)();
            DAT_GameSynchronyState::instance.reparseMaps = TRUE;
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = playerID;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_HOST_REMOVE_PLAYER_BY_SLOT);
            }
        }

    }
}
}
