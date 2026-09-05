/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/GameplayOptions.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/GameplayOptions.hpp"

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace GameplayOptions_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00491EB0,
                &OpenSHC::UI::MenuItems::GameplayOptions::MenuItemRenderFunction_GameplayOptions_Buttons)
            MenuItemRenderFunction_GameplayOptions_Buttons;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x00491FD0,
                &OpenSHC::UI::MenuItems::GameplayOptions::MenuItemActionHandler_GameplayOptions_SpeedSlider)
            MenuItemActionHandler_GameplayOptions_SpeedSlider;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged), false,
                Address::SHC_3BB0A8C1_0x00492080,
                &OpenSHC::UI::MenuItems::GameplayOptions::MenuItemRenderFunction_GameplayOptions_SpeedSlider)
            MenuItemRenderFunction_GameplayOptions_SpeedSlider;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00493D80,
                &OpenSHC::UI::MenuItems::GameplayOptions::MenuItemActionHandler_GameplayOptions_Buttons)
            MenuItemActionHandler_GameplayOptions_Buttons;

        } // namespace GameplayOptions_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
