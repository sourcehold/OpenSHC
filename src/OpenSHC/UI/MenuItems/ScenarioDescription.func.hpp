/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/ScenarioDescription.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/ScenarioDescription.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace ScenarioDescription_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004D8250,
                &OpenSHC::UI::MenuItems::ScenarioDescription::MenuItemRenderFunction_ScenarioDescription_Main)
            MenuItemRenderFunction_ScenarioDescription_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004D8570,
                &OpenSHC::UI::MenuItems::ScenarioDescription::MenuItemActionHandler_ScenarioDescription_Main)
            MenuItemActionHandler_ScenarioDescription_Main;

        } // namespace ScenarioDescription_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
