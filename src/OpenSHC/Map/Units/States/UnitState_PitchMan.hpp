/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Units/States/UnitState_PitchMan.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_PitchMan {

                USPM_WAITING = 0, // 0x00000000
                USPM_WORKING = 1, // 0x00000001
                USPM_AWAITING_STORE_SPACE = 2, // 0x00000002
                USPM_TAKING_GOODS_TO_STORE = 3, // 0x00000003
                USPM_GOING_TO_WORKPLACE = 4, // 0x00000004
                USPM_ATTACKING = 106 // 0x0000006A

            } UnitState_PitchMan;

            static_assert_cpp98_obj(sizeof(UnitState_PitchMan) == 4, UnitState_PitchMan);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
