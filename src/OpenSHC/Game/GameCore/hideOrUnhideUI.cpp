#include "../GameCore.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471AA0
    void GameCore::hideOrUnhideUI()
    {
        if ((DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU
                || DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)
            && DAT_MouseState::instance.selectionBoxMode == 0) {
            // hide the menu
            if (DAT_GameCore::instance.activeMenuTab.buildMenuTab != UI::Enums::BMTT_MENU_HIDDEN
                && DAT_GameCore::instance.activeMenuTab.buildMenuTab != 62) {
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU) {
                    if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == UI::Enums::BMTT_SOLDIERS) {
                        DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab = 62;
                        MACRO_CALL_MEMBER(GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            UI::Enums::MVT_BUILD_MENU, 0);
                        return;
                    }
                    MACRO_CALL_MEMBER(GameCore_Func::setTabToSwitchTo, DAT_GameCore::ptr)();
                    DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab = UI::Enums::BMTT_MENU_HIDDEN;
                }
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                    DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo = UI::Enums::BMTT_MENU_HIDDEN;
                }
                MACRO_CALL_MEMBER(GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    (MenuViewType)DAT_GameCore::instance.currentMenuViewType, 0);
                return;
            }

            // unhide the menu
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU) {
                if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == 62) {
                    DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab = UI::Enums::BMTT_SOLDIERS;
                    MACRO_CALL_MEMBER(GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(UI::Enums::MVT_BUILD_MENU, 0);
                    return;
                }
                MACRO_CALL_MEMBER(GameCore_Func::swapBuildMenuTab, DAT_GameCore::ptr)();
            }
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo
                    = DAT_GameCore::instance.secondaryActiveMenuTabToSwitchTo.tabType;
            }
            if (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab == UI::Enums::BMTT_MENU_HIDDEN) {
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU) {
                    DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab = UI::Enums::BMTT_CASTLE;
                    MACRO_CALL_MEMBER(GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(UI::Enums::MVT_BUILD_MENU, 0);
                    return;
                }
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                    DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo = 231;
                }
            }
            MACRO_CALL_MEMBER(GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                (MenuViewType)DAT_GameCore::instance.currentMenuViewType, 0);
            return;
        }

        if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
            this->secondaryActiveMenuTabToSwitchTo = this->buildmenuMenuTabToSwitchTo;
            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab = UI::Enums::BMTT_MENU_HIDDEN;
            MACRO_CALL_MEMBER(GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(UI::Enums::MVT_BUILD_MENU, 0);
        }
    }

}
}
