/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/DebugDataMousePointing.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuModals/DebugDataMousePointing.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace DebugDataMousePointing_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
                Address::SHC_3BB0A8C1_0x004AAAC0,
                &OpenSHC::UI::MenuModals::DebugDataMousePointing::MenuModalRenderFunction_DebugDataMousePointing)
            MenuModalRenderFunction_DebugDataMousePointing;

        } // namespace DebugDataMousePointing_Func
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
