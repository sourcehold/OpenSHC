/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/LobbyMenu.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/LobbyMenu.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace LobbyMenu_Func {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00427740,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemRenderFunction_LobbyMenu_MapSelectHeader)
            MenuItemRenderFunction_LobbyMenu_MapSelectHeader;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00427810,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemRenderFunction_LobbyMenu_PlayerListAndNpcButtons)
            MenuItemRenderFunction_LobbyMenu_PlayerListAndNpcButtons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004285F0,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemRenderFunction_LobbyMenu_MapDesc)
            MenuItemRenderFunction_LobbyMenu_MapDesc;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x00428980,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemActionHandler_LobbyMenu_MapDescScrollbar)
            MenuItemActionHandler_LobbyMenu_MapDescScrollbar;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged), false,
                Address::SHC_3BB0A8C1_0x00428A60,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemRenderFunction_LobbyMenu_MapDescScrollbar)
            MenuItemRenderFunction_LobbyMenu_MapDescScrollbar;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042A480,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemRenderFunction_LobbyMenu_SkirmishTypeAndBalance)
            MenuItemRenderFunction_LobbyMenu_SkirmishTypeAndBalance;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042A840,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemActionHandler_LobbyMenu_SkirmishTypeAndBalance)
            MenuItemActionHandler_LobbyMenu_SkirmishTypeAndBalance;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042AC40,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemRenderFunction_LobbyMenu_Unknown)
            MenuItemRenderFunction_LobbyMenu_Unknown;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042AC90,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemRenderFunction_LobbyMenu_ChatBox)
            MenuItemRenderFunction_LobbyMenu_ChatBox;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042AE90,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemRenderFunction_LobbyMenu_NonBoxedButtons)
            MenuItemRenderFunction_LobbyMenu_NonBoxedButtons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042B470,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemActionHandler_LobbyMenu_MapSelectTable)
            MenuItemActionHandler_LobbyMenu_MapSelectTable;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0042B4C0,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemRenderFunction_LobbyMenu_MapSelectTable)
            MenuItemRenderFunction_LobbyMenu_MapSelectTable;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x0042B7B0,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemActionHandler_LobbyMenu_MapSelectScrollbar)
            MenuItemActionHandler_LobbyMenu_MapSelectScrollbar;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged), false,
                Address::SHC_3BB0A8C1_0x0042B8F0,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemRenderFunction_LobbyMenu_MapSelectScrollbar)
            MenuItemRenderFunction_LobbyMenu_MapSelectScrollbar;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00440A50,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemActionHandler_LobbyMenu_MapSelectHeader)
            MenuItemActionHandler_LobbyMenu_MapSelectHeader;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00440E50,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemActionHandler_LobbyMenu_PlayerListAndNpcButtons)
            MenuItemActionHandler_LobbyMenu_PlayerListAndNpcButtons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00442640,
                &OpenSHC::UI::MenuItems::LobbyMenu::MenuItemActionHandler_LobbyMenu_LobbyscreenStartButtonClick)
            MenuItemActionHandler_LobbyMenu_LobbyscreenStartButtonClick;

        } // namespace LobbyMenu_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
