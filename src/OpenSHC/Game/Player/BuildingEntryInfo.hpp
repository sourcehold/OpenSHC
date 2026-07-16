/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Player/BuildingEntryInfo.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Player {

#pragma pack(push, 1)
        // SIZE: 0x00000028
        typedef struct BuildingEntryInfo {

            int id; // 0x00000000 length: 4
            int xEntry; // 0x00000004 length: 4
            int yEntry; // 0x00000008 length: 4
            int tileEntry; // 0x0000000C length: 4
            int areaEntry; // 0x00000010 length: 4
            int field5_0x14; // 0x00000014 length: 4
            int field6_0x18; // 0x00000018 length: 4
            int field7_0x1c; // 0x0000001C length: 4
            int field8_0x20; // 0x00000020 length: 4
            int field9_0x24; // 0x00000024 length: 4

        } BuildingEntryInfo;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(BuildingEntryInfo) == 40, BuildingEntryInfo);
    } // namespace Player
} // namespace Game
} // namespace OpenSHC
