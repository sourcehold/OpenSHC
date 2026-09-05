/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/GreatestLord.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/GreatestLord.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace GreatestLord_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004AE720,
                &OpenSHC::UI::MenuItems::GreatestLord::MenuItemRenderFunction_GreatestLord_Main)
            MenuItemRenderFunction_GreatestLord_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004B1990,
                &OpenSHC::UI::MenuItems::GreatestLord::MenuItemActionHandler_GreatestLord_Main)
            MenuItemActionHandler_GreatestLord_Main;

        } // namespace GreatestLord_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
