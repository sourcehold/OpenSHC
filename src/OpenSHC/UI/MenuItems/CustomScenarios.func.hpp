/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/CustomScenarios.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/CustomScenarios.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace CustomScenarios_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00426060,
                &OpenSHC::UI::MenuItems::CustomScenarios::MenuItemRenderFunction_CustomScenarios_Main)
            MenuItemRenderFunction_CustomScenarios_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00440770,
                &OpenSHC::UI::MenuItems::CustomScenarios::MenuItemActionHandler_CustomScenarios_Main)
            MenuItemActionHandler_CustomScenarios_Main;

        } // namespace CustomScenarios_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
