/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/States/UnitState_HorseArcher.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_HorseArcher {

                USHA_IDLE = 1, // 0x00000001
                USHA_MOVE_TO_DESTINATION = 101, // 0x00000065
                USHA_MELEE = 106, // 0x0000006A
                USHA_MELEE_ATTACK_BUILDING = 107 // 0x0000006B

            } UnitState_HorseArcher;

            static_assert_cpp98_obj(sizeof(UnitState_HorseArcher) == 4, UnitState_HorseArcher);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
