/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/TutorialBox.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuModals/TutorialBox.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace TutorialBox_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
                Address::SHC_3BB0A8C1_0x004ABD10,
                &OpenSHC::UI::MenuModals::TutorialBox::MenuModalRenderFunction_TutorialBox_Thunk)
            MenuModalRenderFunction_TutorialBox_Thunk;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
                Address::SHC_3BB0A8C1_0x004BCBA0,
                &OpenSHC::UI::MenuModals::TutorialBox::MenuModalRenderFunction_TutorialBox)
            MenuModalRenderFunction_TutorialBox;

        } // namespace TutorialBox_Func
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
