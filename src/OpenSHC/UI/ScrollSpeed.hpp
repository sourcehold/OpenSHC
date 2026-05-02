/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/ScrollSpeed.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    typedef enum ScrollSpeed {

        SS_NORMAL = 0, // 0x00000000
        SS_FAST = 1, // 0x00000001
        SS_SLOW = 2 // 0x00000002

    } ScrollSpeed;

    static_assert_cpp98_obj(sizeof(ScrollSpeed) == 4, ScrollSpeed);
} // namespace UI
} // namespace OpenSHC
