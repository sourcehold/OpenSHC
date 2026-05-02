/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/ScrollDirection.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    typedef enum ScrollDirection {

        SD_UP = 0, // 0x00000000
        SD_UP_RIGHT = 1, // 0x00000001
        SD_RIGHT = 2, // 0x00000002
        SD_DOWN_RIGHT = 3, // 0x00000003
        SD_DOWN = 4, // 0x00000004
        SD_DOWN_LEFT = 5, // 0x00000005
        SD_LEFT = 6, // 0x00000006
        SD_UP_LEFT = 7, // 0x00000007
        SD_NONE = 15 // 0x0000000F

    } ScrollDirection;

    static_assert_cpp98_obj(sizeof(ScrollDirection) == 4, ScrollDirection);
} // namespace UI
} // namespace OpenSHC
