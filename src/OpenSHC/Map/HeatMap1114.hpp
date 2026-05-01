/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/HeatMap1114.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {

#pragma pack(push, 1)
    // SIZE: 0x00000030
    typedef struct HeatMap1114 {

        int algorithmIterationNumber; // 0x00000000 length: 4
        byte distanceToTheKeepCountUnk_fixme; // 0x00000004 length: 1
        byte algorithmVisitCountUnk; // 0x00000005 length: 1
        byte anotherCount_0x6; // 0x00000006 length: 1
        byte woodCount; // 0x00000007 length: 1
        byte stoneCount; // 0x00000008 length: 1
        byte ironCount; // 0x00000009 length: 1
        byte oilCount_1; // 0x0000000A length: 1
        byte oilCount_2; // 0x0000000B length: 1
        byte lowestTerrainHeight; // 0x0000000C length: 1
        byte highestTerrainHeight; // 0x0000000D length: 1
        byte terrainDiffHigherThan12; // 0x0000000E length: 1
        byte buildingOccupiedTilesCount; // 0x0000000F length: 1
        byte isNotNearEdgeUnk; // 0x00000010 length: 1
        byte oasisUnk; // 0x00000011 length: 1
        byte oasisthickUnk; // 0x00000012 length: 1
        byte value10; // 0x00000013 length: 1
        byte field17_0x14; // 0x00000014 length: 1
        byte tileOwnership; // 0x00000015 length: 1
        byte waterOrRockCountUnk; // 0x00000016 length: 1
        byte field20_0x17; // 0x00000017 length: 1
        short field21_0x18; // 0x00000018 length: 2
        short field22_0x1a; // 0x0000001A length: 2
        short field23_0x1c; // 0x0000001C length: 2
        short field24_0x1e; // 0x0000001E length: 2
        short field25_0x20; // 0x00000020 length: 2
        short field26_0x22; // 0x00000022 length: 2
        short field27_0x24; // 0x00000024 length: 2
        short field28_0x26; // 0x00000026 length: 2
        short field29_0x28; // 0x00000028 length: 2
        short field30_0x2a; // 0x0000002A length: 2
        short field31_0x2c; // 0x0000002C length: 2
        short field32_0x2e; // 0x0000002E length: 2

    } HeatMap1114;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(HeatMap1114) == 48, HeatMap1114);
} // namespace Map
} // namespace OpenSHC
