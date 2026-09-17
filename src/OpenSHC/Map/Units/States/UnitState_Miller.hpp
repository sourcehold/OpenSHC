/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/States/UnitState_Miller.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_Miller {

                USM_WAITING_0 = 0, // 0x00000000
                USM_WAITING_1 = 1, // 0x00000001
                USM_GOING_TO_WORKPLACE = 2, // 0x00000002
                USM_GOING_TO_GET_SUPPLIES = 3, // 0x00000003
                USM_RETURNING_WITH_SUPPLIES = 4, // 0x00000004
                USM_WORKING = 5, // 0x00000005
                USM_WAITING_6 = 6, // 0x00000006
                USM_AWAITING_STORE_SPACE = 7, // 0x00000007
                USM_TAKING_GOODS_TO_STORE = 8, // 0x00000008
                USM_ATTACKING = 106 // 0x0000006A

            } UnitState_Miller;

            static_assert_cpp98_obj(sizeof(UnitState_Miller) == 4, UnitState_Miller);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
