/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/OptionsMenu.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/OptionsMenu.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace OptionsMenu_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00491840,
                &OpenSHC::UI::MenuItems::OptionsMenu::MenuItemRenderFunction_OptionsMenu_Buttons)
            MenuItemRenderFunction_OptionsMenu_Buttons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00491A30,
                &OpenSHC::UI::MenuItems::OptionsMenu::MenuItemRenderFunction_OptionsMenu_SubOptionsButtons)
            MenuItemRenderFunction_OptionsMenu_SubOptionsButtons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00493BD0,
                &OpenSHC::UI::MenuItems::OptionsMenu::MenuItemActionHandler_OptionsMenu_SubOptionsButtons)
            MenuItemActionHandler_OptionsMenu_SubOptionsButtons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00496B80,
                &OpenSHC::UI::MenuItems::OptionsMenu::MenuItemActionHandler_OptionsMenu_Buttons)
            MenuItemActionHandler_OptionsMenu_Buttons;

        } // namespace OptionsMenu_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
