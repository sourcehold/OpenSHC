#include "../SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/UI/Actions.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/SinglePlayerMapChoice.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b95b74.hpp"
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

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042D640
        void SinglePlayerMapChoice::MenuItemActionHandler_SingleplayerMapChoice_ButtonsAndHands(int param_1, ...)
        {
            int iVar1;
            MenuViewType menuID;
            if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU) {}
            DAT_StopHandlingMenuItems::instance = 0;
            if (param_1 < -100) {
                if (param_1 == -0x65) {
                    iVar1 = DAT_00b95b74::instance + -0xcc;
                    if (iVar1 <= DAT_00b960f4::instance) {
                        DAT_StopHandlingMenuItems::instance = 0;
                    }
                    if (DAT_00b960f4::instance + 0xe <= iVar1) {
                        DAT_00b960f4::instance = DAT_00b960f4::instance + 0xe;
                        DAT_StopHandlingMenuItems::instance = 0;
                    }
                    DAT_00b960f4::instance = iVar1;
                }
                if (param_1 != -0x44c) {
                    if (param_1 != -1000) {
                        DAT_StopHandlingMenuItems::instance = 0;
                    }
                switchD_0042d6cf_caseD_2:
                    if (DAT_MapMissionType::instance == 0) {
                        menuID = OpenSHC::UI::Enums::MVT_MAIN_MENU;
                    } else {
                        menuID = OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(menuID, 10000);
                    DWORD_00b95b1c::instance = timeGetTime();
                    DAT_00b960dc::instance = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                }
            switchD_0042d6cf_caseD_41:
                /*
                  Start game
                 */
                if (-1 < DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected) {
                    if ((DAT_MapMissionType::instance == 0) || (DAT_MapMissionType::instance == 3)) {
                        DAT_GameState::instance.mapAndTime.difficulty = 1;
                    }
                    MACRO_CALL(OpenSHC::UI::Actions_Func::LaunchSinglePlayerGameUnk)(0);
                }
            } else {
                switch (param_1) {
                case 2:
                    goto switchD_0042d6cf_caseD_2;
                case 0x41:
                    goto switchD_0042d6cf_caseD_41;
                case 0x42:
                    /*
                      castle builder and landscape mode
                     */
                    if (DAT_MapMissionType::instance != 0) {
                        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                        DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                        DAT_MapMissionType::instance = 0;
                    }
                    break;
                case 0x43:
                    /*
                      unknown
                     */
                    if (DAT_MapMissionType::instance != 1) {
                        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                        DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                        DAT_MapMissionType::instance = 1;
                    }
                    break;
                case 0x44:
                    /*
                      siege mode
                     */
                    if (DAT_MapMissionType::instance != 2) {
                        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                        DAT_MapMissionType::instance = 2;
                    }
                    break;
                case 0x45:
                    /*
                      difficulty button
                     */
                    if ((DAT_GameCore::instance.mapU4Int1_2 == 0) && (DAT_MapMissionType::instance != 0)) {
                        DAT_GameState::instance.mapAndTime.difficulty
                            = DAT_GameState::instance.mapAndTime.difficulty + 1;
                        if (4 <= DAT_GameState::instance.mapAndTime.difficulty) {
                            DAT_GameState::instance.mapAndTime.difficulty = 0;
                        }
                        MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeSiegeRelatedCopying)(
                            DAT_GameState::instance.mapAndTime.difficulty);
                    }
                    break;
                case 0x4a:
                    /*
                      Advanced?
                     */
                    if (((DAT_GameCore::instance.mapU4Int1_2 == 0) && (DAT_MapMissionType::instance == 2))
                        && (DAT_GameSynchronyState::instance.currentPlayerSlotID == 2)) {
                        DAT_SH1_SiegeAdvancedMode::instance = DAT_SH1_SiegeAdvancedMode::instance ^ 1;
                    }
                    break;
                case 0x4c:
                    if (DAT_MapMissionType::instance != 3) {
                        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                        DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                        DAT_MapMissionType::instance = 3;
                    }
                    break;
                case 0x4d:
                    /*
                      "Attacking" or "Defending"
                     */
                    if ((DAT_MapMissionType::instance == 2) && (DAT_GameCore::instance.mapU4Int1_2 == 0)) {
                        if (DAT_GameSynchronyState::instance.currentPlayerSlotID != 1) {
                            DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                            DAT_SH1_SiegeAdvancedMode::instance = 0;
                        }
                        DAT_GameSynchronyState::instance.currentPlayerSlotID = 2;
                    }
                    break;
                case -100:
                    DAT_00b960f4::instance = DAT_00b960f4::instance + -0xe;
                    if (DAT_00b960f4::instance < 0) {
                        DAT_00b960f4::instance = 0;
                    }
                    break;
                case -0xb:
                    if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber + -0xd) {
                        DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                            = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + 1;
                        MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                                MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                            DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                    }
                    break;
                case -10:
                    if (0 < DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset) {
                        DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                            = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + -1;
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
