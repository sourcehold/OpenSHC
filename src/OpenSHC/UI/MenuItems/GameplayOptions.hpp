/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/GameplayOptions.hpp'
*/

#pragma once

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace GameplayOptions {

            void __cdecl MenuItemRenderFunction_GameplayOptions_Buttons(int param_1, ...);

            void __cdecl MenuItemActionHandler_GameplayOptions_SpeedSlider(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemRenderFunction_GameplayOptions_SpeedSlider(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged);

            void __cdecl MenuItemActionHandler_GameplayOptions_Buttons(int param_1, ...);

        } // namespace GameplayOptions
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
