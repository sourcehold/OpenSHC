/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/MapMetaInfo.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {

#pragma pack(push, 1)
    // SIZE: 0x0000000C
    typedef struct MapMetaInfo {

        dword loadedMapsChecksumArray; // 0x00000000 length: 4
        byte mapType; // 0x00000004 length: 1
        byte mapLocked; // 0x00000005 length: 1
        byte mapBalance; // 0x00000006 length: 1
        byte mapEndInt2; // 0x00000007 length: 1
        byte mapPlayerCount; // 0x00000008 length: 1
        byte int0; // 0x00000009 length: 1
        byte mapType2; // 0x0000000A length: 1
        undefined1 padding_0xb[1]; // 0x0000000B length: 1

    } MapMetaInfo;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MapMetaInfo) == 12, MapMetaInfo);
} // namespace Map
} // namespace OpenSHC
