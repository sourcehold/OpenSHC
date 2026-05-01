/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Units/States/UnitState_Fletcher.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_Fletcher {

                USF_WAITING = 0, // 0x00000000
                USF_GOING_TO_GET_SUPPLIES = 1, // 0x00000001
                USF_RETURNING_WITH_SUPPLIES = 2, // 0x00000002
                USF_GOING_TO_WORKPLACE = 3, // 0x00000003
                USF_WORKING_4 = 4, // 0x00000004
                USF_WORKING_5 = 5, // 0x00000005
                USF_AWAITING_STORE_SPACE = 6, // 0x00000006
                USF_TAKING_GOODS_TO_STORE = 7, // 0x00000007
                USF_WAITING_OR_RESTING = 8, // 0x00000008
                USF_ATTACKING = 106 // 0x0000006A

            } UnitState_Fletcher;

            static_assert_cpp98_obj(sizeof(UnitState_Fletcher) == 4, UnitState_Fletcher);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
