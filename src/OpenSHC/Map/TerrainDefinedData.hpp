/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/TerrainDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Map/Buildings/WheatFarm/WheatFarmFieldSpec.hpp"
#include "OpenSHC/Map/GFX/UnkBytePair.hpp"
#include "OpenSHC/Map/Location/Point8.hpp"
#include "OpenSHC/Map/Location/Point8IntXY.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::WheatFarm::WheatFarmFieldSpec;
    using OpenSHC::Map::GFX::UnkBytePair;
    using OpenSHC::Map::Location::Point8;
    using OpenSHC::Map::Location::Point8IntXY;
    using OpenSHC::Map::Navigation::Algorithms::XYPair;

#pragma pack(push, 1)
    // SIZE: 0x000037AC
    typedef struct TerrainDefinedData {

        undefined1 padding_0x0[12]; // 0x00000000 length: 12
        int field12_0xc[37]; // 0x0000000C length: 148
        int DAT_BrushSizeArray[8]; // 0x000000A0 length: 32
        XYPair field14_0xc0; // 0x000000C0 length: 8
        undefined1 padding_0xc8[8]; // 0x000000C8 length: 8
        undefined4 field23_0xd0; // 0x000000D0 length: 4
        undefined1 padding_0xd4[32]; // 0x000000D4 length: 32
        Point8 DAT_CoordinateCardinalTranslationMatrix[8]; // 0x000000F4 length: 64
        undefined1 padding_0x134[4]; // 0x00000134 length: 4
        int field61_0x138; // 0x00000138 length: 4
        XYPair field62_0x13c[4][3]; // 0x0000013C length: 96
        XYPair field63_0x19c[4]; // 0x0000019C length: 32
        XYPair DAT_Stockpile_BuildingPartsOffsets[4]; // 0x000001BC length: 32
        XYPair DAT_Stockpile_PathableOffsets[9]; // 0x000001DC length: 72
        undefined1 padding_0x224[64]; // 0x00000224 length: 64
        XYPair field130_0x264[3][12]; // 0x00000264 length: 288
        Point8IntXY field131_0x384[8]; // 0x00000384 length: 64
        Point8IntXY field132_0x3c4[8]; // 0x000003C4 length: 64
        undefined1 padding_0x404[64]; // 0x00000404 length: 64
        XYPair field197_0x444[24]; // 0x00000444 length: 192
        undefined1 padding_0x504[8]; // 0x00000504 length: 8
        XYPair field206_0x50c; // 0x0000050C length: 8
        undefined1 padding_0x514[4]; // 0x00000514 length: 4
        XYPair field211_0x518; // 0x00000518 length: 8
        undefined1 padding_0x520[76]; // 0x00000520 length: 76
        XYPair field288_0x56c; // 0x0000056C length: 8
        undefined1 padding_0x574[4]; // 0x00000574 length: 4
        XYPair field293_0x578; // 0x00000578 length: 8
        undefined1 padding_0x580[76]; // 0x00000580 length: 76
        XYPair field370_0x5cc; // 0x000005CC length: 8
        undefined1 padding_0x5d4[184]; // 0x000005D4 length: 184
        XYPair field555_0x68c; // 0x0000068C length: 8
        undefined1 padding_0x694[440]; // 0x00000694 length: 440
        int field996_0x84c[25]; // 0x0000084C length: 100
        undefined1 padding_0x8b0[4]; // 0x000008B0 length: 4
        int field1001_0x8b4[25]; // 0x000008B4 length: 100
        undefined1 padding_0x918[4]; // 0x00000918 length: 4
        XYPair field1006_0x91c[4][36]; // 0x0000091C length: 1152
        XYPair field1007_0xd9c[2][24]; // 0x00000D9C length: 384
        XYPair field1008_0xf1c[8]; // 0x00000F1C length: 64
        WheatFarmFieldSpec field1009_0xf5c[4][27]; // 0x00000F5C length: 1296
        undefined1 padding_0x146c[1280]; // 0x0000146C length: 1280
        XYPair field2290_0x196c[4]; // 0x0000196C length: 32
        XYPair field2291_0x198c[9]; // 0x0000198C length: 72
        XYPair field2292_0x19d4[16]; // 0x000019D4 length: 128
        int field2293_0x1a54[4][16]; // 0x00001A54 length: 256
        int field2294_0x1b54[4][16]; // 0x00001B54 length: 256
        int field2295_0x1c54[4][16]; // 0x00001C54 length: 256
        byte field2296_0x1d54[4][2]; // 0x00001D54 length: 8
        byte field2297_0x1d5c[4][2]; // 0x00001D5C length: 8
        UnkBytePair field2298_0x1d64[8]; // 0x00001D64 length: 16
        int DAT_MapSizes[5]; // 0x00001D74 length: 20
        undefined1 padding_0x1d88[164]; // 0x00001D88 length: 164
        int DAT_SomeOrientationOrderArray[8]; // 0x00001E2C length: 32
        int field2465_0x1e4c[32]; // 0x00001E4C length: 128
        XYPair field2466_0x1ecc[4][9]; // 0x00001ECC length: 288
        int field2467_0x1fec[4][25]; // 0x00001FEC length: 400
        int field2468_0x217c[7][4]; // 0x0000217C length: 112
        int field2469_0x21ec[4][25]; // 0x000021EC length: 400
        int field2470_0x237c[4][25]; // 0x0000237C length: 400
        int field2471_0x250c[26]; // 0x0000250C length: 104
        int field2472_0x2574[60]; // 0x00002574 length: 240
        int field2473_0x2664[64]; // 0x00002664 length: 256
        XYPair field2474_0x2764[501]; // 0x00002764 length: 4008
        int field2475_0x370c[8]; // 0x0000370C length: 32
        XYPair field2476_0x372c[8]; // 0x0000372C length: 64
        XYPair field2477_0x376c[4]; // 0x0000376C length: 32
        XYPair field2478_0x378c[4]; // 0x0000378C length: 32

    } TerrainDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(TerrainDefinedData) == 14252, TerrainDefinedData);
} // namespace Map
} // namespace OpenSHC
