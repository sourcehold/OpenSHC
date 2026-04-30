/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Location/Point8.hpp'
*/

#pragma once

#include "OpenSHC/Map/Location/Point8IntXY.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"

namespace OpenSHC {
namespace Map {
    namespace Location {

        using OpenSHC::Map::Location::Point8IntXY;
        using OpenSHC::Map::Location::Point8ShortXY;

#pragma pack(push, 1)
        // SIZE: 0x00000008
        typedef union Point8 {

            Point8IntXY int_; // 0x00000000 length: 8
            Point8ShortXY short_; // 0x00000000 length: 8

        } Point8;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(Point8) == 8, Point8);
    } // namespace Location
} // namespace Map
} // namespace OpenSHC
