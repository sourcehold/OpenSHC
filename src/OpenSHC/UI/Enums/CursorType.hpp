/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Enums/CursorType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace Enums {
        typedef enum CursorType {

            CT_NOT_SELECTED_YET = 0, // 0x00000000
            CT_ANI_CURSOR = 1, // 0x00000001
            CT_WINDOWS_LIKE_CURSOR = 2 // 0x00000002

        } CursorType;

        static_assert_cpp98_obj(sizeof(CursorType) == 4, CursorType);
    } // namespace Enums
} // namespace UI
} // namespace OpenSHC
