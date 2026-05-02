/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Wildlife/WildlifeGridElement.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Wildlife {

#pragma pack(push, 1)
        // SIZE: 0x000000A0
        typedef struct WildlifeGridElement {

            int firstMember; // 0x00000000 length: 4
            int separateAreaID; // 0x00000004 length: 4
            int unclaimedArea; // 0x00000008 length: 4
            int field3_0xc; // 0x0000000C length: 4
            int keeps; // 0x00000010 length: 4
            int field5_0x14; // 0x00000014 length: 4
            int trees; // 0x00000018 length: 4
            int unitCount; // 0x0000001C length: 4
            int field8_0x20; // 0x00000020 length: 4
            int camelCount; // 0x00000024 length: 4
            int lionCount; // 0x00000028 length: 4
            int deerCount; // 0x0000002C length: 4
            int field12_0x30; // 0x00000030 length: 4
            int field13_0x34; // 0x00000034 length: 4
            int casDisRelated2; // 0x00000038 length: 4
            int field15_0x3c; // 0x0000003C length: 4
            int field16_0x40; // 0x00000040 length: 4
            int field17_0x44; // 0x00000044 length: 4
            int field18_0x48; // 0x00000048 length: 4
            int field19_0x4c; // 0x0000004C length: 4
            int field20_0x50; // 0x00000050 length: 4
            int rabbitCount; // 0x00000054 length: 4
            int chimps; // 0x00000058 length: 4
            int castlebuildings; // 0x0000005C length: 4
            int field24_0x60; // 0x00000060 length: 4
            int field25_0x64; // 0x00000064 length: 4
            int unknownNonZero01; // 0x00000068 length: 4
            int field27_0x6c; // 0x0000006C length: 4
            int field28_0x70; // 0x00000070 length: 4
            int field29_0x74; // 0x00000074 length: 4
            undefined1 padding_0x78[40]; // 0x00000078 length: 40

        } WildlifeGridElement;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(WildlifeGridElement) == 160, WildlifeGridElement);
    } // namespace Wildlife
} // namespace Map
} // namespace OpenSHC
