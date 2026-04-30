/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/MapColorRelatedStructure1.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {

#pragma pack(push, 1)
    // SIZE: 0x00000008
    typedef struct MapColorRelatedStructure1 {

        int integer; // 0x00000000 length: 4
        ushort colorModeSpecificValue[2]; // 0x00000004 length: 4

    } MapColorRelatedStructure1;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MapColorRelatedStructure1) == 8, MapColorRelatedStructure1);
} // namespace Map
} // namespace OpenSHC
