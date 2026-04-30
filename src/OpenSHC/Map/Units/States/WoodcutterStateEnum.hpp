/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Units/States/WoodcutterStateEnum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum WoodcutterStateEnum {

                WSE_WAITING = 0, // 0x00000000
                WSE_GOING_TO_CHOP_WOOD = 1, // 0x00000001
                WSE_FELLING_A_TREE = 2, // 0x00000002
                WSE_CHOPPING_A_TREE = 3, // 0x00000003
                WSE_RETURNING_WITH_LOG = 4, // 0x00000004
                WSE_WORKING_5 = 5, // 0x00000005
                WSE_WORKING_6 = 6, // 0x00000006
                WSE_AWAITING_STORE_SPACE = 7, // 0x00000007
                WSE_TAKING_GOODS_TO_STORE = 8, // 0x00000008
                WSE_GOING_TO_WORKPLACE = 9, // 0x00000009
                WSE_RESTING = 10, // 0x0000000A
                WSE_ATTACKING = 106 // 0x0000006A

            } WoodcutterStateEnum;

            static_assert_cpp98_obj(sizeof(WoodcutterStateEnum) == 4, WoodcutterStateEnum);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
