/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/MapEditorProperties.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace MapEditorProperties {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            void __cdecl MenuItemRenderFunction_MapEditorProperties_MainButtons(int param_1, ...);

            void __cdecl MenuItemRenderFunction_MapEditorProperties_MapDescriptionBox(int param_1, ...);

            void __cdecl MenuItemActionHandler_MapEditorProperties_MapDescriptionBox();

            void __cdecl MenuItemActionHandler_MapEditorProperties_MapDescriptionScrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemRenderFunction_MapEditorProperties_MapDescriptionScrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

            void __cdecl MenuItemActionHandler_MapEditorProperties_MainButtons(int param_1, ...);

        } // namespace MapEditorProperties
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
