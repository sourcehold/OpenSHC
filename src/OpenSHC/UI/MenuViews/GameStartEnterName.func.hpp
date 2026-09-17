/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/GameStartEnterName.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuViews/GameStartEnterName.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace GameStartEnterName_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00424B10,
                &OpenSHC::UI::MenuViews::GameStartEnterName::MenuView_GameStartEnterName_DoEveryFrame)
            MenuView_GameStartEnterName_DoEveryFrame;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(void* param_1), false, Address::SHC_3BB0A8C1_0x00440560,
                &OpenSHC::UI::MenuViews::GameStartEnterName::MenuView_GameStartEnterName_Prepare)
            MenuView_GameStartEnterName_Prepare;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004406F0,
                &OpenSHC::UI::MenuViews::GameStartEnterName::MenuView_GameStartEnterName_DoInitial)
            MenuView_GameStartEnterName_DoInitial;

        } // namespace GameStartEnterName_Func
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
