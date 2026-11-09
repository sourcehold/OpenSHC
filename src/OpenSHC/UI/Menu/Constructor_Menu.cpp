#include "../Menu.func.hpp"

#include "OpenSHC/UI/Enums/MenuItemType.hpp"
#include "OpenSHC/UI/Enums/MenuItemUCMarker.hpp"

namespace OpenSHC {
namespace UI {

    using namespace OpenSHC::UI::Enums;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4100
    Menu* Menu::Constructor_Menu(MenuItem* menuItemArrayAddress)
    {
        // item types and flags without a name yet, as in handleMenuItems
        int const optionGroupFlag = 1 << 29;
        int const optionType = MIT_START_OF_INTERACTION_GROUPUnk | 1 << 28;
        int const alternativeFlag = 1 << 26;
        int const alternativesFlag = 1 << 27;
        this->menuItemArray = menuItemArrayAddress;
        this->xPosition = 0;
        this->yPosition = 0;
        this->thousand = 1000;
        this->zero = 0;
        this->someTimestampUnk = 0;
        this->mouseXScreenSpace = -1000;
        for (MenuItem* item = menuItemArrayAddress; item->menuItemType != MIT_LAST_ENTRY; ++item) {
            item->menuPointer = this;
            if (item->position.ucInfo.ucMarker_0x0 == USE_UC_COORDS) {
                item->ucID = item->position.ucInfo.ucIndex_0x4;
            } else {
                item->ucID = -1;
            }
            item->unknownZero = 0;
            if (item->menuItemType == MIT_TAB_CONSIDER_ITEM_SKIP_BECAUSE_OTHER_MENU_TAB) {
                // a tab's items reach up to the next tab, the end, or past a stop item
                int count = 0;
                MenuItem* next;
                for (next = item + 1; next->menuItemType != MIT_LAST_ENTRY
                    && next->menuItemType != MIT_TAB_CONSIDER_ITEM_SKIP_BECAUSE_OTHER_MENU_TAB
                    && next->menuItemType != MIT_STOP_HANDLING;
                    ++next) {
                    ++count;
                }
                if (next->menuItemType == MIT_STOP_HANDLING) {
                    ++count;
                }
                item->firstItemTypeData.itemsToSkip = count;
            } else if (item->menuItemType == MIT_START_OF_INTERACTION_GROUPUnk) {
                // the group's members take the group's callbacks where they have none
                MenuItemActionHandlerUnion actionHandler = item->menuItemActionHandler;
                MenuItemRenderFunctionUnion renderFunction = item->menuItemRenderFunction;
                MenuItem* member = item + 1;
                int count = 0;
                for (; member->menuItemType & MIT_PART_OF_INTERACTION_GROUPUnk; ++member) {
                    if (member->menuItemActionHandler.simple == NULL) {
                        member->menuItemActionHandler = actionHandler;
                    }
                    if (member->menuItemRenderFunction.simple == NULL) {
                        member->menuItemRenderFunction = renderFunction;
                    }
                    ++count;
                }
                item->firstItemTypeData.itemsToSkip = count;
                // options follow, each with members of its own (a while: a for over the options loses the match)
                while (member->menuItemType == optionType) {
                    item->menuItemType |= optionGroupFlag;
                    actionHandler = member->menuItemActionHandler;
                    renderFunction = member->menuItemRenderFunction;
                    MenuItem* const option = member;
                    count = 0;
                    for (++member; member->menuItemType & MIT_PART_OF_INTERACTION_GROUPUnk; ++member) {
                        if (member->menuItemActionHandler.simple == NULL) {
                            member->menuItemActionHandler = actionHandler;
                        }
                        if (member->menuItemRenderFunction.simple == NULL) {
                            member->menuItemRenderFunction = renderFunction;
                        }
                        ++count;
                    }
                    option->firstItemTypeData.itemsToSkip = count;
                }
            } else if (item->menuItemType & alternativeFlag) {
                // the item before a run of alternatives is marked as its head
                MenuItem* head;
                for (head = item; head->menuItemType & alternativeFlag && head != menuItemArrayAddress; --head) {}
                head->menuItemType |= alternativesFlag;
            }
        }
        return this;
    }

}
}
