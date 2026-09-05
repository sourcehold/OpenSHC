/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuViews/MissionFinishedTransition.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuViews/MissionFinishedTransition.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace MissionFinishedTransition_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DC500,
                &OpenSHC::UI::MenuViews::MissionFinishedTransition::MenuView_MissionFinishedTransition_DoEveryFrame)
            MenuView_MissionFinishedTransition_DoEveryFrame;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004E1B30,
                &OpenSHC::UI::MenuViews::MissionFinishedTransition::MenuView_MissionFinishedTransition_Prepare)
            MenuView_MissionFinishedTransition_Prepare;

        } // namespace MissionFinishedTransition_Func
    } // namespace MenuViews
} // namespace UI
} // namespace OpenSHC
