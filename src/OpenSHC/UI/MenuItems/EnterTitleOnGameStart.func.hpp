/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/EnterTitleOnGameStart.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/EnterTitleOnGameStart.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace EnterTitleOnGameStart_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00491C20,
                &OpenSHC::UI::MenuItems::EnterTitleOnGameStart::MenuItemActionHandler_EnterTitleOnGameStart_Button)
            MenuItemActionHandler_EnterTitleOnGameStart_Button;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00491C50,
                &OpenSHC::UI::MenuItems::EnterTitleOnGameStart::MenuItemRenderFunction_EnterTitleOnGameStart_Button)
            MenuItemRenderFunction_EnterTitleOnGameStart_Button;

        } // namespace EnterTitleOnGameStart_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
