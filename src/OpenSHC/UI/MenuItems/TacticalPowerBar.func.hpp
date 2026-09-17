/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/TacticalPowerBar.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/TacticalPowerBar.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace TacticalPowerBar_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004D9EC0,
                &OpenSHC::UI::MenuItems::TacticalPowerBar::MenuItemRenderFunction_TacticalPowerBar_Main)
            MenuItemRenderFunction_TacticalPowerBar_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004DA050,
                &OpenSHC::UI::MenuItems::TacticalPowerBar::MenuItemActionHandler_TacticalPowerBar_Main)
            MenuItemActionHandler_TacticalPowerBar_Main;

        } // namespace TacticalPowerBar_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
