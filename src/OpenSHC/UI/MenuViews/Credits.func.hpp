/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/Credits.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuViews/Credits.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace Credits_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004261E0,
                &OpenSHC::UI::MenuViews::Credits::MenuView_Credits_Prepare)
            MenuView_Credits_Prepare;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004262B0,
                &OpenSHC::UI::MenuViews::Credits::MenuView_Credits_DoInitial)
            MenuView_Credits_DoInitial;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00426340,
                &OpenSHC::UI::MenuViews::Credits::MenuView_Credits_DoEveryFrame)
            MenuView_Credits_DoEveryFrame;

        } // namespace Credits_Func
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
