/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/States/UnitState_Hunter.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_Hunter {

                WAITING_0 = 0, // 0x00000000
                HUNTING_1 = 1, // 0x00000001
                RETURNING_WITH_KILL = 2, // 0x00000002
                WORKING_3 = 3, // 0x00000003
                AWAITING_STORE_SPACE = 4, // 0x00000004
                TAKING_GOODS_TO_STORE = 5, // 0x00000005
                GOING_TO_WORKPLACE = 6, // 0x00000006
                RESTING_7 = 7, // 0x00000007
                WAITING_8 = 8, // 0x00000008
                STALKING_AND_FIGHTING = 9, // 0x00000009
                HUNTING_AND_FIGHTING = 10, // 0x0000000A
                HUNTING_11 = 11, // 0x0000000B
                ATTACKING = 106 // 0x0000006A

            } UnitState_Hunter;

            static_assert_cpp98_obj(sizeof(UnitState_Hunter) == 4, UnitState_Hunter);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
