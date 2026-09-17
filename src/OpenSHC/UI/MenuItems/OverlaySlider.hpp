/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/OverlaySlider.hpp'
*/

#pragma once

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace OverlaySlider {

            void __cdecl MenuItemActionHandler_OverlaySlider_Slider(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemRenderFunction_OverlaySlider_Slider(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged);

            void __cdecl MenuItemActionHandler_OverlaySlider_Deselect(int param_1, ...);

        } // namespace OverlaySlider
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
