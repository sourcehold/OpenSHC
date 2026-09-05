/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/AlliesSendAndRequestGoods.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/AlliesSendAndRequestGoods.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace AlliesSendAndRequestGoods_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int actionParam, ...), false, Address::SHC_3BB0A8C1_0x004AD920,
                &OpenSHC::UI::MenuItems::AlliesSendAndRequestGoods::
                    MenuItemRenderFunction_AlliesSendAndRequestGoods_Main)
            MenuItemRenderFunction_AlliesSendAndRequestGoods_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004B14C0,
                &OpenSHC::UI::MenuItems::AlliesSendAndRequestGoods::
                    MenuItemActionHandler_AlliesSendAndRequestGoods_Main)
            MenuItemActionHandler_AlliesSendAndRequestGoods_Main;

        } // namespace AlliesSendAndRequestGoods_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
