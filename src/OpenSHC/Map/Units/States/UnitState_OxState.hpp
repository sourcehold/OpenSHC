/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/States/UnitState_OxState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_OxState {

                USOS_RESET = 0, // 0x00000000
                USOS_TAKING_GOODS_TO_STORE = 1, // 0x00000001
                USOS_WAITING = 2, // 0x00000002
                USOS_GOING_TO_WORKPLACE = 3, // 0x00000003
                USOS_EATING_GRASS = 4, // 0x00000004
                USOS_ATTACKING = 106 // 0x0000006A

            } UnitState_OxState;

            static_assert_cpp98_obj(sizeof(UnitState_OxState) == 4, UnitState_OxState);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
