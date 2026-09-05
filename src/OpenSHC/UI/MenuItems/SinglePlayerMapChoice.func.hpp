/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/SinglePlayerMapChoice.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/SinglePlayerMapChoice.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SinglePlayerMapChoice_Func {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042D140,
                &OpenSHC::UI::MenuItems::SinglePlayerMapChoice::
                    MenuItemRenderFunction_SingleplayerMapChoice_ButtonsAndHands)
            MenuItemRenderFunction_SingleplayerMapChoice_ButtonsAndHands;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042D640,
                &OpenSHC::UI::MenuItems::SinglePlayerMapChoice::
                    MenuItemActionHandler_SingleplayerMapChoice_ButtonsAndHands)
            MenuItemActionHandler_SingleplayerMapChoice_ButtonsAndHands;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042D9A0,
                &OpenSHC::UI::MenuItems::SinglePlayerMapChoice::MenuItemRenderFunction_SingleplayerMapChoice_MapTable)
            MenuItemRenderFunction_SingleplayerMapChoice_MapTable;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042DBB0,
                &OpenSHC::UI::MenuItems::SinglePlayerMapChoice::
                    MenuItemRenderFunction_SingleplayerMapChoice_MapTableHeader)
            MenuItemRenderFunction_SingleplayerMapChoice_MapTableHeader;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged), false,
                Address::SHC_3BB0A8C1_0x0042DC60,
                &OpenSHC::UI::MenuItems::SinglePlayerMapChoice::MenuItemRenderFunction_SingleplayerMapChoice_Scrollbar)
            MenuItemRenderFunction_SingleplayerMapChoice_Scrollbar;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00442C30,
                &OpenSHC::UI::MenuItems::SinglePlayerMapChoice::MenuItemActionHandler_SingleplayerMapChoice_MapTable)
            MenuItemActionHandler_SingleplayerMapChoice_MapTable;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x00442F40,
                &OpenSHC::UI::MenuItems::SinglePlayerMapChoice::MenuItemActionHandler_SingleplayerMapChoice_Scrollbar)
            MenuItemActionHandler_SingleplayerMapChoice_Scrollbar;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00449290,
                &OpenSHC::UI::MenuItems::SinglePlayerMapChoice::
                    MenuItemActionHandler_SingleplayerMapChoice_MapTableHeader)
            MenuItemActionHandler_SingleplayerMapChoice_MapTableHeader;

        } // namespace SinglePlayerMapChoice_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
