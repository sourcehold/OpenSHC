/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/CustomScenarios.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuViews/CustomScenarios.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace CustomScenarios_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00425EA0,
                &OpenSHC::UI::MenuViews::CustomScenarios::MenuView_CustomScenarios_Prepare)
            MenuView_CustomScenarios_Prepare;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00425FF0,
                &OpenSHC::UI::MenuViews::CustomScenarios::MenuView_CustomScenarios_DoEveryFrame)
            MenuView_CustomScenarios_DoEveryFrame;

        } // namespace CustomScenarios_Func
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
