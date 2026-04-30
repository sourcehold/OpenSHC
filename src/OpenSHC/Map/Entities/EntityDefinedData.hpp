/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Entities/EntityDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/IO/Graphics/GmIDInt.hpp"
#include "OpenSHC/Map/Location/Point4ShortXY.hpp"
#include "OpenSHC/Map/Location/Point8IntXY.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::IO::Graphics::GmIDInt;
        using OpenSHC::Map::Location::Point4ShortXY;
        using OpenSHC::Map::Location::Point8IntXY;

#pragma pack(push, 1)
        // SIZE: 0x00001964
        typedef struct EntityDefinedData {

            int field0_0x0[9]; // 0x00000000 length: 36
            pointer PTR_FUN_EntityCallbacks[44]; // 0x00000024 length: 176
            GmIDInt DAT_EntityPropertyArray_1[45]; // 0x000000D4 length: 180
            byte field3_0x188[36]; // 0x00000188 length: 36
            int DAT_EntityPropertyArray_2[45]; // 0x000001AC length: 180
            byte field5_0x260[16]; // 0x00000260 length: 16
            int field6_0x270[15]; // 0x00000270 length: 60
            int field7_0x2ac[35]; // 0x000002AC length: 140
            byte field8_0x338[28]; // 0x00000338 length: 28
            uint DAT_EntityTypeArrayForProjectileRange[38]; // 0x00000354 length: 152
            undefined1 padding_0x3ec[28]; // 0x000003EC length: 28
            byte field38_0x408[28]; // 0x00000408 length: 28
            int DAT_EntityArrayCurveTypeForProjectileType[45]; // 0x00000424 length: 180
            byte field40_0x4d8[28]; // 0x000004D8 length: 28
            int DAT_EntityArrayProjectileVelocityForProjectileType[45]; // 0x000004F4 length: 180
            byte field42_0x5a8[28]; // 0x000005A8 length: 28
            float field43_0x5c4[46]; // 0x000005C4 length: 184
            int DAT_EntityPropertyArray_3[56]; // 0x0000067C length: 224
            int field45_0x75c[36]; // 0x0000075C length: 144
            int field46_0x7ec[3]; // 0x000007EC length: 12
            int field47_0x7f8; // 0x000007F8 length: 4
            int field48_0x7fc[42]; // 0x000007FC length: 168
            int field49_0x8a4[3]; // 0x000008A4 length: 12
            int field50_0x8b0; // 0x000008B0 length: 4
            int field51_0x8b4[42]; // 0x000008B4 length: 168
            GmIDInt field52_0x95c[46]; // 0x0000095C length: 184
            int field53_0xa14[92]; // 0x00000A14 length: 368
            Point4ShortXY field54_0xb84[128]; // 0x00000B84 length: 512
            Point8IntXY field55_0xd84[16]; // 0x00000D84 length: 128
            byte field56_0xe04[48]; // 0x00000E04 length: 48
            byte field57_0xe34[56]; // 0x00000E34 length: 56
            int DAT_XYOffsetsInAllDirections[64][2]; // 0x00000E6C length: 512
            int field59_0x106c[4]; // 0x0000106C length: 16
            int field60_0x107c[58]; // 0x0000107C length: 232
            int field61_0x1164[76]; // 0x00001164 length: 304
            int field62_0x1294[66]; // 0x00001294 length: 264
            int field63_0x139c[144]; // 0x0000139C length: 576
            int field64_0x15dc[114]; // 0x000015DC length: 456
            int field65_0x17a4[112]; // 0x000017A4 length: 448

        } EntityDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(EntityDefinedData) == 6500, EntityDefinedData);
    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
