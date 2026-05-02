/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Game {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    void __cdecl UpdateUnitValueLoss(int value);

    int __cdecl RelativeValueForGenie(int larger, int smaller);

    BOOLEnum __cdecl Tutorial_IsActionAllowed(undefined4 actionType, int actionParam);

} // namespace Game
} // namespace OpenSHC
