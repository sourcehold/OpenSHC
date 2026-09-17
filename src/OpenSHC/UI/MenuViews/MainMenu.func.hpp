/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/MainMenu.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuViews/MainMenu.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace MainMenu_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00424C40,
                &OpenSHC::UI::MenuViews::MainMenu::MenuView_MainMenu_Prepare)
            MenuView_MainMenu_Prepare;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00424CD0,
                &OpenSHC::UI::MenuViews::MainMenu::MenuView_MainMenu_DoInitial)
            MenuView_MainMenu_DoInitial;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00424DA0,
                &OpenSHC::UI::MenuViews::MainMenu::MenuView_MainMenu_DoEveryFrame)
            MenuView_MainMenu_DoEveryFrame;

        } // namespace MainMenu_Func
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
