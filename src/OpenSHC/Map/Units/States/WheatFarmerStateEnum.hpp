/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/States/WheatFarmerStateEnum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum WheatFarmerStateEnum {

                WFSE_WAITING_0 = 0, // 0x00000000
                WFSE_WAITING_1 = 1, // 0x00000001
                WFSE_GOING_TO_WORKPLACE = 2, // 0x00000002
                WFSE_WORKING_3 = 3, // 0x00000003
                WFSE_WORKING_4 = 4, // 0x00000004
                WFSE_WORKING_5 = 5, // 0x00000005
                WFSE_WORKING_6 = 6, // 0x00000006
                WFSE_WORKING_7 = 7, // 0x00000007
                WFSE_WORKING_8 = 8, // 0x00000008
                WFSE_AWAITING_STORE_SPACE = 9, // 0x00000009
                WFSE_TAKING_GOODS_TO_STORE = 10, // 0x0000000A
                WFSE_ATTACKING = 106 // 0x0000006A

            } WheatFarmerStateEnum;

            static_assert_cpp98_obj(sizeof(WheatFarmerStateEnum) == 4, WheatFarmerStateEnum);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
