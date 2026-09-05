/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/IntroVideo.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuViews/IntroVideo.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace IntroVideo_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00424A50,
                &OpenSHC::UI::MenuViews::IntroVideo::MenuView_IntroVideo_Prepare)
            MenuView_IntroVideo_Prepare;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00424AD0,
                &OpenSHC::UI::MenuViews::IntroVideo::MenuView_IntroVideo_DoEveryFrame)
            MenuView_IntroVideo_DoEveryFrame;

        } // namespace IntroVideo_Func
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
