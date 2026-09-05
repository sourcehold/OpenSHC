/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/ScenarioDescription.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuViews/ScenarioDescription.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace ScenarioDescription_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DD100,
                &OpenSHC::UI::MenuViews::ScenarioDescription::MenuView_ScenarioDescription_Prepare)
            MenuView_ScenarioDescription_Prepare;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DD300,
                &OpenSHC::UI::MenuViews::ScenarioDescription::MenuView_ScenarioDescription_DoInitial)
            MenuView_ScenarioDescription_DoInitial;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DD350,
                &OpenSHC::UI::MenuViews::ScenarioDescription::MenuView_ScenarioDescription_DoEveryFrame)
            MenuView_ScenarioDescription_DoEveryFrame;

        } // namespace ScenarioDescription_Func
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
