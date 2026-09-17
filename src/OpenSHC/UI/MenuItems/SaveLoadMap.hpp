/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/SaveLoadMap.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SaveLoadMap {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            void __cdecl MenuItemRenderFunction_SaveLoadMap_Buttons(int param_1, ...);

            void __cdecl MenuItemActionHandler_SaveLoadMap_Scrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemRenderFunction_SaveLoadMap_Scrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

            void __cdecl MenuItemRenderFunction_SaveLoadMap_TableContent(int param_1, ...);

            void __cdecl MenuItemActionHandler_SaveLoadMap_TableHeader(int param_1, ...);

            void __cdecl MenuItemRenderFunction_SaveLoadMap_TableHeader(int param_1, ...);

            void __cdecl MenuItemActionHandler_SaveLoadMap_Buttons(int param_1, ...);

        } // namespace SaveLoadMap
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
