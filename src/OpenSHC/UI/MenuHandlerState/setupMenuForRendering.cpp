#include "../MenuHandlerState.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"
#include "OpenSHC/UI/Enums/MenuItemHandleState.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuItemHandleState;
    using OpenSHC::UI::Enums::MenuViewType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F6A80
    void MenuHandlerState::setupMenuForRendering(MenuViewType menuID)
    {
        MenuViewTypeInt _menuID;
        MenuIDMenuElementAddressPair* _arrayElementOffset;
        Menu* _menuAddr;
        _menuID = (this->pointerToMenuIDMenuElementAddressMap)->menuID;
        _arrayElementOffset = this->pointerToMenuIDMenuElementAddressMap;
        if (_menuID != OpenSHC::UI::Enums::MVT_MENUVIEWID_MENU_PAIR_ENDMARKER) {
            while (_menuID != menuID) {
                /*
                  next element in the list
                 */
                _menuID = _arrayElementOffset[1].menuID;
                _arrayElementOffset = _arrayElementOffset + 1;
                if (_menuID == OpenSHC::UI::Enums::MVT_MENUVIEWID_MENU_PAIR_ENDMARKER) {}
            }
            /*
              get the value of the menu pointer
             */
            _menuAddr = _arrayElementOffset->menuAddress;
            this->currentMenu = _menuAddr;
            MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::handleMenuItems, _menuAddr)(
                OpenSHC::UI::Enums::MIHS_RESET_MENU_ITEM_STATEUnk);
            _menuAddr->zero = 0;
            (this->currentMenu)->one = 1;
            /*
              call class method for the menu
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::loadMenuElements, DAT_MenuHandlerState::instance.currentMenu)(0);
        }
    }

}
}
