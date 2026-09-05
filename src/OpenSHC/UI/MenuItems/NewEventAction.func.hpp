/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/NewEventAction.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/NewEventAction.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace NewEventAction_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004B9C00,
                &OpenSHC::UI::MenuItems::NewEventAction::MenuItemActionHandler_NewEventAction_Main)
            MenuItemActionHandler_NewEventAction_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004C0860,
                &OpenSHC::UI::MenuItems::NewEventAction::MenuItemRenderFunction_NewEventAction_Main)
            MenuItemRenderFunction_NewEventAction_Main;

        } // namespace NewEventAction_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
