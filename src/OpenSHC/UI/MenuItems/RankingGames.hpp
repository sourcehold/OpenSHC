/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/RankingGames.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace RankingGames {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            void __cdecl MenuItemActionHandler_RankingGames_Main(int param_1, ...);

            void __cdecl MenuItemRenderFunction_RankingGames_Main(int param_1, ...);

            void __cdecl MenuItemActionHandler_RankingGames_Scrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemRenderFunction_RankingGames_Scrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

        } // namespace RankingGames
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
