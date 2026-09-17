/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/TraderSettings.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/TraderSettings.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace TraderSettings_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BA780,
                &OpenSHC::UI::MenuItems::TraderSettings::MenuItemActionHandler_TraderSettings)
            MenuItemActionHandler_TraderSettings;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004C1070,
                &OpenSHC::UI::MenuItems::TraderSettings::MenuItemRenderFunction_TraderSettings)
            MenuItemRenderFunction_TraderSettings;

        } // namespace TraderSettings_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
