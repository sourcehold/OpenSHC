/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/MapDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Map/MapSectionAddress.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::MapSectionAddress;

#pragma pack(push, 1)
    // SIZE: 0x0003304C
    typedef struct MapDefinedData {

        undefined1 padding_0x0[4]; // 0x00000000 length: 4
        char DAT_GMNameArray[207][1000]; // 0x00000004 length: 207000
        MapSectionAddress DAT_MapSectionAddressArray[123]; // 0x0003289C length: 1968

    } MapDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MapDefinedData) == 208972, MapDefinedData);
} // namespace Map
} // namespace OpenSHC
