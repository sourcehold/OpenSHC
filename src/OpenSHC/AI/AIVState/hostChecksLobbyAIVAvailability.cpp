#include "../AIVState.func.hpp"

#include "OpenSHC/Synchrony/Actions.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace AI {

    // lists the AIs with an AIV that every player has, and removes other AIs from the lobby
    // FUNCTION: STRONGHOLDCRUSADER 0x004ECBC0
    void AIVState::hostChecksLobbyAIVAvailability()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
            && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER) {
            if (!DAT_GameSynchronyState::instance.isHost) {
                return;
            }
            int const localPlayer = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            DAT_GameCore::instance.numOfAIsWithCastleUnk = 0;
            for (int aiIndex = 0; aiIndex < 16; ++aiIndex) {
                bool available = true;
                for (int player = 1; player < 9; ++player) {
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] == -1) {
                        continue;
                    }
                    int count;
                    if (DAT_GameSynchronyState::instance.DAT_ReceivedAIVFileAvailabilityPerAIArray[player][0] == -1) {
                        // nothing received yet
                        if (player != localPlayer) {
                            continue;
                        }
                        count = this->aivFileAvailabilityPerAIArray[aiIndex];
                    } else if (player == localPlayer) {
                        count = this->aivFileAvailabilityPerAIArray[aiIndex];
                    } else {
                        count = DAT_GameSynchronyState::instance
                                    .DAT_ReceivedAIVFileAvailabilityPerAIArray[player][aiIndex];
                    }
                    if (count == 0) {
                        available = false;
                        break;
                    }
                }
                if (available) {
                    DAT_GameCore::instance.arrayOfLordIdsWithAIVsUnk[DAT_GameCore::instance.numOfAIsWithCastleUnk]
                        = aiIndex + 1;
                    ++DAT_GameCore::instance.numOfAIsWithCastleUnk;
                }
            }

            BOOLEnum removedPlayer = FALSE;
            for (int player = 1; player < 9; ++player) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] != -1
                    || DAT_GameSynchronyState::instance.currentAIArray[player] == 0) {
                    continue;
                }
                bool hasAIV = false;
                for (int i = 0; i < DAT_GameCore::instance.numOfAIsWithCastleUnk; ++i) {
                    if (DAT_GameSynchronyState::instance.currentAIArray[player]
                        == DAT_GameCore::instance.arrayOfLordIdsWithAIVsUnk[i]) {
                        hasAIV = true;
                        break;
                    }
                }
                if (hasAIV) {
                    continue;
                }
                DAT_GameSynchronyState::instance.currentAIArray[player] = 0;
                MACRO_CALL(Synchrony::Actions_Func::RemovePositionOfPlayer)(player);
                removedPlayer = TRUE;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = player;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_HOST_REMOVE_PLAYER_BY_SLOT);
            }
            if (removedPlayer) {
                MACRO_CALL_MEMBER(
                    Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions, DAT_GameSynchronyState::ptr)();
                DAT_GameSynchronyState::instance.reparseMaps = TRUE;
            }

            // switch between the small and the extended AI selection
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_BASIC_AI_LORD_SELECT) {
                if (DAT_GameCore::instance.numOfAIsWithCastleUnk > 8) {
                    MACRO_CALL(UI::Helpers_Func::ClearLobbyHoveredAI)();
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_EXTENDED_AI_LORD_SELECT,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 4,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 205);
                }
            } else if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_EXTENDED_AI_LORD_SELECT
                && DAT_GameCore::instance.numOfAIsWithCastleUnk <= 8) {
                MACRO_CALL(UI::Helpers_Func::ClearLobbyHoveredAI)();
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                    DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_BASIC_AI_LORD_SELECT,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 4,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 205);
            }
            return;
        }

        // single player
        DAT_GameCore::instance.numOfAIsWithCastleUnk = this->numberOfAIsWithAIV;
        int count = 0;
        for (int aiIndex = 0; aiIndex < 16; ++aiIndex) {
            if (this->aivFileAvailabilityPerAIArray[aiIndex] != 0) {
                DAT_GameCore::instance.arrayOfLordIdsWithAIVsUnk[count] = aiIndex + 1;
                ++count;
            }
        }
    }

}
}
