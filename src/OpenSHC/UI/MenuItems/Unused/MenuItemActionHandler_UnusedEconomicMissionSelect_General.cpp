#include "../Unused.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/BOOL_CurrentMenuClickState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Game::GameMode2;
        using UI::Enums::MenuModalType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00426ED0
        void Unused::MenuItemActionHandler_UnusedEconomicMissionSelect_General(int param_1, ...)
        {
            if ((DAT_MenuTextInputState::instance.currentModalDialog == UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE)) {
                if (param_1 == 0xd) {
                LAB_00426f5c:
                    DAT_GameCore::instance.missionNumber1to20 = DAT_GameCore::instance.missionNumber1to20 + -1;
                    DAT_GameCore::instance.gameMode_2 = Game::GM_ECONOMIC_CAMPAIGN_SH1;
                    DAT_GameCore::instance.field26_0x74 = 1;
                    MACRO_CALL_MEMBER(Game::GameCore_Func::incrementMission, DAT_GameCore::ptr)();
                }
                if (param_1 == 0x12) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_MAIN_MENU, 0);
                }
                if (param_1 == 0x14) {
                    DAT_GameState::instance.mapAndTime.difficulty = DAT_GameState::instance.mapAndTime.difficulty + 1;
                    if (3 < DAT_GameState::instance.mapAndTime.difficulty) {
                        DAT_GameState::instance.mapAndTime.difficulty = 0;
                    }
                } else {
                    DAT_GameCore::instance.missionNumber1to20 = -param_1;
                    BOOL_CurrentMenuClickState::instance = FALSE;
                    DWORD DVar1 = timeGetTime();
                    if (DAT_GameCore::instance.missionNumber1to20
                            == DAT_MenuTextInputState::instance.lastClickedListIndex
                        && (int)(DVar1 - DAT_MenuTextInputState::instance.lastListClickTime) < 500)
                        goto LAB_00426f5c;
                    DAT_MenuTextInputState::instance.lastClickedListIndex = DAT_GameCore::instance.missionNumber1to20;
                    DAT_MenuTextInputState::instance.lastListClickTime = DVar1;
                }
            }
        }

    }
}
}
