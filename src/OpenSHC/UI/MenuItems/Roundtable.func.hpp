/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/Roundtable.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/Roundtable.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace Roundtable_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004AEA50,
                &OpenSHC::UI::MenuItems::Roundtable::MenuItemActionHandler_Roundtable_Main)
            MenuItemActionHandler_Roundtable_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004AEF70,
                &OpenSHC::UI::MenuItems::Roundtable::MenuItemRenderFunction_Roundtable_Main)
            MenuItemRenderFunction_Roundtable_Main;

        } // namespace Roundtable_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
