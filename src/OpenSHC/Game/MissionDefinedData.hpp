/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/MissionDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Game/CampaignInfoStruct1.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::CampaignInfoStruct1;

#pragma pack(push, 1)
    // SIZE: 0x000016C4
    typedef struct MissionDefinedData {

        char** field0_0x0; // 0x00000000 length: 4
        char** field1_0x4; // 0x00000004 length: 4
        char** field2_0x8; // 0x00000008 length: 4
        char** field3_0xc; // 0x0000000C length: 4
        char** field4_0x10; // 0x00000010 length: 4
        char** field5_0x14; // 0x00000014 length: 4
        char** field6_0x18; // 0x00000018 length: 4
        char** field7_0x1c; // 0x0000001C length: 4
        char** field8_0x20; // 0x00000020 length: 4
        undefined1 padding_0x24[4]; // 0x00000024 length: 4
        CampaignInfoStruct1 field13_0x28; // 0x00000028 length: 88
        int field14_0x80[461]; // 0x00000080 length: 1844
        char** field15_0x7b4; // 0x000007B4 length: 4
        char** field16_0x7b8; // 0x000007B8 length: 4
        char** field17_0x7bc; // 0x000007BC length: 4
        char** field18_0x7c0; // 0x000007C0 length: 4
        char** field19_0x7c4; // 0x000007C4 length: 4
        char** field20_0x7c8; // 0x000007C8 length: 4
        char** field21_0x7cc; // 0x000007CC length: 4
        char** field22_0x7d0; // 0x000007D0 length: 4
        int field23_0x7d4[18][2]; // 0x000007D4 length: 144
        char field24_0x864[20][32]; // 0x00000864 length: 640
        int field25_0xae4[5]; // 0x00000AE4 length: 20
        int field26_0xaf8[2]; // 0x00000AF8 length: 8
        int field27_0xb00[20]; // 0x00000B00 length: 80
        int sortColumn; // 0x00000B50 length: 4
        int field29_0xb54[26]; // 0x00000B54 length: 104
        int field30_0xbbc[50][2]; // 0x00000BBC length: 400
        int field31_0xd4c[30][2]; // 0x00000D4C length: 240
        int field32_0xe3c[30][2]; // 0x00000E3C length: 240
        int field33_0xf2c[50]; // 0x00000F2C length: 200
        int field34_0xff4[50][4]; // 0x00000FF4 length: 800
        int field35_0x1314[22]; // 0x00001314 length: 88
        undefined4 descending; // 0x0000136C length: 4
        int field37_0x1370; // 0x00001370 length: 4
        undefined1 padding_0x1374[8]; // 0x00001374 length: 8
        int field46_0x137c[50]; // 0x0000137C length: 200
        char field47_0x1444[20][32]; // 0x00001444 length: 640

    } MissionDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MissionDefinedData) == 5828, MissionDefinedData);
} // namespace Game
} // namespace OpenSHC
