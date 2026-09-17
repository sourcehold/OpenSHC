/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/SaveLoadMap.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/SaveLoadMap.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SaveLoadMap_Func {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00492A90,
                &OpenSHC::UI::MenuItems::SaveLoadMap::MenuItemRenderFunction_SaveLoadMap_Buttons)
            MenuItemRenderFunction_SaveLoadMap_Buttons;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x00492BA0,
                &OpenSHC::UI::MenuItems::SaveLoadMap::MenuItemActionHandler_SaveLoadMap_Scrollbar)
            MenuItemActionHandler_SaveLoadMap_Scrollbar;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged), false,
                Address::SHC_3BB0A8C1_0x00492C60,
                &OpenSHC::UI::MenuItems::SaveLoadMap::MenuItemRenderFunction_SaveLoadMap_Scrollbar)
            MenuItemRenderFunction_SaveLoadMap_Scrollbar;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00492C90,
                &OpenSHC::UI::MenuItems::SaveLoadMap::MenuItemRenderFunction_SaveLoadMap_TableContent)
            MenuItemRenderFunction_SaveLoadMap_TableContent;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00492DE0,
                &OpenSHC::UI::MenuItems::SaveLoadMap::MenuItemActionHandler_SaveLoadMap_TableHeader)
            MenuItemActionHandler_SaveLoadMap_TableHeader;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00492FD0,
                &OpenSHC::UI::MenuItems::SaveLoadMap::MenuItemRenderFunction_SaveLoadMap_TableHeader)
            MenuItemRenderFunction_SaveLoadMap_TableHeader;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004943B0,
                &OpenSHC::UI::MenuItems::SaveLoadMap::MenuItemActionHandler_SaveLoadMap_Buttons)
            MenuItemActionHandler_SaveLoadMap_Buttons;

        } // namespace SaveLoadMap_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
