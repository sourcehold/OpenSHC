/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Units/States/UnitState_Tunneler.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_Tunneler {

                UST_WAITING_0 = 0, // 0x00000000
                UST_WAITING_1 = 1, // 0x00000001
                UST_WORKING_2 = 2, // 0x00000002
                UST_WORKING_3 = 3, // 0x00000003
                UST_WAITING_4 = 4, // 0x00000004
                UST_WAITING_5 = 5, // 0x00000005
                UST_WAITING_6 = 6, // 0x00000006
                UST_MOVING = 7, // 0x00000007
                UST_WORKING_8 = 8, // 0x00000008
                UST_WORKING_9 = 9, // 0x00000009
                UST_ATTACKING = 106 // 0x0000006A

            } UnitState_Tunneler;

            static_assert_cpp98_obj(sizeof(UnitState_Tunneler) == 4, UnitState_Tunneler);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
