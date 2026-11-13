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
        void SinglePlayerMapChoice::MenuItemActionHandler_SingleplayerMapChoice_ButtonsAndHands(int button, ...)
        {
            if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU) {
                return;
            }
            DAT_StopHandlingMenuItems::instance = 0;
            // the cases in the original's block order
            switch (button) {
            case -1000:
            case 2:
                // back
                if (DAT_MapMissionType::instance == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_MAIN_MENU, 10000);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS, 10000);
                }
                DWORD_00b95b1c::instance = timeGetTime();
                DAT_00b960dc::instance = 1;
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                return;
            case -101: {
                // map description scroll down
                int const limit = INT_00b95b74::instance - 204;
                if (DAT_00b960f4::instance >= limit) {
                    return;
                }
                DAT_00b960f4::instance += 14;
                if (DAT_00b960f4::instance > limit) {
                    DAT_00b960f4::instance = limit;
                }
                return;
            }
            case -1100:
            case 65:
                // start the game
                // the offset through ptr: that way the relative selection is read first, for the match
                if (DAT_GameSynchronyState::ptr->DAT_MapSelectionScrollOffset
                        + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                    < 0) {
                    return;
                }
                if (DAT_MapMissionType::instance == 0 || DAT_MapMissionType::instance == 3) {
                    DAT_GameState::instance.mapAndTime.difficulty = 1;
                }
                MACRO_CALL(OpenSHC::UI::Actions_Func::LaunchSinglePlayerGameUnk)(0);
                return;
            case 66:
                // castle builder and landscape mode
                if (DAT_MapMissionType::instance != 0) {
                    DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                    DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                    DAT_MapMissionType::instance = 0;
                }
                return;
            case 67:
                // mission type 1
                if (DAT_MapMissionType::instance != 1) {
                    DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                    DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                    DAT_MapMissionType::instance = 1;
                }
                return;
            case 68:
                // siege mode
                if (DAT_MapMissionType::instance != 2) {
                    DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                    DAT_MapMissionType::instance = 2;
                }
                return;
            case 76:
                // mission type 3
                if (DAT_MapMissionType::instance != 3) {
                    DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                    DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                    DAT_MapMissionType::instance = 3;
                }
                return;
            case 69:
                // difficulty
                if (DAT_GameCore::instance.mapU4Int1_2 == 0 && DAT_MapMissionType::instance != 0) {
                    ++DAT_GameState::instance.mapAndTime.difficulty;
                    if (DAT_GameState::instance.mapAndTime.difficulty >= 4) {
                        DAT_GameState::instance.mapAndTime.difficulty = 0;
                    }
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeSiegeRelatedCopying)(
                        DAT_GameState::instance.mapAndTime.difficulty);
                }
                return;
            case 74:
                // advanced siege, for the defender
                if (DAT_GameCore::instance.mapU4Int1_2 == 0 && DAT_MapMissionType::instance == 2
                    && DAT_GameSynchronyState::instance.currentPlayerSlotID == 2) {
                    DAT_SH1_SiegeAdvancedMode::instance ^= 1;
                }
                return;
            case 77:
                // "Attacking" or "Defending"
                if (DAT_MapMissionType::instance == 2 && DAT_GameCore::instance.mapU4Int1_2 == 0) {
                    if (DAT_GameSynchronyState::instance.currentPlayerSlotID == 1) {
                        DAT_GameSynchronyState::instance.currentPlayerSlotID = 2;
                        return;
                    }
                    DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                    DAT_SH1_SiegeAdvancedMode::instance = 0;
                }
                return;
            case -10:
                // map list scroll up
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset > 0) {
                    --DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                    MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                            MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                        DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                }
                return;
            case -11:
                // map list scroll down
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 13) {
                    ++DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                    MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                            MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                        DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                }
                return;
            case -100:
                // map description scroll up
                DAT_00b960f4::instance -= 14;
                if (DAT_00b960f4::instance < 0) {
                    DAT_00b960f4::instance = 0;
                }
                return;
            }
        }

    }
}
}
