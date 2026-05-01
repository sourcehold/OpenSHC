/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/AI/AttackInfo/AttackInfoDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/AI/Tribes/AITribeTypeInt.hpp"
#include "OpenSHC/AI/Tribes/AITribeTypeShort.hpp"
#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"

namespace OpenSHC {
namespace AI {
    namespace AttackInfo {

        using OpenSHC::AI::Tribes::AITribeTypeInt;
        using OpenSHC::AI::Tribes::AITribeTypeShort;
        using OpenSHC::Commands::CommandBuildingTypeInt;

#pragma pack(push, 1)
        // SIZE: 0x00000A34
        typedef struct AttackInfoDefinedData {

            int field0_0x0[10]; // 0x00000000 length: 40
            int field1_0x28[10]; // 0x00000028 length: 40
            int DAT_AttackWaveDurationPerAttacker[10]; // 0x00000050 length: 40
            int field3_0x78[10]; // 0x00000078 length: 40
            int field4_0xa0[10]; // 0x000000A0 length: 40
            CommandBuildingTypeInt field5_0xc8[5]; // 0x000000C8 length: 20
            int field6_0xdc; // 0x000000DC length: 4
            int field7_0xe0; // 0x000000E0 length: 4
            int field8_0xe4; // 0x000000E4 length: 4
            int field9_0xe8; // 0x000000E8 length: 4
            short field10_0xec[16][2]; // 0x000000EC length: 64
            undefined1 padding_0x12c[240]; // 0x0000012C length: 240
            AITribeTypeInt field251_0x21c[20]; // 0x0000021C length: 80
            AITribeTypeInt field252_0x26c[20]; // 0x0000026C length: 80
            AITribeTypeInt field253_0x2bc[20]; // 0x000002BC length: 80
            AITribeTypeInt field254_0x30c[20]; // 0x0000030C length: 80
            AITribeTypeInt field255_0x35c[20]; // 0x0000035C length: 80
            AITribeTypeInt field256_0x3ac[20]; // 0x000003AC length: 80
            AITribeTypeInt field257_0x3fc[20]; // 0x000003FC length: 80
            undefined1 padding_0x44c[800]; // 0x0000044C length: 800
            AITribeTypeInt field1058_0x76c[20]; // 0x0000076C length: 80
            AITribeTypeInt field1059_0x7bc[20]; // 0x000007BC length: 80
            AITribeTypeShort field1060_0x80c[40]; // 0x0000080C length: 80
            undefined1 padding_0x85c[400]; // 0x0000085C length: 400
            int field1461_0x9ec[5]; // 0x000009EC length: 20
            undefined1 padding_0xa00[12]; // 0x00000A00 length: 12
            int field1474_0xa0c; // 0x00000A0C length: 4
            undefined1 padding_0xa10[36]; // 0x00000A10 length: 36

        } AttackInfoDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(AttackInfoDefinedData) == 2612, AttackInfoDefinedData);
    } // namespace AttackInfo
} // namespace AI
} // namespace OpenSHC
