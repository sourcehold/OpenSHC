/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/NewInvasion.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/NewInvasion.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace NewInvasion_Func {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int unitTypeMenuID, ...), false, Address::SHC_3BB0A8C1_0x004B9110,
                &OpenSHC::UI::MenuItems::NewInvasion::MenuItemActionHandler_NewInvasion_UnitButtons)
            MenuItemActionHandler_NewInvasion_UnitButtons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004B92D0,
                &OpenSHC::UI::MenuItems::NewInvasion::MenuItemRenderFunction_NewInvasion_UnitButtons)
            MenuItemRenderFunction_NewInvasion_UnitButtons;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x004B94A0,
                &OpenSHC::UI::MenuItems::NewInvasion::MenuItemActionHandler_NewInvasion_RepeatSlider)
            MenuItemActionHandler_NewInvasion_RepeatSlider;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int thumbXPos, int sliderValue, int thumbWidth, BOOLEnum isDragged), false,
                Address::SHC_3BB0A8C1_0x004B9530,
                &OpenSHC::UI::MenuItems::NewInvasion::MenuItemRenderFunction_NewInvasion_RepeatSlider)
            MenuItemRenderFunction_NewInvasion_RepeatSlider;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BF760,
                &OpenSHC::UI::MenuItems::NewInvasion::MenuItemActionHandler_NewInvasion_Buttons)
            MenuItemActionHandler_NewInvasion_Buttons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BFA60,
                &OpenSHC::UI::MenuItems::NewInvasion::MenuItemRenderFunction_NewInvasion_Buttons)
            MenuItemRenderFunction_NewInvasion_Buttons;

        } // namespace NewInvasion_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
