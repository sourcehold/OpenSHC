/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/OverlaySlider.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/OverlaySlider.hpp"

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace OverlaySlider_Func {

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x004AA600,
                &OpenSHC::UI::MenuItems::OverlaySlider::MenuItemActionHandler_OverlaySlider_Slider)
            MenuItemActionHandler_OverlaySlider_Slider;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged), false,
                Address::SHC_3BB0A8C1_0x004AA800,
                &OpenSHC::UI::MenuItems::OverlaySlider::MenuItemRenderFunction_OverlaySlider_Slider)
            MenuItemRenderFunction_OverlaySlider_Slider;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004B0F70,
                &OpenSHC::UI::MenuItems::OverlaySlider::MenuItemActionHandler_OverlaySlider_Deselect)
            MenuItemActionHandler_OverlaySlider_Deselect;

        } // namespace OverlaySlider_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
