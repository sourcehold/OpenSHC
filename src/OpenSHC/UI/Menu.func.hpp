/**
  path: 'OpenSHC/UI/Menu.func.hpp'
*/

#include "OpenSHC/UI/Enums/MenuItemHandleState.hpp"
#include "OpenSHC/UI/Menu.hpp"
namespace OpenSHC {
namespace UI {
    namespace Menu_Func {

        using OpenSHC::UI::Enums::MenuItemHandleState;

        // Constructor

        MACRO_FUNCTION_RESOLVER(
            Menu* (Menu::*)(MenuItem*), false, Address::SHC_3BB0A8C1_0x004F4100, &Menu::Constructor_Menu)
        Constructor_Menu;

        MACRO_FUNCTION_RESOLVER(
            void (Menu::*)(MenuItemHandleState), false, Address::SHC_3BB0A8C1_0x004F6280, &Menu::handleMenuItems)
        handleMenuItems;

        MACRO_FUNCTION_RESOLVER(void (Menu::*)(), false, Address::SHC_3BB0A8C1_0x004F6470, &Menu::updateMenuButtons)
        updateMenuButtons;

        MACRO_FUNCTION_RESOLVER(
            void (Menu::*)(), false, Address::SHC_3BB0A8C1_0x004F64A0, &Menu::renderConstructionMenu)
        renderConstructionMenu;

        MACRO_FUNCTION_RESOLVER(void (Menu::*)(int), false, Address::SHC_3BB0A8C1_0x004F69D0, &Menu::loadMenuElements)
        loadMenuElements;

    } // namespace Menu_Func
} // namespace UI
} // namespace OpenSHC
