/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/LobbyMenu.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace LobbyMenu {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            void __cdecl MenuItemRenderFunction_LobbyMenu_MapSelectHeader(int param_1, ...);

            void __cdecl MenuItemRenderFunction_LobbyMenu_PlayerListAndNpcButtons(int param_1, ...);

            void __cdecl MenuItemRenderFunction_LobbyMenu_MapDesc(int param_1, ...);

            void __cdecl MenuItemActionHandler_LobbyMenu_MapDescScrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemRenderFunction_LobbyMenu_MapDescScrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

            void __cdecl MenuItemRenderFunction_LobbyMenu_SkirmishTypeAndBalance(int param_1, ...);

            void __cdecl MenuItemActionHandler_LobbyMenu_SkirmishTypeAndBalance(int param_1, ...);

            void __cdecl MenuItemRenderFunction_LobbyMenu_Unknown(int param_1, ...);

            void __cdecl MenuItemRenderFunction_LobbyMenu_ChatBox(int param_1, ...);

            void __cdecl MenuItemRenderFunction_LobbyMenu_NonBoxedButtons(int param_1, ...);

            void __cdecl MenuItemActionHandler_LobbyMenu_MapSelectTable(int param_1, ...);

            void __cdecl MenuItemRenderFunction_LobbyMenu_MapSelectTable(int param_1, ...);

            void __cdecl MenuItemActionHandler_LobbyMenu_MapSelectScrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemRenderFunction_LobbyMenu_MapSelectScrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

            void __cdecl MenuItemActionHandler_LobbyMenu_MapSelectHeader(int param_1, ...);

            void __cdecl MenuItemActionHandler_LobbyMenu_PlayerListAndNpcButtons(int param_1, ...);

            void __cdecl MenuItemActionHandler_LobbyMenu_LobbyscreenStartButtonClick(int param_1, ...);

        } // namespace LobbyMenu
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
