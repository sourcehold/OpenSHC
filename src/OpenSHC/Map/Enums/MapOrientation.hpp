/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Enums/MapOrientation.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Enums {
        typedef enum MapOrientation {

            MO_NORTH = 0, // 0x00000000
            MO_EAST = 2, // 0x00000002
            MO_SOUTH = 4, // 0x00000004
            MO_WEST = 6 // 0x00000006

        } MapOrientation;

        static_assert_cpp98_obj(sizeof(MapOrientation) == 4, MapOrientation);
    } // namespace Enums
} // namespace Map
} // namespace OpenSHC
