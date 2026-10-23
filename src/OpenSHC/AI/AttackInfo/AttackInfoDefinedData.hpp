/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AttackInfo/AttackInfoDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/AI/Tribes/AITribeTypeInt.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"

namespace OpenSHC {
namespace AI {
    namespace AttackInfo {

        using OpenSHC::AI::Tribes::AITribeTypeInt;
        using OpenSHC::Commands::MappersEnum;

#pragma pack(push, 1)
        // SIZE: 0x00000A34
        typedef struct AttackInfoDefinedData {

            int AICasDisThreshold[10]; // 0x00000000 length: 40
            int AIAttackWaveAdvanceDelay[10]; // 0x00000028 length: 40
            int AttackWaveDurationPerAttacker[10]; // 0x00000050 length: 40
            int AIAttackWaveTargetDelay[10]; // 0x00000078 length: 40
            int AIReservedTroopBudget[10]; // 0x000000A0 length: 40
            MappersEnum field5_0xc8[5]; // 0x000000C8 length: 20
            int field6_0xdc; // 0x000000DC length: 4
            int field7_0xe0; // 0x000000E0 length: 4
            int field8_0xe4; // 0x000000E4 length: 4
            int field9_0xe8; // 0x000000E8 length: 4
            short SiegeCrewPositionOffsets[16][2]; // 0x000000EC length: 64
            AITribeTypeInt field_0x12c[20]; // 0x0000012C length: 80
            AITribeTypeInt field_0x17c[20]; // 0x0000017C length: 80
            AITribeTypeInt field_0x1cc[20]; // 0x000001CC length: 80
            AITribeTypeInt field14_0x21c[20]; // 0x0000021C length: 80
            AITribeTypeInt field15_0x26c[20]; // 0x0000026C length: 80
            AITribeTypeInt field16_0x2bc[20]; // 0x000002BC length: 80
            AITribeTypeInt field17_0x30c[20]; // 0x0000030C length: 80
            AITribeTypeInt field18_0x35c[20]; // 0x0000035C length: 80
            AITribeTypeInt field19_0x3ac[20]; // 0x000003AC length: 80
            AITribeTypeInt field20_0x3fc[20]; // 0x000003FC length: 80
            AITribeTypeInt field_0x44c[20]; // 0x0000044C length: 80
            AITribeTypeInt field_0x49c[20]; // 0x0000049C length: 80
            AITribeTypeInt field_0x4ec[20]; // 0x000004EC length: 80
            AITribeTypeInt field_0x53c[20]; // 0x0000053C length: 80
            AITribeTypeInt field_0x58c[20]; // 0x0000058C length: 80
            AITribeTypeInt field_0x5dc[20]; // 0x000005DC length: 80
            AITribeTypeInt field_0x62c[20]; // 0x0000062C length: 80
            AITribeTypeInt field_0x67c[20]; // 0x0000067C length: 80
            AITribeTypeInt field_0x6cc[20]; // 0x000006CC length: 80
            AITribeTypeInt field_0x71c[20]; // 0x0000071C length: 80
            AITribeTypeInt field31_0x76c[20]; // 0x0000076C length: 80
            AITribeTypeInt field32_0x7bc[20]; // 0x000007BC length: 80
            AITribeTypeInt field33_0x80c[20]; // 0x0000080C length: 80
            AITribeTypeInt field_0x85c[20]; // 0x0000085C length: 80
            AITribeTypeInt field_0x8ac[20]; // 0x000008AC length: 80
            AITribeTypeInt field_0x8fc[20]; // 0x000008FC length: 80
            AITribeTypeInt field_0x94c[20]; // 0x0000094C length: 80
            AITribeTypeInt field_0x99c[20]; // 0x0000099C length: 80
            int field39_0x9ec[5]; // 0x000009EC length: 20
            undefined1 padding_0xa00[12]; // 0x00000A00 length: 12
            int field52_0xa0c; // 0x00000A0C length: 4
            undefined1 padding_0xa10[36]; // 0x00000A10 length: 36

        } AttackInfoDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(AttackInfoDefinedData) == 2612, AttackInfoDefinedData);
    } // namespace AttackInfo
} // namespace AI
} // namespace OpenSHC
