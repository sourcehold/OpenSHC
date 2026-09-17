/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/States/UnitState_WheatFarmer.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_WheatFarmer {

                USWF_WAITING_0 = 0, // 0x00000000
                USWF_WAITING_1 = 1, // 0x00000001
                USWF_GOING_TO_WORKPLACE = 2, // 0x00000002
                USWF_WORKING_3 = 3, // 0x00000003
                USWF_WORKING_4 = 4, // 0x00000004
                USWF_WORKING_5 = 5, // 0x00000005
                USWF_WORKING_6 = 6, // 0x00000006
                USWF_WORKING_7 = 7, // 0x00000007
                USWF_WORKING_8 = 8, // 0x00000008
                USWF_AWAITING_STORE_SPACE = 9, // 0x00000009
                USWF_TAKING_GOODS_TO_STORE = 10, // 0x0000000A
                USWF_ATTACKING = 106 // 0x0000006A

            } UnitState_WheatFarmer;

            static_assert_cpp98_obj(sizeof(UnitState_WheatFarmer) == 4, UnitState_WheatFarmer);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
