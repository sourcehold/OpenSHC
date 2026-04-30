/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/Enums/MenuItemHandleState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace Enums {
        typedef enum MenuItemHandleState {

            MIHS_HANDLE_INPUT_CALLBACKSUnk = 0, // 0x00000000
            MIHS_PREPARE_AND_RENDER = 1, // 0x00000001
            MIHS_RESET_MENU_ITEM_STATEUnk = 2, // 0x00000002
            MIHS_PREPARE_AND_RENDER_FOR_FLAG_0X800000 = 3 // 0x00000003

        } MenuItemHandleState;

        static_assert_cpp98_obj(sizeof(MenuItemHandleState) == 4, MenuItemHandleState);
    } // namespace Enums
} // namespace UI
} // namespace OpenSHC
