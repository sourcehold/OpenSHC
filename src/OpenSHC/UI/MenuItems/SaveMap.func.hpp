/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/SaveMap.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/SaveMap.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SaveMap_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004932A0,
                &OpenSHC::UI::MenuItems::SaveMap::MenuItemActionHandler_SaveMap_TableContent)
            MenuItemActionHandler_SaveMap_TableContent;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004932E0,
                &OpenSHC::UI::MenuItems::SaveMap::MenuItemRenderFunction_SaveMap_InputTextDisplay)
            MenuItemRenderFunction_SaveMap_InputTextDisplay;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00494920,
                &OpenSHC::UI::MenuItems::SaveMap::MenuItemActionHandler_SaveMap_ReturnKeySave)
            MenuItemActionHandler_SaveMap_ReturnKeySave;

        } // namespace SaveMap_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
