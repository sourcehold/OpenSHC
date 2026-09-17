/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/SendReceiveMap.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/SendReceiveMap.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SendReceiveMap_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004AC440,
                &OpenSHC::UI::MenuItems::SendReceiveMap::MenuItemRenderFunction_SendReceiveMap_Main)
            MenuItemRenderFunction_SendReceiveMap_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004B10D0,
                &OpenSHC::UI::MenuItems::SendReceiveMap::MenuItemActionHandler_SendReceiveMap_Main)
            MenuItemActionHandler_SendReceiveMap_Main;

        } // namespace SendReceiveMap_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
