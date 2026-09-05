/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/SoundOptions.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/SoundMenuClickType.hpp"
#include "OpenSHC/UI/MenuItems/SoundOptions.hpp"

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SoundOptions_Func {

            using OpenSHC::UI::Enums::SoundMenuClickType;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00492690,
                &OpenSHC::UI::MenuItems::SoundOptions::MenuItemRenderFunction_SoundOptions_Buttons)
            MenuItemRenderFunction_SoundOptions_Buttons;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x00492890,
                &OpenSHC::UI::MenuItems::SoundOptions::MenuItemActionHandler_SoundOptions_VolumeSlider)
            MenuItemActionHandler_SoundOptions_VolumeSlider;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged), false,
                Address::SHC_3BB0A8C1_0x004929C0,
                &OpenSHC::UI::MenuItems::SoundOptions::MenuItemRenderFunction_SoundOptions_VolumeSlider)
            MenuItemRenderFunction_SoundOptions_VolumeSlider;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(SoundMenuClickType param_1, ...), false,
                Address::SHC_3BB0A8C1_0x004940B0,
                &OpenSHC::UI::MenuItems::SoundOptions::MenuItemActionHandler_SoundOptions_Buttons)
            MenuItemActionHandler_SoundOptions_Buttons;

        } // namespace SoundOptions_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
