/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/States/UnitState_QuarryWorker.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_QuarryWorker {

                WORKING_0 = 0, // 0x00000000
                WAITING_1 = 1, // 0x00000001
                AWAITING_STORE_SPACE = 2, // 0x00000002
                TAKING_GOODS_TO_STORE = 3, // 0x00000003
                GOING_TO_WORKPLACE = 4, // 0x00000004
                RESTING = 5, // 0x00000005
                WAITING_6 = 6, // 0x00000006
                ATTACKING = 106 // 0x0000006A

            } UnitState_QuarryWorker;

            static_assert_cpp98_obj(sizeof(UnitState_QuarryWorker) == 4, UnitState_QuarryWorker);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
