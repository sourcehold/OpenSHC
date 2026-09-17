/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/SinglePlayerMapChoice.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SinglePlayerMapChoice {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            void __cdecl MenuItemRenderFunction_SingleplayerMapChoice_ButtonsAndHands(int param_1, ...);

            void __cdecl MenuItemActionHandler_SingleplayerMapChoice_ButtonsAndHands(int param_1, ...);

            void __cdecl MenuItemRenderFunction_SingleplayerMapChoice_MapTable(int param_1, ...);

            void __cdecl MenuItemRenderFunction_SingleplayerMapChoice_MapTableHeader(int param_1, ...);

            void __cdecl MenuItemRenderFunction_SingleplayerMapChoice_Scrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

            void __cdecl MenuItemActionHandler_SingleplayerMapChoice_MapTable(int param_1, ...);

            void __cdecl MenuItemActionHandler_SingleplayerMapChoice_Scrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemActionHandler_SingleplayerMapChoice_MapTableHeader(int param_1, ...);

        } // namespace SinglePlayerMapChoice
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
