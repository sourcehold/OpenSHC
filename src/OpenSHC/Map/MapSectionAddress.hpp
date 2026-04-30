/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/MapSectionAddress.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {

#pragma pack(push, 1)
    // SIZE: 0x00000010
    typedef struct MapSectionAddress {

        pointer* address; // 0x00000000 length: 4
        undefined4 unknown; // 0x00000004 length: 4
        uint size; // 0x00000008 length: 4
        ushort compressed; // 0x0000000C length: 2
        ushort sectionId; // 0x0000000E length: 2

    } MapSectionAddress;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MapSectionAddress) == 16, MapSectionAddress);
} // namespace Map
} // namespace OpenSHC
