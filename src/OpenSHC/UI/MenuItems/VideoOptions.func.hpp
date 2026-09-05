/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/VideoOptions.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/VideoOptions.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace VideoOptions_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00492170,
                &OpenSHC::UI::MenuItems::VideoOptions::MenuItemRenderFunction_VideoOptions_Main)
            MenuItemRenderFunction_VideoOptions_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00493E20,
                &OpenSHC::UI::MenuItems::VideoOptions::MenuItemActionHandler_VideoOptions_Main)
            MenuItemActionHandler_VideoOptions_Main;

        } // namespace VideoOptions_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
