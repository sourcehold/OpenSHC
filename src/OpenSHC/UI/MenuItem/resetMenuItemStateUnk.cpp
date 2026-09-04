#include "OpenSHC/UI/MenuItem.func.hpp"
#include "OpenSHC/UI/Enums/MenuItemType.hpp"
#include "OpenSHC/UI/Enums/MenuItemTypeInt.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuItemType;
    using OpenSHC::UI::Enums::MenuItemTypeInt;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4C30
    void MenuItem::resetMenuItemStateUnk()

    {
        MenuItemTypeInt MVar1;

        this->hovering = 0;
        this->clicked = 0;
        (this->secondItemTypeData).buttonState.someTimestamp_1_0x0 = 0;
        (this->secondItemTypeData).buttonState.clickTimestamp_0x4 = 0;
        (this->secondItemTypeData).buttonState.countTo100 = 0;
        MVar1 = this->menuItemType & Enums::MIT_MENU_ITEM_TYPE_ID_PARTUnk;
        if ((MVar1 == OpenSHC::UI::Enums::MIT_SLIDERUnk) || (MVar1 == OpenSHC::UI::Enums::MIT_SCROLLBARUnk)) {
            (this->secondItemTypeData).buttonState.currentButtonPictureInGm_0xc = -1000;
        }
        return;
    }

}
}
