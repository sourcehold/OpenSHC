/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModals/DisableWeapon.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuModals/DisableWeapon.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace DisableWeapon_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
                Address::SHC_3BB0A8C1_0x004ABCE0,
                &OpenSHC::UI::MenuModals::DisableWeapon::MenuModalRenderFunction_DisableWeapon)
            MenuModalRenderFunction_DisableWeapon;

        } // namespace DisableWeapon_Func
    } // namespace MenuModals
} // namespace UI
} // namespace OpenSHC
