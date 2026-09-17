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

                USH_WAITING_0 = 0, // 0x00000000
                USH_HUNTING_1 = 1, // 0x00000001
                USH_RETURNING_WITH_KILL = 2, // 0x00000002
                USH_WORKING_3 = 3, // 0x00000003
                USH_AWAITING_STORE_SPACE = 4, // 0x00000004
                USH_TAKING_GOODS_TO_STORE = 5, // 0x00000005
                USH_GOING_TO_WORKPLACE = 6, // 0x00000006
                USH_RESTING_7 = 7, // 0x00000007
                USH_WAITING_8 = 8, // 0x00000008
                USH_STALKING_AND_FIGHTING = 9, // 0x00000009
                USH_HUNTING_AND_FIGHTING = 10, // 0x0000000A
                USH_HUNTING_11 = 11, // 0x0000000B
                USH_ATTACKING = 106 // 0x0000006A

            } UnitState_Hunter;

            static_assert_cpp98_obj(sizeof(UnitState_Hunter) == 4, UnitState_Hunter);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
