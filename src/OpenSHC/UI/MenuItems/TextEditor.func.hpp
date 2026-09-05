/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/TextEditor.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/TextEditor.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace TextEditor_Func {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0045DE40,
                &OpenSHC::UI::MenuItems::TextEditor::MenuItemRenderFunction_TextEditor_Buttons)
            MenuItemRenderFunction_TextEditor_Buttons;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x0045EDF0,
                &OpenSHC::UI::MenuItems::TextEditor::MenuItemActionHandler_TextEditor_Scrollbar)
            MenuItemActionHandler_TextEditor_Scrollbar;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged), false,
                Address::SHC_3BB0A8C1_0x0045EF90,
                &OpenSHC::UI::MenuItems::TextEditor::MenuItemRenderFunction_TextEditor_Scrollbar)
            MenuItemRenderFunction_TextEditor_Scrollbar;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00461570,
                &OpenSHC::UI::MenuItems::TextEditor::MenuItemActionHandler_TextEditor_TextInputRelatedUnk)
            MenuItemActionHandler_TextEditor_TextInputRelatedUnk;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00462340,
                &OpenSHC::UI::MenuItems::TextEditor::MenuItemActionHandler_TextEditor_Buttons)
            MenuItemActionHandler_TextEditor_Buttons;

        } // namespace TextEditor_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
