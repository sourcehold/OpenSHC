#include "../RankingGames.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/CHAR_ARRAY_00eb9ac8.hpp"
#include "OpenSHC/Globals/DAT_00eb9b60.hpp"
#include "OpenSHC/Globals/DAT_00ed2788.hpp"
#include "OpenSHC/Globals/DAT_00ed3120.hpp"
#include "OpenSHC/Globals/DAT_00ed3124.hpp"
#include "OpenSHC/Globals/DAT_CurrentMenuID_3.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2DataArray.hpp"
#include "OpenSHC/Globals/DAT_StoredGameMode.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb96d8.hpp"
#include "OpenSHC/Game/Skirmish/SkirmishStatistics.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;
        using OpenSHC::Game::Skirmish::SkirmishStatistics;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004D9730
        void RankingGames::MenuItemActionHandler_RankingGames_Main(int param_1, ...)
        {
            int iVar1;
            int iVar2;
            int iVar3;
            SkirmishStatistics* pSVar4;
            char* pcVar5;
            SkirmishStatistics* pSVar6;
            char* pcVar7;
            if (param_1 == -10) {
                if (0 < DAT_00ed3120::instance) {
                    DAT_00ed3120::instance = DAT_00ed3120::instance + -1;
                }
            } else if (param_1 == -0xb) {
                if (DAT_00ed3120::instance < DAT_00eb9b60::instance + -8) {
                    DAT_00ed3120::instance = DAT_00ed3120::instance + 1;
                }
            } else {
                if ((param_1 < 8) && (DAT_00ed3120::instance + param_1 < DAT_00eb9b60::instance)) {
                    iVar1 = INT_ARRAY_00eb96d8::instance[DAT_00ed3120::instance + param_1];
                    iVar3 = DAT_SkMasters2DataArray::instance[iVar1].aliveArray[1];
                    pSVar4 = &DAT_SkMasters2DataArray::instance[iVar1].results;
                    pSVar6 = &DAT_GameSynchronyState::instance.finalResults;
                    for (iVar2 = 0x1de; iVar2 != 0; iVar2 = iVar2 + -1) {
                        *(undefined4*)pSVar6->names[0] = *(undefined4*)pSVar4->names[0];
                        pSVar4 = (SkirmishStatistics*)(pSVar4->names[0] + 4);
                        pSVar6 = (SkirmishStatistics*)(pSVar6->names[0] + 4);
                    }
                    DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER;
                    DAT_GameSynchronyState::instance.currentGameMode
                        = OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER;
                    if (iVar3 == 0) {
                        iVar1 = DAT_SkMasters2DataArray::instance[iVar1].lordType;
                        pcVar5 = "lose_screen_crusader.tgx";
                        pcVar7 = CHAR_ARRAY_00eb9ac8::instance;
                        for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
                            *(undefined4*)pcVar7 = *(undefined4*)pcVar5;
                            pcVar5 = pcVar5 + 4;
                            pcVar7 = pcVar7 + 4;
                        }
                        *pcVar7 = *pcVar5;
                        if (iVar1 != 0) {
                            memcpy(CHAR_ARRAY_00eb9ac8::instance, "lose_screen_arab.tgx", 20);
                            (*(uint*)(CHAR_ARRAY_00eb9ac8::instance + 20)) = (*(uint*)(CHAR_ARRAY_00eb9ac8::instance + 20)) & 0xffffff00;
                        }
                    } else {
                        strcpy(CHAR_ARRAY_00eb9ac8::instance, "win_screen_crusader.tgx");
                        if (DAT_SkMasters2DataArray::instance[iVar1].lordType != 0) {
                            strcpy(CHAR_ARRAY_00eb9ac8::instance, "win_screen_arab.tgx");
                        }
                    }
                    DAT_GameCore::instance.skipStoreSKMasters = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_MISSION_FINISHED_TRANSITION, 0);
                }
                if ((0x27 < param_1)
                    && (iVar1 = DAT_00ed3120::instance + -0x28 + param_1, iVar1 < DAT_00eb9b60::instance)) {
                    DAT_00ed2788::instance = INT_ARRAY_00eb96d8::instance[iVar1];
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_DELETE_GAME_RECORD, FALSE);
                }
                if (param_1 == 0xb) {
                    if (DAT_CurrentMenuID_3::instance != 0x39) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_LOBBY_MENU, 0);
                        DAT_GameSynchronyState::instance.currentGameMode = DAT_StoredGameMode::instance;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_CRUSADE_MAP, 0);
                    DAT_GameSynchronyState::instance.currentGameMode = DAT_StoredGameMode::instance;
                }
                if (param_1 - 0x14U < 10) {
                    if (DAT_MissionDefinedData::instance.sortColumn == param_1 + -0x13) {
                        DAT_MissionDefinedData::instance.descending = 1 - DAT_MissionDefinedData::instance.descending;
                    } else {
                        DAT_MissionDefinedData::instance.descending = 1;
                        DAT_MissionDefinedData::instance.sortColumn = param_1 + -0x13;
                    }
                    MACRO_CALL(OpenSHC::Game::Skirmish_Func::Skirmish_PrepareLeaderboardView)();
                    iVar1 = DAT_00eb9b60::instance + -8;
                    if (iVar1 < 0) {
                        iVar1 = 0;
                    }
                    if (iVar1 < DAT_00ed3120::instance) {
                        DAT_00ed3120::instance = iVar1;
                    }
                }
                if (param_1 == 0x1e) {
                    DAT_00ed3124::instance = (uint)(DAT_00ed3124::instance != 1);
                } else {
                    if (param_1 != 0x1f) {}
                    DAT_00ed3124::instance = -(uint)(DAT_00ed3124::instance != 2) & 2;
                }
                MACRO_CALL(OpenSHC::Game::Skirmish_Func::Skirmish_PrepareLeaderboardView)();
                iVar1 = DAT_00eb9b60::instance + -8;
                if (iVar1 < 0) {
                    iVar1 = 0;
                }
                if (iVar1 < DAT_00ed3120::instance) {
                    DAT_00ed3120::instance = iVar1;
                }
            }
        }

    }
}
}
