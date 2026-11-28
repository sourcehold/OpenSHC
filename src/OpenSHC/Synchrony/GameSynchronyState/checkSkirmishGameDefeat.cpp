#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    struct TeamDefeatCount {
        int players, lordsKilled;
    };

    // FUNCTION: STRONGHOLDCRUSADER 0x00486600
    void GameSynchronyState::checkSkirmishGameDefeat()
    {
        // declared at the top for the match: the original reserves stack slots for these three and copies them from
        // the zero register
        int activeTeams = 0;
        int defeatedTeams = 0;
        BOOLEnum found = FALSE;
        if (this->currentGameMode == Game::GM_SOLITARY) {
            return;
        }
        int player;
        for (player = 1; player < 9; ++player) {
            if (DAT_GameState::instance.playerDataArray[player].commemorationShrinePlacementCountdown <= 0) {
                continue;
            }
            DAT_GameState::instance.playerDataArray[player].commemorationShrinePlacementCountdown -= 1;
            if (DAT_GameState::instance.playerDataArray[player].commemorationShrinePlacementCountdown == 0) {
                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::placeCommemoratingStatueAtGoodLocation,
                    DAT_PathFindingState::ptr)(player);
            }
        }
        if (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION
            || DAT_GameState::instance.mapAndTime.gameOver != FALSE) {
            return;
        }
        if (DAT_GameCore::instance.unknownAlwaysZero != 0) {
            DAT_GameCore::instance.unknownAlwaysZero = 0;
            for (player = 1; player < 9; ++player) {
                DAT_GameState::instance.mapAndTime.playerIsAlive[player] = 0;
                DAT_GameState::instance.playerDataArray[player].playerDeathRelated = 1;
            }
            DAT_GameState::instance.mapAndTime.gameOver = TRUE;
            DAT_GameState::instance.mapAndTime.gameOverTime = timeGetTime();
            DAT_GameState::instance.mapAndTime.playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
            DAT_GameCore::instance.skipStoreSKMasters = 0;
            MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                UI::Enums::DEID_WIN_DEFEAT_WINDOW, 1);
            return;
        }

        TeamDefeatCount teams[9];
        for (int team = 1; team < (int)countof(teams); ++team) {
            teams[team].lordsKilled = 0;
            teams[team].players = 0;
        }
        for (player = 1; player < 9; ++player) {
            if (this->currentPlayerFullIDArray[player] == -1 && this->currentAIArray[player] == 0) {
                continue;
            }
            teams[DAT_GameState::instance.mapAndTime.playerTeams[player]].players += 1;
            if (DAT_GameState::instance.playerDataArray[player].lordKilledByPlayerID != 0) {
                teams[DAT_GameState::instance.mapAndTime.playerTeams[player]].lordsKilled += 1;
            }
        }
        int winningTeam = 0;
        for (int team = 1; team < (int)countof(teams); ++team) {
            if (teams[team].players == 0) {
                continue;
            }
            ++activeTeams;
            if (teams[team].lordsKilled == teams[team].players) {
                ++defeatedTeams;
            } else {
                winningTeam = team;
            }
        }

        int won[9];
        for (player = 1; player < 9; ++player) {
            won[player] = 0;
        }
        if (defeatedTeams >= activeTeams - 1) {
            DAT_GameCore::instance.unknownAlwaysZero = 0;
        } else {
            if (DAT_GameCore::instance.mapU4Int0 == 0) {
                return;
            }
            for (player = 1; player < 9; ++player) {
                if ((this->currentPlayerFullIDArray[player] != -1 || this->currentAIArray[player] != 0)
                    && DAT_GameState::instance.playerDataArray[player].field_0x229c == 0) {
                    winningTeam = DAT_GameState::instance.mapAndTime.playerTeams[player];
                    found = TRUE;
                }
            }
            if (!found) {
                return;
            }
        }

        for (int player = 1; player < 9; ++player) {
            if ((this->currentPlayerFullIDArray[player] != -1 || this->currentAIArray[player] != 0)
                && DAT_GameState::instance.mapAndTime.playerTeams[player] == winningTeam) {
                won[player] = 1;
            }
        }
        for (int player = 1; player < 9; ++player) {
            if (this->currentPlayerFullIDArray[player] == -1 && this->currentAIArray[player] == 0) {
                continue;
            }
            DAT_GameState::instance.mapAndTime.playerIsAlive[player] = (short)won[player];
            DAT_GameState::instance.mapAndTime.gameOver = TRUE;
            DAT_GameState::instance.playerDataArray[player].playerDeathRelated = 1;
            DAT_GameState::instance.mapAndTime.gameOverTime = timeGetTime();
            DAT_GameCore::instance.skipStoreSKMasters = 0;
            MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                UI::Enums::DEID_WIN_DEFEAT_WINDOW, 1);
            if (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab == UI::Enums::BMTT_SOLDIERS
                || DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab == UI::Enums::BMTT_UNKNOWN_62) {
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                    = DAT_GameCore::instance.tabTypeSiegeSubset;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_BUILD_MENU, 0);
            }
            DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_NULL;
            if (DAT_UnitsState::instance.totalUnitsInSelection > 0) {
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
            }
        }
    }

}
}
