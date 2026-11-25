/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Walls/WallConstants.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Walls {
        typedef enum WallConstants {

            WALL_LOW_HEIGHT = 60, // 0x0000003C
            WALL_LOW_CRENAL_HEIGHT = 68, // 0x00000044
            WALL_HIGH_HEIGHT = 90, // 0x0000005A
            WALL_HIGH_CRENAL_HEIGHT = 98 // 0x00000062

        } WallConstants;

        static_assert_cpp98_obj(sizeof(WallConstants) == 4, WallConstants);
    } // namespace Walls
} // namespace Map
} // namespace OpenSHC
