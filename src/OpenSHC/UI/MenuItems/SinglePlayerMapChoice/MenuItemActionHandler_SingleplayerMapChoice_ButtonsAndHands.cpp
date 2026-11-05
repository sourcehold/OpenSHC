#include "../SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/UI/Actions.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapMissionType.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SH1_SiegeAdvancedMode.hpp"
#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"
#include "OpenSHC/Globals/DWORD_00b95b1c.hpp"
#include "OpenSHC/Globals/INT_00b95b74.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042D640
        void SinglePlayerMapChoice::MenuItemActionHandler_SingleplayerMapChoice_ButtonsAndHands(int param_1, ...)
        {
            if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU) {
                return;
            }
            DAT_StopHandlingMenuItems::instance = 0;
            if (param_1 < -100) {
                if (param_1 == -101) {
                    int iVar1 = INT_00b95b74::instance - 204;
                    if ((int)DAT_00b960f4::instance >= iVar1) {
                        DAT_StopHandlingMenuItems::instance = 0;
                    }
                    if (DAT_00b960f4::instance + 14 <= iVar1) {
                        DAT_00b960f4::instance += 14;
                        DAT_StopHandlingMenuItems::instance = 0;
                    }
                    DAT_00b960f4::instance = iVar1;
                    return;
                }
                if (param_1 != -1100) {
                    if (param_1 != -1000) {
                        DAT_StopHandlingMenuItems::instance = 0;
                        return;
                    }
                switchD_0042d6cf_caseD_2:
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        (DAT_MapMissionType::instance == 0 ? OpenSHC::UI::Enums::MVT_MAIN_MENU
                                                           : OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS),
                        10000);
                    DWORD_00b95b1c::instance = timeGetTime();
                    DAT_00b960dc::instance = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                    return;
                }
            switchD_0042d6cf_caseD_41:
                // Start game
                if (-(int)DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    > 1 + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected) {
                    if ((DAT_MapMissionType::instance == 0) || (DAT_MapMissionType::instance == 3)) {
                        DAT_GameState::instance.mapAndTime.difficulty = 1;
                        return;
                    }
                    MACRO_CALL(OpenSHC::UI::Actions_Func::LaunchSinglePlayerGameUnk)(0);
                }
            } else {
                switch (param_1) {
                case 2:
                    goto switchD_0042d6cf_caseD_2;
                case 65:
                    goto switchD_0042d6cf_caseD_41;
                case 66:
                    // castle builder and landscape mode
                    if (DAT_MapMissionType::instance != 0) {
                        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                        DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                        DAT_MapMissionType::instance = 0;
                        return;
                    }
                    break;
                case 67:
                    // unknown
                    if (DAT_MapMissionType::instance != 1) {
                        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                        DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                        DAT_MapMissionType::instance = 1;
                        return;
                    }
                    break;
                case 68:
                    // siege mode
                    if (DAT_MapMissionType::instance != 2) {
                        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                        DAT_MapMissionType::instance = 2;
                        return;
                    }
                    break;
                case 69:
                    // difficulty button
                    if ((DAT_GameCore::instance.mapU4Int1_2 == 0) && (DAT_MapMissionType::instance != 0)) {
                        ++DAT_GameState::instance.mapAndTime.difficulty;
                        if (4 <= DAT_GameState::instance.mapAndTime.difficulty) {
                            DAT_GameState::instance.mapAndTime.difficulty = 0;
                        }
                        MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeSiegeRelatedCopying)(
                            DAT_GameState::instance.mapAndTime.difficulty);
                    }
                    break;
                case 74:
                    // Advanced?
                    if (DAT_GameCore::instance.mapU4Int1_2 == 0 && DAT_MapMissionType::instance == 2
                        && DAT_GameSynchronyState::instance.currentPlayerSlotID == 2) {
                        DAT_SH1_SiegeAdvancedMode::instance ^= 1;
                        return;
                    }
                    break;
                case 76:
                    if (DAT_MapMissionType::instance != 3) {
                        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                        DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                        DAT_MapMissionType::instance = 3;
                        return;
                    }
                    break;
                case 77:
                    // "Attacking" or "Defending"
                    if ((DAT_MapMissionType::instance == 2) && (DAT_GameCore::instance.mapU4Int1_2 == 0)) {
                        if (DAT_GameSynchronyState::instance.currentPlayerSlotID != 1) {
                            DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                            DAT_SH1_SiegeAdvancedMode::instance = 0;
                            return;
                        }
                        DAT_GameSynchronyState::instance.currentPlayerSlotID = 2;
                        return;
                    }
                    break;
                case -100:
                    DAT_00b960f4::instance -= 14;
                    if ((int)DAT_00b960f4::instance < 0) {
                        DAT_00b960f4::instance = 0;
                        return;
                    }
                    break;
                case -11:
                    if ((int)DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        < (int)DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 13) {
                        ++DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                        MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                                MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                            DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                        return;
                    }
                    break;
                case -10:
                    if (0 < (int)DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset) {
                        --DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                        MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                                MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                            DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                    }
                }
            }
        }

    }
}
}
