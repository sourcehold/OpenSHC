/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/CrusadeEndscreen.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuViews/CrusadeEndscreen.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace CrusadeEndscreen_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004D91D0,
                &OpenSHC::UI::MenuViews::CrusadeEndscreen::MenuView_CrusadeEndscreen_DoInitial)
            MenuView_CrusadeEndscreen_DoInitial;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DF2E0,
                &OpenSHC::UI::MenuViews::CrusadeEndscreen::MenuView_CrusadeEndscreen_Prepare)
            MenuView_CrusadeEndscreen_Prepare;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004E1F50,
                &OpenSHC::UI::MenuViews::CrusadeEndscreen::MenuView_CrusadeEndscreen_DoEveryFrame)
            MenuView_CrusadeEndscreen_DoEveryFrame;

        } // namespace CrusadeEndscreen_Func
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
