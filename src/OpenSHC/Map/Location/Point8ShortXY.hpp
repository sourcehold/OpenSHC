/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Location/Point8ShortXY.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Location {

#pragma pack(push, 1)
        // SIZE: 0x00000008
        typedef struct Point8ShortXY {

            short xOffset; // 0x00000000 length: 2
            undefined1 padding_0x2[2]; // 0x00000002 length: 2
            short yOffset; // 0x00000004 length: 2
            undefined1 padding_0x6[2]; // 0x00000006 length: 2

        } Point8ShortXY;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(Point8ShortXY) == 8, Point8ShortXY);
    } // namespace Location
} // namespace Map
} // namespace OpenSHC
