/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/RankingGames.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/RankingGames.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace RankingGames_Func {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004D9730,
                &OpenSHC::UI::MenuItems::RankingGames::MenuItemActionHandler_RankingGames_Main)
            MenuItemActionHandler_RankingGames_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004D99F0,
                &OpenSHC::UI::MenuItems::RankingGames::MenuItemRenderFunction_RankingGames_Main)
            MenuItemRenderFunction_RankingGames_Main;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x004D9B30,
                &OpenSHC::UI::MenuItems::RankingGames::MenuItemActionHandler_RankingGames_Scrollbar)
            MenuItemActionHandler_RankingGames_Scrollbar;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged), false,
                Address::SHC_3BB0A8C1_0x004D9C10,
                &OpenSHC::UI::MenuItems::RankingGames::MenuItemRenderFunction_RankingGames_Scrollbar)
            MenuItemRenderFunction_RankingGames_Scrollbar;

        } // namespace RankingGames_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
