/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Enums/CardinalDirection.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Enums {
        typedef enum CardinalDirection {

            CD_NORTH = 0, // 0x00000000
            CD_NORTHEAST = 1, // 0x00000001
            CD_EAST = 2, // 0x00000002
            CD_SOUTHEAST = 3, // 0x00000003
            CD_SOUTH = 4, // 0x00000004
            CD_SOUTHWEST = 5, // 0x00000005
            CD_WEST = 6, // 0x00000006
            CD_NORTHWEST = 7, // 0x00000007
            CD_UPPER_LIMIT = 8, // 0x00000008
            CD_UNSPECIFIED = 15 // 0x0000000F

        } CardinalDirection;

        static_assert_cpp98_obj(sizeof(CardinalDirection) == 4, CardinalDirection);
    } // namespace Enums
} // namespace Map
} // namespace OpenSHC
