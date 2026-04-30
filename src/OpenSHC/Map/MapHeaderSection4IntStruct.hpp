/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/MapHeaderSection4IntStruct.hpp'
*/

#pragma once

#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Navigation::Algorithms::XYPair;

#pragma pack(push, 1)
    // SIZE: 0x00000040
    typedef struct MapHeaderSection4IntStruct {

        XYPair keepPositions[8]; // 0x00000000 length: 64

    } MapHeaderSection4IntStruct;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MapHeaderSection4IntStruct) == 64, MapHeaderSection4IntStruct);
} // namespace Map
} // namespace OpenSHC
