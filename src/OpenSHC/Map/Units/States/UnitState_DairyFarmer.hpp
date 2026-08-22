/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/States/UnitState_DairyFarmer.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_DairyFarmer {

                USDF_WAITING_0 = 0, // 0x00000000
                USDF_WAITING_1 = 1, // 0x00000001
                USDF_GOING_TO_WORKPLACE = 2, // 0x00000002
                USDF_WORKING = 3, // 0x00000003
                USDF_AWAIT_STORE_SPACE = 4, // 0x00000004
                USDF_TAKING_GOODS_TO_STORE = 5, // 0x00000005
                USDF_ATTACKING = 106 // 0x0000006A

            } UnitState_DairyFarmer;

            static_assert_cpp98_obj(sizeof(UnitState_DairyFarmer) == 4, UnitState_DairyFarmer);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
