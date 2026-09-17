/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/BuildingAndStatusMenu.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuViews/BuildingAndStatusMenu.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace BuildingAndStatusMenu_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004398B0,
                &OpenSHC::UI::MenuViews::BuildingAndStatusMenu::MenuView_BuildingAndStatusMenu_DoInitial)
            MenuView_BuildingAndStatusMenu_DoInitial;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00446C00,
                &OpenSHC::UI::MenuViews::BuildingAndStatusMenu::MenuView_BuildingAndStatusMenu_Prepare)
            MenuView_BuildingAndStatusMenu_Prepare;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004494E0,
                &OpenSHC::UI::MenuViews::BuildingAndStatusMenu::MenuView_BuildingAndStatusMenu_DoEveryFrame)
            MenuView_BuildingAndStatusMenu_DoEveryFrame;

        } // namespace BuildingAndStatusMenu_Func
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
