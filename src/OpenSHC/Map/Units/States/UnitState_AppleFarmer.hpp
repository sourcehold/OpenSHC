/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Units/States/UnitState_AppleFarmer.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_AppleFarmer {

                USAF_DETERMINE_NEXT_STATE = 0, // 0x00000000
                USAF_CHECK_IDLE = 1, // 0x00000001
                USAF_START_TAKING_APPLES = 2, // 0x00000002
                USAF_PICKING_APPLES = 3, // 0x00000003
                USAF_WALKING = 4, // 0x00000004
                USAF_GOING_TO_WORKPLACE = 5, // 0x00000005
                USAF_WORKSHOP_TIMER_CHECK = 6, // 0x00000006
                USAF_TAKE_RESOURCE_TO_GRANARY = 7, // 0x00000007
                USAF_GATHER_APPLES = 8 // 0x00000008

            } UnitState_AppleFarmer;

            static_assert_cpp98_obj(sizeof(UnitState_AppleFarmer) == 4, UnitState_AppleFarmer);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
