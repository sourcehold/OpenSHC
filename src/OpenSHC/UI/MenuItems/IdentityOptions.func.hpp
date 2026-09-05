/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/IdentityOptions.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/IdentityOptions.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace IdentityOptions_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00491CE0,
                &OpenSHC::UI::MenuItems::IdentityOptions::MenuItemActionHandler_IdentityOptions_LordIcons)
            MenuItemActionHandler_IdentityOptions_LordIcons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00491D70,
                &OpenSHC::UI::MenuItems::IdentityOptions::MenuItemRenderFunction_IdentityOptions_LordIcons)
            MenuItemRenderFunction_IdentityOptions_LordIcons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00493D30,
                &OpenSHC::UI::MenuItems::IdentityOptions::MenuItemActionHandler_IdentityOptions_Confirm)
            MenuItemActionHandler_IdentityOptions_Confirm;

        } // namespace IdentityOptions_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
