/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/MainMenu.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/MainMenu.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace MainMenu_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00424F50,
                &OpenSHC::UI::MenuItems::MainMenu::MenuItemRenderFunction_MainMenu_Main)
            MenuItemRenderFunction_MainMenu_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004251A0,
                &OpenSHC::UI::MenuItems::MainMenu::MenuItemActionHandler_MainMenu_Main)
            MenuItemActionHandler_MainMenu_Main;

        } // namespace MainMenu_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
