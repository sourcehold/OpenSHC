/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/GameLost.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuViews/GameLost.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace GameLost_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004D55D0,
                &OpenSHC::UI::MenuViews::GameLost::MenuView_GameLost_Prepare)
            MenuView_GameLost_Prepare;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DC9E0,
                &OpenSHC::UI::MenuViews::GameLost::MenuView_GameLost_DoEveryFrame)
            MenuView_GameLost_DoEveryFrame;

        } // namespace GameLost_Func
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
