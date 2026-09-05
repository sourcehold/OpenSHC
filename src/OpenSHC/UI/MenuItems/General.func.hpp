/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/General.func.hpp'
*/

#pragma once

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/MenuItems/General.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace General_Func {

            using OpenSHC::Commands::MappersEnum;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00428150,
                &OpenSHC::UI::MenuItems::General::MenuItemRenderFunction_General_MenuMiniMap)
            MenuItemRenderFunction_General_MenuMiniMap;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00428AC0,
                &OpenSHC::UI::MenuItems::General::MenuItemRenderFunction_General_AdvancedGameOptions)
            MenuItemRenderFunction_General_AdvancedGameOptions;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00429A40,
                &OpenSHC::UI::MenuItems::General::MenuItemActionHandler_General_AdvancedGameOptions)
            MenuItemActionHandler_General_AdvancedGameOptions;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00434260,
                &OpenSHC::UI::MenuItems::General::MenuItemActionHandler_General_Unknown2)
            MenuItemActionHandler_General_Unknown2;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00440410,
                &OpenSHC::UI::MenuItems::General::MenuItemFunction_General_Unknown)
            MenuItemFunction_General_Unknown;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(MappersEnum buttonID), false, Address::SHC_3BB0A8C1_0x00444410,
                &OpenSHC::UI::MenuItems::General::MenuItemActionHandler_General_ToolbarButtonPressed)
            MenuItemActionHandler_General_ToolbarButtonPressed;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00463FF0,
                &OpenSHC::UI::MenuItems::General::
                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)
            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0047CC10,
                &OpenSHC::UI::MenuItems::General::MenuItemActionHandler_General_TextInputDisplay)
            MenuItemActionHandler_General_TextInputDisplay;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0047CCA0,
                &OpenSHC::UI::MenuItems::General::MenuItemRenderFunction_General_TextInputDisplay)
            MenuItemRenderFunction_General_TextInputDisplay;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004934F0,
                &OpenSHC::UI::MenuItems::General::MenuItemRenderFunction_General_GameOptionsTextButton)
            MenuItemRenderFunction_General_GameOptionsTextButton;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00494950,
                &OpenSHC::UI::MenuItems::General::MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk)
            MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x004B9E50,
                &OpenSHC::UI::MenuItems::General::MenuItemActionHandler_General_EventSlider)
            MenuItemActionHandler_General_EventSlider;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged), false,
                Address::SHC_3BB0A8C1_0x004BA3C0,
                &OpenSHC::UI::MenuItems::General::MenuItemRenderFunction_General_EventSlider)
            MenuItemRenderFunction_General_EventSlider;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x004BAD70,
                &OpenSHC::UI::MenuItems::General::MenuItemActionHandler_General_MessageScrollbar)
            MenuItemActionHandler_General_MessageScrollbar;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged), false,
                Address::SHC_3BB0A8C1_0x004BAE30,
                &OpenSHC::UI::MenuItems::General::MenuItemRenderFunction_General_Scrollbar)
            MenuItemRenderFunction_General_Scrollbar;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BAE80,
                &OpenSHC::UI::MenuItems::General::MenuItemRenderFunction_General_MessageScrollbarUpDown)
            MenuItemRenderFunction_General_MessageScrollbarUpDown;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BBA60,
                &OpenSHC::UI::MenuItems::General::MenuItemRenderFunction_General_CreateEventCallbackFunction)
            MenuItemRenderFunction_General_CreateEventCallbackFunction;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BFFA0,
                &OpenSHC::UI::MenuItems::General::MenuItemRenderFunction_General_EventButtonAndData)
            MenuItemRenderFunction_General_EventButtonAndData;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004C1770,
                &OpenSHC::UI::MenuItems::General::MenuItemActionHandler_General_CreateEventCallbackFunction)
            MenuItemActionHandler_General_CreateEventCallbackFunction;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004D8DF0,
                &OpenSHC::UI::MenuItems::General::MenuItemRenderFunction_General_CrusadeMapAndEndscreen)
            MenuItemRenderFunction_General_CrusadeMapAndEndscreen;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004F6A60,
                &OpenSHC::UI::MenuItems::General::MenuItemActionHandler_General_DisplayConditionalText)
            MenuItemActionHandler_General_DisplayConditionalText;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004F6A70,
                &OpenSHC::UI::MenuItems::General::MenuItemActionHandler_General_RemoveConditionalTextOrReleaseHoverUnk)
            MenuItemActionHandler_General_RemoveConditionalTextOrReleaseHoverUnk;

        } // namespace General_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
