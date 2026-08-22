/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/States/UnitState_HopsFarmer.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_HopsFarmer {

                USHF_WAITING_0 = 0, // 0x00000000
                USHF_WAITING_1 = 1, // 0x00000001
                USHF_GOING_TO_WORKPLACE = 2, // 0x00000002
                USHF_WORKING_3 = 3, // 0x00000003
                USHF_WORKING_4 = 4, // 0x00000004
                USHF_WORKING_5 = 5, // 0x00000005
                USHF_WORKING_6 = 6, // 0x00000006
                USHF_AWAIT_STORE_SPACE = 7, // 0x00000007
                USHF_TAKING_GOODS_TO_STORE = 8, // 0x00000008
                USHF_ATTACKING = 106 // 0x0000006A

            } UnitState_HopsFarmer;

            static_assert_cpp98_obj(sizeof(UnitState_HopsFarmer) == 4, UnitState_HopsFarmer);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
