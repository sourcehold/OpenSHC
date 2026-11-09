#include "../Menu.func.hpp"

#include "OpenSHC/UI/MenuItem.func.hpp"
#include "OpenSHC/UI/Enums/MenuItemHandleState.hpp"
#include "OpenSHC/UI/Enums/MenuItemType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {

    using namespace OpenSHC::UI::Enums;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F6280
    void Menu::handleMenuItems(MenuItemHandleState funcIndex)
    {
        // item types without a name yet: two kinds of option group, and flags in the high bits
        int const optionGroupType = MIT_START_OF_INTERACTION_GROUPUnk | 1 << 29;
        int const optionType = MIT_START_OF_INTERACTION_GROUPUnk | 1 << 28;
        int const clickHandlerType = 7;
        int const alternativeFlag = 1 << 26;
        int const alternativesFlag = 1 << 27;
        int const renderSeparatelyFlag = 1 << 23;
        int const hiddenFlag = 1 << 31;
        this->currentBuildMenuButtonShiftUnk_0x14 = 0;
        for (MenuItem* item = this->menuItemArray; item->menuItemType != MIT_LAST_ENTRY; ++item) {
            MenuItemTypeInt const type = item->menuItemType;
            if (type == MIT_TAB_CONSIDER_ITEM_SKIP_BECAUSE_OTHER_MENU_TAB) {
                if (item->callbackParameter.activeMenuTab.tabType != DAT_GameCore::instance.activeMenuTab.tabType
                    && funcIndex != MIHS_RESET_MENU_ITEM_STATEUnk) {
                    item += item->firstItemTypeData.itemsToSkip;
                }
            } else if (type == MIT_TAB_CONSIDER_STOP_BECAUSE_IS_CURRENT_MENU_TAB) {
                if (item->callbackParameter.activeMenuTab.tabType == DAT_GameCore::instance.activeMenuTab.tabType
                    && funcIndex != MIHS_RESET_MENU_ITEM_STATEUnk) {
                    return;
                }
            } else if (type == MIT_STOP_HANDLING) {
                return;
            } else if (type == MIT_ENABLE_OR_WRAP_BUILD_MENU_TRANSITION_OFFSET) {
                if (DAT_MenuHandlerState::instance.isBuildMenuTransitioning_0x18
                    && funcIndex == MIHS_HANDLE_INPUT_CALLBACKSUnk) {
                    return;
                }
                if (this->currentBuildMenuButtonShiftUnk_0x14 != 0) {
                    this->currentBuildMenuButtonShiftUnk_0x14 = 0;
                } else {
                    this->currentBuildMenuButtonShiftUnk_0x14
                        = DAT_MenuHandlerState::instance.buildMenuItemsLeftShift_0x28;
                }
            } else if (type == MIT_MENU_MODALUnk) {
                if (DAT_MenuModalComposition1::instance.activeModalDialogID != MMT_NONE) {
                    return;
                }
            } else if (type == optionGroupType) {
                for (MenuItem* option = item + item->firstItemTypeData.itemsToSkip + 1;
                    option->menuItemType == optionType; option += option->firstItemTypeData.itemsToSkip + 1) {
                    if (option->testNotEqualZero == DAT_GameCore::instance.unknownAlwaysZero01) {
                        item = option;
                        break;
                    }
                }
            } else if (type == optionType) {
                item += item->firstItemTypeData.itemsToSkip;
            } else if (type == clickHandlerType) {
                DAT_GameCore::instance.menuType7_MenuItemClickHandlerUnk = item->menuItemActionHandler.simple;
            } else if (type != MIT_START_OF_INTERACTION_GROUPUnk && (type & alternativeFlag) == 0) {
                if (type & alternativesFlag) {
                    for (MenuItem* alternative = item + 1; alternative->menuItemType & alternativeFlag; ++alternative) {
                        if (alternative->testNotEqualZero == DAT_GameCore::instance.unknownAlwaysZero01) {
                            item = alternative;
                            break;
                        }
                    }
                }
                // the sign bit is tested with &, not as >= 0, as the original does
                if (item->menuItemType & hiddenFlag) {
                    continue;
                }
                if (!(((item->menuItemType & renderSeparatelyFlag) != 0
                          && funcIndex == MIHS_PREPARE_AND_RENDER_FOR_FLAG_0X800000)
                        || ((item->menuItemType & renderSeparatelyFlag) == 0 && funcIndex == MIHS_PREPARE_AND_RENDER)
                        || funcIndex == MIHS_HANDLE_INPUT_CALLBACKSUnk || funcIndex == MIHS_RESET_MENU_ITEM_STATEUnk)) {
                    continue;
                }
                switch (funcIndex) {
                case MIHS_HANDLE_INPUT_CALLBACKSUnk:
                    if (MACRO_CALL_MEMBER(OpenSHC::UI::MenuItem_Func::handleMenuElementsCallbacks, item)()) {
                        return;
                    }
                    break;
                case MIHS_PREPARE_AND_RENDER:
                case MIHS_PREPARE_AND_RENDER_FOR_FLAG_0X800000:
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuItem_Func::prepareAndRenderMenuItems, item)();
                    break;
                case MIHS_RESET_MENU_ITEM_STATEUnk:
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuItem_Func::resetMenuItemStateUnk, item)();
                    break;
                }
            }
        }
    }

}
}
