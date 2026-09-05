/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/NewInvasion.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace NewInvasion {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            void __cdecl MenuItemActionHandler_NewInvasion_UnitButtons(int unitTypeMenuID, ...);

            void __cdecl MenuItemRenderFunction_NewInvasion_UnitButtons(int param_1, ...);

            void __cdecl MenuItemActionHandler_NewInvasion_RepeatSlider(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemRenderFunction_NewInvasion_RepeatSlider(
                int param_1, int thumbXPos, int sliderValue, int thumbWidth, BOOLEnum isDragged);

            void __cdecl MenuItemActionHandler_NewInvasion_Buttons(int param_1, ...);

            void __cdecl MenuItemRenderFunction_NewInvasion_Buttons(int param_1, ...);

        } // namespace NewInvasion
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
