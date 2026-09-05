/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/ChooseRandomNumberOfEnemies.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/ChooseRandomNumberOfEnemies.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace ChooseRandomNumberOfEnemies_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00464260,
                &OpenSHC::UI::MenuItems::ChooseRandomNumberOfEnemies::
                    MenuItemRenderFunction_ChooseRandomNumberOfEnemies_Main)
            MenuItemRenderFunction_ChooseRandomNumberOfEnemies_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004B18D0,
                &OpenSHC::UI::MenuItems::ChooseRandomNumberOfEnemies::
                    MenuItemActionHandler_ChooseRandomNumberOfEnemies_Main)
            MenuItemActionHandler_ChooseRandomNumberOfEnemies_Main;

        } // namespace ChooseRandomNumberOfEnemies_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
