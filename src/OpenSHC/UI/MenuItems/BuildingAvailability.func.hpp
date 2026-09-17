/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/BuildingAvailability.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/BuildingAvailability.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAvailability_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BB0D0,
                &OpenSHC::UI::MenuItems::BuildingAvailability::MenuItemRenderFunction_BuildingAvailability_Buttons)
            MenuItemRenderFunction_BuildingAvailability_Buttons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BB2C0,
                &OpenSHC::UI::MenuItems::BuildingAvailability::MenuItemActionHandler_BuildingAvailability_Buttons)
            MenuItemActionHandler_BuildingAvailability_Buttons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BB3E0,
                &OpenSHC::UI::MenuItems::BuildingAvailability::MenuItemRenderFunction_BuildingAvailability_TableRows)
            MenuItemRenderFunction_BuildingAvailability_TableRows;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x004BB480,
                &OpenSHC::UI::MenuItems::BuildingAvailability::MenuItemActionHandler_BuildingAvailability_Scrollbar)
            MenuItemActionHandler_BuildingAvailability_Scrollbar;

        } // namespace BuildingAvailability_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
