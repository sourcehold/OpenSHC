/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/Allies.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/Allies.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace Allies_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004AC7A0,
                &OpenSHC::UI::MenuItems::Allies::MenuItemRenderFunction_Allies_Main)
            MenuItemRenderFunction_Allies_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004B12D0,
                &OpenSHC::UI::MenuItems::Allies::MenuItemActionHandler_Allies_Main)
            MenuItemActionHandler_Allies_Main;

        } // namespace Allies_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
