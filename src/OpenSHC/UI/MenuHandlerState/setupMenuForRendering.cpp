#include "../MenuHandlerState.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"
#include "OpenSHC/UI/Enums/MenuItemHandleState.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F6A80
    void MenuHandlerState::setupMenuForRendering(MenuViewType menuID)
    {
        for (MenuIDMenuElementAddressPair* pair = this->pointerToMenuIDMenuElementAddressMap;
            pair->menuID != OpenSHC::UI::Enums::MVT_MENUVIEWID_MENU_PAIR_ENDMARKER; ++pair) {
            if (pair->menuID == menuID) {
                Menu* const menu = pair->menuAddress;
                this->currentMenu = menu;
                MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::handleMenuItems, menu)(
                    OpenSHC::UI::Enums::MIHS_RESET_MENU_ITEM_STATEUnk);
                menu->zero = 0;
                this->currentMenu->one = 1;
                MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::loadMenuElements, this->currentMenu)(0);
                return;
            }
        }
    }

}
}
