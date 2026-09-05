/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/CrusadeMissionIntro.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/CrusadeMissionIntro.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace CrusadeMissionIntro_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004D8BB0,
                &OpenSHC::UI::MenuItems::CrusadeMissionIntro::MenuItemRenderFunction_CrusadeMissionIntro_Main)
            MenuItemRenderFunction_CrusadeMissionIntro_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004D8C10,
                &OpenSHC::UI::MenuItems::CrusadeMissionIntro::MenuItemActionHandler_CrusadeMissionIntro_Main)
            MenuItemActionHandler_CrusadeMissionIntro_Main;

        } // namespace CrusadeMissionIntro_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
