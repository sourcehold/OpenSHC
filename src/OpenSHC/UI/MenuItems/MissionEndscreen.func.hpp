/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/MissionEndscreen.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/MissionEndscreen.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace MissionEndscreen_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004D6BC0,
                &OpenSHC::UI::MenuItems::MissionEndscreen::MenuItemActionHandler_MissionEndscreen_Main)
            MenuItemActionHandler_MissionEndscreen_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004D6D20,
                &OpenSHC::UI::MenuItems::MissionEndscreen::MenuItemRenderFunction_MissionEndscreen_Main)
            MenuItemRenderFunction_MissionEndscreen_Main;

        } // namespace MissionEndscreen_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
