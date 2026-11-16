/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Enums/LoweredViewTransition.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Enums {
        typedef enum LoweredViewTransition {

            LVT_NONE = 0, // 0x00000000
            LVT_SET_LOWERED = 1, // 0x00000001
            LVT_SET_NORMAL = 2, // 0x00000002
            LVT_LOWER = 3, // 0x00000003
            LVT_RAISE = 4 // 0x00000004

        } LoweredViewTransition;

        static_assert_cpp98_obj(sizeof(LoweredViewTransition) == 4, LoweredViewTransition);
    } // namespace Enums
} // namespace Map
} // namespace OpenSHC
