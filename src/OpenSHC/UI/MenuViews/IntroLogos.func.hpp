/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/IntroLogos.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuViews/IntroLogos.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace IntroLogos_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00424720,
                &OpenSHC::UI::MenuViews::IntroLogos::MenuView_IntroLogos_Prepare)
            MenuView_IntroLogos_Prepare;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00424770,
                &OpenSHC::UI::MenuViews::IntroLogos::MenuView_IntroLogos_DoInitial)
            MenuView_IntroLogos_DoInitial;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004247A0,
                &OpenSHC::UI::MenuViews::IntroLogos::MenuView_IntroLogos_DoEveryFrame)
            MenuView_IntroLogos_DoEveryFrame;

        } // namespace IntroLogos_Func
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
