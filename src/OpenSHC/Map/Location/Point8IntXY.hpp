/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Location/Point8IntXY.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Location {

#pragma pack(push, 1)
        // SIZE: 0x00000008
        typedef struct Point8IntXY {

            int xOffset; // 0x00000000 length: 4
            int yOffset; // 0x00000004 length: 4

        } Point8IntXY;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(Point8IntXY) == 8, Point8IntXY);
    } // namespace Location
} // namespace Map
} // namespace OpenSHC
