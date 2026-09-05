/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/HistoricMissionSelect.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/HistoricMissionSelect.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace HistoricMissionSelect_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004269E0,
                &OpenSHC::UI::MenuItems::HistoricMissionSelect::
                    MenuItemRenderFunction_HistoricMissionSelect_MissionRows)
            MenuItemRenderFunction_HistoricMissionSelect_MissionRows;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00426B80,
                &OpenSHC::UI::MenuItems::HistoricMissionSelect::MenuItemActionHandler_HistoricMissionSelect_General)
            MenuItemActionHandler_HistoricMissionSelect_General;

        } // namespace HistoricMissionSelect_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
