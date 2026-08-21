/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/States/UnitState_Baker.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_Baker {

                USB_WAITING_0 = 0, // 0x00000000
                USB_WAITING_1 = 1, // 0x00000001
                USB_GOING_TO_WORKPLACE = 2, // 0x00000002
                USB_AWAITING_STORE_SPACE = 5, // 0x00000005
                USB_TAKING_GOODS_TO_STORE = 6, // 0x00000006
                USB_GOING_TO_GET_SUPPLIES = 7, // 0x00000007
                USB_RETURNING_WITH_SUPPLIES = 8, // 0x00000008
                USB_ATTACKING = 106 // 0x0000006A

            } UnitState_Baker;

            static_assert_cpp98_obj(sizeof(UnitState_Baker) == 4, UnitState_Baker);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
