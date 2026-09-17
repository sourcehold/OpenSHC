/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/DisableArabTroops.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/DisableArabTroops.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace DisableArabTroops_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BB650,
                &OpenSHC::UI::MenuItems::DisableArabTroops::MenuItemActionHandler_DisableArabTroops_Main)
            MenuItemActionHandler_DisableArabTroops_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BB680,
                &OpenSHC::UI::MenuItems::DisableArabTroops::MenuItemRenderFunction_DisableArabTroops_Main)
            MenuItemRenderFunction_DisableArabTroops_Main;

        } // namespace DisableArabTroops_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
