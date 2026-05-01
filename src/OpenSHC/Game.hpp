/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
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
