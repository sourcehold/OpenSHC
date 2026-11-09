#include "../BuildMenu.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00b960f0.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x00431A90
        void BuildMenu::MenuView_BuildMenu_Prepare()
        {
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                OpenSHC::Text::TAIT_UNKNOWN_4);
            if (DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM
                && DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD
                && DAT_GameCore::instance.menuTabToSwitchTo.tabType != OpenSHC::UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM
                && DAT_GameCore::instance.menuTabToSwitchTo.tabType != OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD) {
                DAT_TileMapState::instance.shiftRelated0or3 = 0;
                DAT_UnitsState::instance.unitCountOfSelection[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 0;
            }
            MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO, 0);
            DAT_WindowAndDirectDraw::instance.pendingMenuRedraw = TRUE;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::getEventIDForTimeUntilDefeatEventType,
                    DAT_MapPropertiesState::ptr)()
                >= 0) {
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    OpenSHC::UI::Enums::DEID_TIME_UNTIL_DEFEAT, 1);
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                if (DAT_GameCore::instance.mapU4Int0 != 0) {
                    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                        OpenSHC::UI::Enums::DEID_UNKNOWN_25, 1);
                }
                // the original tests the game mode again after each call
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                        OpenSHC::UI::Enums::DEID_PLAYER_INFO_ON_HOVER, 1);
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                        && DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                        && DAT_GameState::instance.mapAndTime.skirmishNoRushTicks != 0) {
                        MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                            OpenSHC::UI::Enums::DEID_NO_RUSH, 1);
                    }
                }
            }
            DAT_MouseState::instance.waitCursorToggle = 0;
            INT_00b960f0::instance = 0;
        }

    }
}
}
