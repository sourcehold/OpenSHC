/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/AlliesOrder.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/AlliesOrder.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace AlliesOrder_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004AD480,
                &OpenSHC::UI::MenuItems::AlliesOrder::MenuItemRenderFunction_AlliesOrder_Main)
            MenuItemRenderFunction_AlliesOrder_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004B1410,
                &OpenSHC::UI::MenuItems::AlliesOrder::MenuItemActionHandler_AlliesOrder_Main)
            MenuItemActionHandler_AlliesOrder_Main;

        } // namespace AlliesOrder_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
