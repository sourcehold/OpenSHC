// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../RankingGames.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/CHAR_ARRAY_00eb9ac8.hpp"
#include "OpenSHC/Globals/DAT_00ed2788.hpp"
#include "OpenSHC/Globals/DAT_00ed3124.hpp"
#include "OpenSHC/Globals/DAT_CurrentMenuID_3.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2DataArray.hpp"
#include "OpenSHC/Globals/DAT_StoredGameMode.hpp"
#include "OpenSHC/Globals/INT_00eb9b60.hpp"
#include "OpenSHC/Globals/INT_00ed3120.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb96d8.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D9730
        void RankingGames::MenuItemActionHandler_RankingGames_Main(int button, ...)
        {
            // buttons -10 and -11 scroll the list, which shows 8 rows
            if (button == -10) {
                if (INT_00ed3120::instance > 0) {
                    --INT_00ed3120::instance;
                }
                return;
            }
            if (button == -11) {
                if (INT_00ed3120::instance < INT_00eb9b60::instance - 8) {
                    ++INT_00ed3120::instance;
                }
                return;
            }
            // buttons 0 to 7 are the rows: a row shows that game's end screen
            if (button < 8 && INT_00ed3120::instance + button < INT_00eb9b60::instance) {
                int const game = INT_ARRAY_00eb96d8::instance[INT_00ed3120::instance + button];
                DAT_GameSynchronyState::instance.finalResults = DAT_SkMasters2DataArray::instance[game].results;
                DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER;
                DAT_GameSynchronyState::instance.currentGameMode = OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER;
                if (DAT_SkMasters2DataArray::instance[game].aliveArray[1] != 0) {
                    // "win_screen_crusader.tgx"
                    strcpy(CHAR_ARRAY_00eb9ac8::instance, S_WIN_SCREEN_CRUSADER_TGX_005AB024);
                    if (DAT_SkMasters2DataArray::instance[game].lordType != 0) {
                        // "win_screen_arab.tgx"
                        strcpy(CHAR_ARRAY_00eb9ac8::instance, S_WIN_SCREEN_ARAB_TGX_005AB010);
                    }
                } else {
                    // "lose_screen_crusader.tgx"
                    strcpy(CHAR_ARRAY_00eb9ac8::instance, S_LOSE_SCREEN_CRUSADER_TGX_005AAFF4);
                    if (DAT_SkMasters2DataArray::instance[game].lordType != 0) {
                        // "lose_screen_arab.tgx"
                        strcpy(CHAR_ARRAY_00eb9ac8::instance, S_LOSE_SCREEN_ARAB_TGX_005AAFDC);
                    }
                }
                DAT_GameCore::instance.skipStoreSKMasters = 1;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MISSION_FINISHED_TRANSITION, 0);
            }
            // buttons from 40 on delete the game in that row, after asking
            if (button >= 40 && INT_00ed3120::instance + button - 40 < INT_00eb9b60::instance) {
                DAT_00ed2788::instance = INT_ARRAY_00eb96d8::instance[INT_00ed3120::instance + button - 40];
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_DELETE_GAME_RECORD, FALSE);
            }
            // button 11 goes back where the rankings were opened from
            if (button == 11) {
                if (DAT_CurrentMenuID_3::instance == OpenSHC::UI::Enums::MVT_CRUSADE_MAP) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_CRUSADE_MAP, 0);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_LOBBY_MENU, 0);
                }
                DAT_GameSynchronyState::instance.currentGameMode = DAT_StoredGameMode::instance;
                return;
            }
            // headers 20 to 29 sort by columns 1 to 10: again on the same column turns the order round
            if (button >= 20 && button <= 29) {
                if (DAT_MissionDefinedData::instance.sortColumn != button - 19) {
                    DAT_MissionDefinedData::instance.sortColumn = button - 19;
                    DAT_MissionDefinedData::instance.descending = TRUE;
                } else {
                    // (!descending: quick_diff 0.9506 -> 0.9354)
                    DAT_MissionDefinedData::instance.descending = 1 - DAT_MissionDefinedData::instance.descending;
                }
                MACRO_CALL(OpenSHC::Game::Skirmish_Func::Skirmish_PrepareLeaderboardView)();
                int lastFirstRow = INT_00eb9b60::instance - 8;
                if (lastFirstRow < 0) {
                    lastFirstRow = 0;
                }
                if (INT_00ed3120::instance > lastFirstRow) {
                    INT_00ed3120::instance = lastFirstRow;
                }
            }
            // headers 30 and 31 turn the "Crusader Trail Only" (1) and "Custom Games Only" (2) filters on and off; 0 is
            // "All Games"
            if (button == 30) {
                if (DAT_00ed3124::instance != 1) {
                    DAT_00ed3124::instance = 1;
                } else {
                    DAT_00ed3124::instance = 0;
                }
            } else if (button == 31) {
                if (DAT_00ed3124::instance != 2) {
                    DAT_00ed3124::instance = 2;
                } else {
                    DAT_00ed3124::instance = 0;
                }
            } else {
                return;
            }
            MACRO_CALL(OpenSHC::Game::Skirmish_Func::Skirmish_PrepareLeaderboardView)();
            int lastFirstRow = INT_00eb9b60::instance - 8;
            if (lastFirstRow < 0) {
                lastFirstRow = 0;
            }
            if (INT_00ed3120::instance > lastFirstRow) {
                INT_00ed3120::instance = lastFirstRow;
            }
        }

    }
}
}
