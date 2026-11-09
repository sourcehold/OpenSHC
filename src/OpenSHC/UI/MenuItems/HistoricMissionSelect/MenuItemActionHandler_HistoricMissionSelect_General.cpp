#include "../HistoricMissionSelect.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/BOOL_CurrentMenuClickState.hpp"
#include "OpenSHC/Globals/DAT_00b96100.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00426B80
        void HistoricMissionSelect::MenuItemActionHandler_HistoricMissionSelect_General(int button, ...)
        {
            if ((DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)) {
                // a sparse switch; the original lays its arms out default, 20, 18, 13
                switch (button) {
                default: {
                    BOOL_CurrentMenuClickState::instance = FALSE;
                    DAT_GameCore::instance.missionNumber1to20 = (DAT_00b96100::instance - button) - 1;
                    DWORD const clickTime = timeGetTime();
                    if (DAT_GameCore::instance.missionNumber1to20
                            != DAT_MenuTextInputState::instance.lastClickedListIndex
                        || 500 <= (int)(clickTime - DAT_MenuTextInputState::instance.lastListClickTime)) {
                        DAT_MenuTextInputState::instance.lastClickedListIndex
                            = DAT_GameCore::instance.missionNumber1to20;
                        DAT_MenuTextInputState::instance.lastListClickTime = clickTime;
                        return;
                    }
                    // the original shares this tail with case 13; writing it out twice adds 9 instructions
                    goto startMission;
                }
                case 20: {
                    ++DAT_GameState::instance.mapAndTime.difficulty;
                    // the original compares against 4 (`cmp eax, 4; jl`), not 3
                    if (4 <= DAT_GameState::instance.mapAndTime.difficulty) {
                        DAT_GameState::instance.mapAndTime.difficulty = 0;
                    }
                    return;
                }
                case 18: {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_HISTORIC_CAMPAIGN_SELECT, 0);
                    return;
                }
                case 13:
                startMission:
                    --DAT_GameCore::instance.missionNumber1to20;
                    DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_CAMPAIGN_MISSION;
                    DAT_GameCore::instance.field_0x74 = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::incrementMissionProgress, DAT_GameCore::ptr)();
                    return;
                }
            }
        }

    }
}
}
