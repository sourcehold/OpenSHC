#include "../Helpers.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x00440430
    HCURSOR Helpers::SetCursorDependingOnProgramState()
    {
        if (DAT_MouseState::instance.waitCursorToggle) {
            return MACRO_CALL_MEMBER(Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(3);
        }
        if (DAT_MenuTextInputState::instance.currentModalDialog == UI::Enums::MMT_NO_MENU
            && DAT_TextEditorState::instance.helpDialogVariant == 0
            && !DAT_TextEditorState::instance.isDialogStateInitialized) {
            // Two ifs with the same body, as in the original: one condition with || orders the blocks differently.
            if (DAT_MouseState::instance.field_0x1dc >= 0 && DAT_MouseState::instance.field_0x1dc <= 999) {
                return MACRO_CALL_MEMBER(Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(1);
            }
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_INTRO_LOGOS) {
                return MACRO_CALL_MEMBER(Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(1);
            }
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU
                && DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_DELETE) {
                if (!DAT_TileMapState::instance.demolishBlocked) {
                    return MACRO_CALL_MEMBER(Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(2);
                }
                return MACRO_CALL_MEMBER(Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(5);
            }
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR) {
                return MACRO_CALL_MEMBER(Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(4);
            }
        }
        // Cursor 6 is used while playing an Arabian lord, and around campaign missions 6 to 10.
        if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                if (DAT_GameCore::instance.selectedLordTypes[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    == 1) {
                    return MACRO_CALL_MEMBER(Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(6);
                }
            } else if (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION
                && DAT_GameCore::instance.missionNumber1to20 >= 6 && DAT_GameCore::instance.missionNumber1to20 <= 10) {
                return MACRO_CALL_MEMBER(Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(6);
            }
        } else if (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION
            && DAT_GameCore::instance.missionNumber1to20 >= 6 && DAT_GameCore::instance.missionNumber1to20 <= 10
            && (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_HISTORIC_CAMPAIGN_INTRO
                || DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_HISTORIC_CAMPAIGN_OUTRO
                || DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_SCENARIO_DESCRIPTION
                || DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_HISTORIC_MISSION_PICTURE
                || DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_HISTORIC_MISSION_INTRO)) {
            return MACRO_CALL_MEMBER(Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(6);
        }
        return MACRO_CALL_MEMBER(Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(0);
    }

}
}
