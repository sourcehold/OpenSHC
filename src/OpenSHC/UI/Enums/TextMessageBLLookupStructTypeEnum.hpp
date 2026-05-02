/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Enums/TextMessageBLLookupStructTypeEnum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace Enums {
        typedef enum TextMessageBLLookupStructTypeEnum {

            TMBLLSTE_BUTTON_TEXT = 2, // 0x00000002
            TMBLLSTE_BUILDING_TEXT = 3, // 0x00000003
            TMBLLSTE_POPULARITY_HELP_TEXT = 4, // 0x00000004
            TMBLLSTE_WALL_TEXT = 5, // 0x00000005
            TMBLLSTE_UNITS_AND_WEAPONS_TEXT = 6 // 0x00000006

        } TextMessageBLLookupStructTypeEnum;

        static_assert_cpp98_obj(sizeof(TextMessageBLLookupStructTypeEnum) == 4, TextMessageBLLookupStructTypeEnum);
    } // namespace Enums
} // namespace UI
} // namespace OpenSHC
