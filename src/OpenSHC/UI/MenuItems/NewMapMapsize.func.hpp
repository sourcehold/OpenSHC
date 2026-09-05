/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/NewMapMapsize.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/NewMapMapsize.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace NewMapMapsize_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042F7F0,
                &OpenSHC::UI::MenuItems::NewMapMapsize::MenuItemRenderFunction_NewMapMapsize_Buttons)
            MenuItemRenderFunction_NewMapMapsize_Buttons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042F940,
                &OpenSHC::UI::MenuItems::NewMapMapsize::MenuItemActionHandler_NewMapMapsize_Buttons)
            MenuItemActionHandler_NewMapMapsize_Buttons;

        } // namespace NewMapMapsize_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
