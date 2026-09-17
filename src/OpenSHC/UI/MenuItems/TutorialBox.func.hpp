/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/TutorialBox.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/TutorialBox.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace TutorialBox_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BCEC0,
                &OpenSHC::UI::MenuItems::TutorialBox::MenuItemActionHandler_TutorialBox_Main)
            MenuItemActionHandler_TutorialBox_Main;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x004BD0F0,
                &OpenSHC::UI::MenuItems::TutorialBox::MenuItemRenderFunction_TutorialBox_Main)
            MenuItemRenderFunction_TutorialBox_Main;

        } // namespace TutorialBox_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
