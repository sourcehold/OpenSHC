/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/States/UnitState_FireThrower.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_FireThrower {

                USFT_THROW_PREPARE = 4, // 0x00000004
                USFT_THROWING = 5, // 0x00000005
                USFT_THROWN = 6, // 0x00000006
                USFT_IDLE = 11 // 0x0000000B

            } UnitState_FireThrower;

            static_assert_cpp98_obj(sizeof(UnitState_FireThrower) == 4, UnitState_FireThrower);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
