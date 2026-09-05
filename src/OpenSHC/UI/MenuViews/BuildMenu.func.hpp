/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/BuildMenu.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuViews/BuildMenu.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace BuildMenu_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00431A90,
                &OpenSHC::UI::MenuViews::BuildMenu::MenuView_BuildMenu_Prepare)
            MenuView_BuildMenu_Prepare;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00431B60,
                &OpenSHC::UI::MenuViews::BuildMenu::MenuView_BuildMenu_DoInitial)
            MenuView_BuildMenu_DoInitial;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00433030,
                &OpenSHC::UI::MenuViews::BuildMenu::MenuView_BuildMenu_DoEveryFrame)
            MenuView_BuildMenu_DoEveryFrame;

        } // namespace BuildMenu_Func
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
