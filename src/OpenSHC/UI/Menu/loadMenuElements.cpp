#include "../Menu.func.hpp"

#include "OpenSHC/UI/UCPointerStruct.func.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F69D0
    void Menu::loadMenuElements(int ucPositionIndex)
    {
        for (MenuItem* item = this->menuItemArray; item->menuItemType != 102; ++item) {
            if (item->ucID >= 0) {
                MACRO_CALL_MEMBER(UCPointerStruct_Func::loadMenuElement, &DAT_MenuHandlerState::instance.ucPtrStruct)(
                    item->ucID, &item->position.position.x, &item->position.position.y, &item->iconDeactivatedUnk_0x36,
                    ucPositionIndex);
            }
        }
    }

}
}
