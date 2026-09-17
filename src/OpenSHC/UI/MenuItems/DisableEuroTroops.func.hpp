/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/DisableEuroTroops.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/DisableEuroTroops.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace DisableEuroTroops_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BB540,
                &OpenSHC::UI::MenuItems::DisableEuroTroops::MenuItemActionHandler_DisableEuroTroops_Main)
            MenuItemActionHandler_DisableEuroTroops_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BB570,
                &OpenSHC::UI::MenuItems::DisableEuroTroops::MenuItemRenderFunction_DisableEuroTroops_Main)
            MenuItemRenderFunction_DisableEuroTroops_Main;

        } // namespace DisableEuroTroops_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
