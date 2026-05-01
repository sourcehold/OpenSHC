/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Units/States/UnitState_QuarryMason.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_QuarryMason {

                USQM_WAITING = 0, // 0x00000000
                USQM_AWAITING_STORE_SPACE = 2, // 0x00000002
                USQM_ATTACKING = 106 // 0x0000006A

            } UnitState_QuarryMason;

            static_assert_cpp98_obj(sizeof(UnitState_QuarryMason) == 4, UnitState_QuarryMason);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
