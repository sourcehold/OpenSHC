/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/TriggerInvasion.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/TriggerInvasion.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace TriggerInvasion_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BBD90,
                &OpenSHC::UI::MenuItems::TriggerInvasion::MenuItemActionHandler_TriggerInvasion_Main)
            MenuItemActionHandler_TriggerInvasion_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BBF40,
                &OpenSHC::UI::MenuItems::TriggerInvasion::MenuItemRenderFunction_TriggerInvasion_Main)
            MenuItemRenderFunction_TriggerInvasion_Main;

        } // namespace TriggerInvasion_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
