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

        using OpenSHC::Game::GameMode2;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00426ED0
        void Unused::MenuItemActionHandler_UnusedEconomicMissionSelect_General(int param_1, ...)
        {
            if ((DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)) {
                /*
                  a chain of `sub`s with a `je` after each (0x426ee9) is MSVC's sparse
                  switch, and the arm bodies are laid out default, 0x14, 0x12, 0xd
                 */
                switch (param_1) {
                default: {
                    BOOL_CurrentMenuClickState::instance = FALSE;
                    DAT_GameCore::instance.missionNumber1to20 = -param_1;
                    DWORD DVar1 = timeGetTime();
                    if (DAT_GameCore::instance.missionNumber1to20
                            != DAT_MenuTextInputState::instance.lastClickedListIndex
                        || 500 <= (int)(DVar1 - DAT_MenuTextInputState::instance.lastListClickTime)) {
                        DAT_MenuTextInputState::instance.lastClickedListIndex
                            = DAT_GameCore::instance.missionNumber1to20;
                        DAT_MenuTextInputState::instance.lastListClickTime = DVar1;
                        return;
                    }
                    goto LAB_00426f5c;
                }
                case 0x14: {
                    DAT_GameState::instance.mapAndTime.difficulty = DAT_GameState::instance.mapAndTime.difficulty + 1;
                    /* the original compares against 4 (`cmp eax, 4; jl`), not 3 */
                    if (4 <= DAT_GameState::instance.mapAndTime.difficulty) {
                        DAT_GameState::instance.mapAndTime.difficulty = 0;
                    }
                    return;
                }
                case 0x12: {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
                    return;
                }
                case 0xd:
                LAB_00426f5c:
                    DAT_GameCore::instance.missionNumber1to20 = DAT_GameCore::instance.missionNumber1to20 + -1;
                    DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1;
                    DAT_GameCore::instance.field26_0x74 = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::incrementMission, DAT_GameCore::ptr)();
                    return;
                }
            }
        }

    }
}
}
