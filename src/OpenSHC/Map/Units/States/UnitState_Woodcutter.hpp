/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/States/UnitState_Woodcutter.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_Woodcutter {

                USWC_WAITING = 0, // 0x00000000
                USWC_GOING_TO_CHOP_WOOD = 1, // 0x00000001
                USWC_FELLING_A_TREE = 2, // 0x00000002
                USWC_CHOPPING_A_TREE = 3, // 0x00000003
                USWC_RETURNING_WITH_LOG = 4, // 0x00000004
                USWC_WORKING_5 = 5, // 0x00000005
                USWC_WORKING_6 = 6, // 0x00000006
                USWC_AWAITING_STORE_SPACE = 7, // 0x00000007
                USWC_TAKING_GOODS_TO_STORE = 8, // 0x00000008
                USWC_GOING_TO_WORKPLACE = 9, // 0x00000009
                USWC_RESTING = 10, // 0x0000000A
                USWC_ATTACKING = 106 // 0x0000006A

            } UnitState_Woodcutter;

            static_assert_cpp98_obj(sizeof(UnitState_Woodcutter) == 4, UnitState_Woodcutter);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
