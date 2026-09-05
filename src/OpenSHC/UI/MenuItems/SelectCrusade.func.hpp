/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/SelectCrusade.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/SelectCrusade.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SelectCrusade_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042BF00,
                &OpenSHC::UI::MenuItems::SelectCrusade::MenuItemActionHandler_SelectCrusade_Main)
            MenuItemActionHandler_SelectCrusade_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042C060,
                &OpenSHC::UI::MenuItems::SelectCrusade::MenuItemRenderFunction_SelectCrusade_Main)
            MenuItemRenderFunction_SelectCrusade_Main;

        } // namespace SelectCrusade_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
