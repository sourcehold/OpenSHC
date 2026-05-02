/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game.func.hpp'
*/

#pragma once

#include "OpenSHC/Game.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Game_Func {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int value), false, Address::SHC_3BB0A8C1_0x0044AA70, &OpenSHC::Game::UpdateUnitValueLoss)
    UpdateUnitValueLoss;

    MACRO_FUNCTION_RESOLVER(int(__cdecl*)(int larger, int smaller), false, Address::SHC_3BB0A8C1_0x0044AAB0,
        &OpenSHC::Game::RelativeValueForGenie)
    RelativeValueForGenie;

    MACRO_FUNCTION_RESOLVER(BOOLEnum(__cdecl*)(undefined4 actionType, int actionParam), false,
        Address::SHC_3BB0A8C1_0x004BD800, &OpenSHC::Game::Tutorial_IsActionAllowed)
    Tutorial_IsActionAllowed;

} // namespace Game_Func
} // namespace OpenSHC
