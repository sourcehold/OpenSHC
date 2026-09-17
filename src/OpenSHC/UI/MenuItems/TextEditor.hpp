/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/TextEditor.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace TextEditor {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            void __cdecl MenuItemRenderFunction_TextEditor_Buttons(int param_1, ...);

            void __cdecl MenuItemActionHandler_TextEditor_Scrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemRenderFunction_TextEditor_Scrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

            void __cdecl MenuItemActionHandler_TextEditor_TextInputRelatedUnk();

            void __cdecl MenuItemActionHandler_TextEditor_Buttons(int param_1, ...);

        } // namespace TextEditor
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
