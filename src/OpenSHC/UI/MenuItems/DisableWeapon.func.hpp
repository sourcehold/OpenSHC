/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/DisableWeapon.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/DisableWeapon.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace DisableWeapon_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BB740,
                &OpenSHC::UI::MenuItems::DisableWeapon::MenuItemActionHandler_DisableWeapon_Main)
            MenuItemActionHandler_DisableWeapon_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BB7B0,
                &OpenSHC::UI::MenuItems::DisableWeapon::MenuItemRenderFunction_DisableWeapon_Main)
            MenuItemRenderFunction_DisableWeapon_Main;

        } // namespace DisableWeapon_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
