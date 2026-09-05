/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/General.hpp'
*/

#pragma once

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace General {

            using OpenSHC::Commands::MappersEnum;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            void __cdecl MenuItemRenderFunction_General_MenuMiniMap(int param_1, ...);

            void __cdecl MenuItemRenderFunction_General_AdvancedGameOptions(int param_1, ...);

            void __cdecl MenuItemActionHandler_General_AdvancedGameOptions(int param_1, ...);

            void __cdecl MenuItemActionHandler_General_Unknown2(int param_1, ...);

            void __cdecl MenuItemFunction_General_Unknown(int param_1, ...);

            void __cdecl MenuItemActionHandler_General_ToolbarButtonPressed(MappersEnum buttonID);

            void __cdecl MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface();

            void __cdecl MenuItemActionHandler_General_TextInputDisplay(int param_1, ...);

            void __cdecl MenuItemRenderFunction_General_TextInputDisplay(int param_1, ...);

            void __cdecl MenuItemRenderFunction_General_GameOptionsTextButton(int param_1, ...);

            void __cdecl MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk(int param_1, ...);

            void __cdecl MenuItemActionHandler_General_EventSlider(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemRenderFunction_General_EventSlider(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged);

            void __cdecl MenuItemActionHandler_General_MessageScrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemRenderFunction_General_Scrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

            void __cdecl MenuItemRenderFunction_General_MessageScrollbarUpDown(int param_1, ...);

            void __cdecl MenuItemRenderFunction_General_CreateEventCallbackFunction(int param_1, ...);

            void __cdecl MenuItemRenderFunction_General_EventButtonAndData(int param_1, ...);

            void __cdecl MenuItemActionHandler_General_CreateEventCallbackFunction(int param_1, ...);

            void __cdecl MenuItemRenderFunction_General_CrusadeMapAndEndscreen(int param_1, ...);

            void __cdecl MenuItemActionHandler_General_DisplayConditionalText(int param_1, ...);

            void __cdecl MenuItemActionHandler_General_RemoveConditionalTextOrReleaseHoverUnk(int param_1, ...);

        } // namespace General
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
