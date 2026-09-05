/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/MapEditorProperties.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/MapEditorProperties.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace MapEditorProperties_Func {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042E900,
                &OpenSHC::UI::MenuItems::MapEditorProperties::MenuItemRenderFunction_MapEditorProperties_MainButtons)
            MenuItemRenderFunction_MapEditorProperties_MainButtons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042EBC0,
                &OpenSHC::UI::MenuItems::MapEditorProperties::
                    MenuItemRenderFunction_MapEditorProperties_MapDescriptionBox)
            MenuItemRenderFunction_MapEditorProperties_MapDescriptionBox;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0042EDF0,
                &OpenSHC::UI::MenuItems::MapEditorProperties::
                    MenuItemActionHandler_MapEditorProperties_MapDescriptionBox)
            MenuItemActionHandler_MapEditorProperties_MapDescriptionBox;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x0042EE80,
                &OpenSHC::UI::MenuItems::MapEditorProperties::
                    MenuItemActionHandler_MapEditorProperties_MapDescriptionScrollbar)
            MenuItemActionHandler_MapEditorProperties_MapDescriptionScrollbar;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged), false,
                Address::SHC_3BB0A8C1_0x0042EF80,
                &OpenSHC::UI::MenuItems::MapEditorProperties::
                    MenuItemRenderFunction_MapEditorProperties_MapDescriptionScrollbar)
            MenuItemRenderFunction_MapEditorProperties_MapDescriptionScrollbar;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00443070,
                &OpenSHC::UI::MenuItems::MapEditorProperties::MenuItemActionHandler_MapEditorProperties_MainButtons)
            MenuItemActionHandler_MapEditorProperties_MainButtons;

        } // namespace MapEditorProperties_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
