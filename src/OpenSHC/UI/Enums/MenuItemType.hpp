/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/Enums/MenuItemType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace Enums {
        typedef enum MenuItemType {

            MIT_NORMAL_ELEMENTUnk = 3, // 0x00000003
            MIT_TEXT_OR_STATE_OR_PLAYER_DEPENDENTUnk = 4, // 0x00000004
            MIT_SLIDERUnk = 5, // 0x00000005
            MIT_SCROLLBARUnk = 6, // 0x00000006
            MIT_ENABLE_OR_WRAP_BUILD_MENU_TRANSITION_OFFSET = 8, // 0x00000008
            MIT_MENU_MODALUnk = 9, // 0x00000009
            MIT_TAB_CONSIDER_ITEM_SKIP_BECAUSE_OTHER_MENU_TAB = 100, // 0x00000064
            MIT_TAB_CONSIDER_STOP_BECAUSE_IS_CURRENT_MENU_TAB = 101, // 0x00000065
            MIT_LAST_ENTRY = 102, // 0x00000066
            MIT_STOP_HANDLING = 103, // 0x00000067
            MIT_MENU_ITEM_TYPE_ID_PARTUnk = 8388607, // 0x007FFFFF
            MIT_START_OF_INTERACTION_GROUPUnk = 16777216, // 0x01000000
            MIT_PART_OF_INTERACTION_GROUPUnk = 33554432 // 0x02000000

        } MenuItemType;

        static_assert_cpp98_obj(sizeof(MenuItemType) == 4, MenuItemType);
    } // namespace Enums
} // namespace UI
} // namespace OpenSHC
