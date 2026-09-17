/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/SoundOptions.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/SoundMenuClickType.hpp"

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SoundOptions {

            using OpenSHC::UI::Enums::SoundMenuClickType;

            void __cdecl MenuItemRenderFunction_SoundOptions_Buttons(int param_1, ...);

            void __cdecl MenuItemActionHandler_SoundOptions_VolumeSlider(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemRenderFunction_SoundOptions_VolumeSlider(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged);

            void __cdecl MenuItemActionHandler_SoundOptions_Buttons(SoundMenuClickType param_1, ...);

        } // namespace SoundOptions
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
