/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/State/MapAndTimeState.hpp'
*/

#pragma once

#include "OpenSHC/Game/Market/BuySellPair.hpp"
#include "OpenSHC/Game/Skirmish/AttackVector.hpp"
#include "OpenSHC/Map/Location/Point8IntXY.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYTileObject.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"

namespace OpenSHC {
namespace Game {
    namespace State {

        using OpenSHC::Game::Market::BuySellPair;
        using OpenSHC::Game::Skirmish::AttackVector;
        using OpenSHC::Map::Location::Point8IntXY;
        using OpenSHC::Map::Navigation::Algorithms::XYPair;
        using OpenSHC::Map::Navigation::Algorithms::XYTileObject;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
        // SIZE: 0x000401D0
        typedef struct MapAndTimeState {

            int field0_0x0; // 0x00000000 length: 4
            BOOLEnum singlePlayerHasKeepAndGranary; // 0x00000004 length: 4
            int field2_0x8; // 0x00000008 length: 4
            int field3_0xc; // 0x0000000C length: 4
            int field4_0x10; // 0x00000010 length: 4
            int field5_0x14; // 0x00000014 length: 4
            int field6_0x18; // 0x00000018 length: 4
            int field7_0x1c; // 0x0000001C length: 4
            int field8_0x20; // 0x00000020 length: 4
            int field9_0x24; // 0x00000024 length: 4
            int field10_0x28; // 0x00000028 length: 4
            int field11_0x2c; // 0x0000002C length: 4
            int field12_0x30; // 0x00000030 length: 4
            int field13_0x34; // 0x00000034 length: 4
            int field14_0x38; // 0x00000038 length: 4
            int field15_0x3c; // 0x0000003C length: 4
            int field16_0x40; // 0x00000040 length: 4
            int field17_0x44; // 0x00000044 length: 4
            int field18_0x48; // 0x00000048 length: 4
            int field19_0x4c; // 0x0000004C length: 4
            int field20_0x50; // 0x00000050 length: 4
            int field21_0x54; // 0x00000054 length: 4
            int field22_0x58[2][5]; // 0x00000058 length: 40
            int field23_0x80; // 0x00000080 length: 4
            int field24_0x84; // 0x00000084 length: 4
            int field25_0x88; // 0x00000088 length: 4
            int field26_0x8c; // 0x0000008C length: 4
            int field27_0x90; // 0x00000090 length: 4
            int field28_0x94; // 0x00000094 length: 4
            int field29_0x98; // 0x00000098 length: 4
            int field30_0x9c; // 0x0000009C length: 4
            int field31_0xa0; // 0x000000A0 length: 4
            int field32_0xa4; // 0x000000A4 length: 4
            int field33_0xa8; // 0x000000A8 length: 4
            int field34_0xac; // 0x000000AC length: 4
            int field35_0xb0; // 0x000000B0 length: 4
            int field36_0xb4; // 0x000000B4 length: 4
            int field37_0xb8; // 0x000000B8 length: 4
            int field38_0xbc; // 0x000000BC length: 4
            int field39_0xc0; // 0x000000C0 length: 4
            int field40_0xc4; // 0x000000C4 length: 4
            int field41_0xc8; // 0x000000C8 length: 4
            int emenyHitArray[9]; // 0x000000CC length: 36
            int field43_0xf0; // 0x000000F0 length: 4
            int field44_0xf4; // 0x000000F4 length: 4
            int field45_0xf8; // 0x000000F8 length: 4
            DWORD gameOverTime; // 0x000000FC length: 4
            int drunkenManStatus; // 0x00000100 length: 4
            undefined1 padding_0x104[148]; // 0x00000104 length: 148
            int field196_0x198; // 0x00000198 length: 4
            undefined1 padding_0x19c[380]; // 0x0000019C length: 380
            int cathedralRelated1; // 0x00000318 length: 4
            undefined1 padding_0x31c[8]; // 0x0000031C length: 8
            int week; // 0x00000324 length: 4
            int month; // 0x00000328 length: 4
            int year; // 0x0000032C length: 4
            undefined1 padding_0x330[8]; // 0x00000330 length: 8
            int monthChanged; // 0x00000338 length: 4
            int yearChanged; // 0x0000033C length: 4
            int weekChanged; // 0x00000340 length: 4
            int strongWalls2; // 0x00000344 length: 4
            int field601_0x348; // 0x00000348 length: 4
            int counterForUpdatingSeparateAreaTileMaps; // 0x0000034C length: 4
            int totalGameTicksUnk; // 0x00000350 length: 4
            int treeSpreadCounter; // 0x00000354 length: 4
            int newOrganisms; // 0x00000358 length: 4
            int treeSpreadInterval; // 0x0000035C length: 4
            int newOrganismsValue2; // 0x00000360 length: 4
            BOOLEnum startOfDay; // 0x00000364 length: 4
            int section1023; // 0x00000368 length: 4
            undefined1 padding_0x36c[436]; // 0x0000036C length: 436
            XYPair somePairArray; // 0x00000520 length: 8
            undefined1 padding_0x528[312]; // 0x00000528 length: 312
            int startGoods[25]; // 0x00000660 length: 100
            undefined1 padding_0x6c4[4]; // 0x000006C4 length: 4
            int field1364_0x6c8; // 0x000006C8 length: 4
            int field1365_0x6cc; // 0x000006CC length: 4
            int field1366_0x6d0; // 0x000006D0 length: 4
            int field1367_0x6d4; // 0x000006D4 length: 4
            int field1368_0x6d8; // 0x000006D8 length: 4
            int field1369_0x6dc; // 0x000006DC length: 4
            int field1370_0x6e0; // 0x000006E0 length: 4
            int field1371_0x6e4; // 0x000006E4 length: 4
            int field1372_0x6e8; // 0x000006E8 length: 4
            int field1373_0x6ec; // 0x000006EC length: 4
            int field1374_0x6f0; // 0x000006F0 length: 4
            int field1375_0x6f4; // 0x000006F4 length: 4
            int field1376_0x6f8; // 0x000006F8 length: 4
            int field1377_0x6fc; // 0x000006FC length: 4
            int field1378_0x700; // 0x00000700 length: 4
            int field1379_0x704; // 0x00000704 length: 4
            int field1380_0x708; // 0x00000708 length: 4
            int field1381_0x70c; // 0x0000070C length: 4
            int field1382_0x710; // 0x00000710 length: 4
            int startingPopularity; // 0x00000714 length: 4
            undefined1 padding_0x718[4]; // 0x00000718 length: 4
            int field1388_0x71c; // 0x0000071C length: 4
            int field1389_0x720; // 0x00000720 length: 4
            int traderRelated1; // 0x00000724 length: 4
            int traderRelatedCounter2; // 0x00000728 length: 4
            int traderRelatedCounter1; // 0x0000072C length: 4
            int traderRelated2; // 0x00000730 length: 4
            int field1394_0x734; // 0x00000734 length: 4
            undefined1 padding_0x738[72]; // 0x00000738 length: 72
            BuySellPair copyOfBuyAndSalesPrice[25]; // 0x00000780 length: 200
            BuySellPair buyAndSalesPriceArray[25]; // 0x00000848 length: 200
            int unknownResouceFlagArray1[25]; // 0x00000910 length: 100
            int unknownResourceFlagArray2[25]; // 0x00000974 length: 100
            int isResourceTradeable[25]; // 0x000009D8 length: 100
            int field1472_0xa3c; // 0x00000A3C length: 4
            short deerSpawnLocationsXY[4][2]; // 0x00000A40 length: 16
            int field1474_0xa50; // 0x00000A50 length: 4
            undefined1 padding_0xa54[800]; // 0x00000A54 length: 800
            BOOLEnum gameOver; // 0x00000D74 length: 4
            int unknownCountdown01; // 0x00000D78 length: 4
            int euroRecruitable[7]; // 0x00000D7C length: 28
            int euroRecruitableCopy_index_0; // 0x00000D98 length: 4
            int euroRecruitableCopy_index_1_b; // 0x00000D9C length: 4
            int euroRecruitableCopy_index_2; // 0x00000DA0 length: 4
            int euroRecruitableCopy_index_3_b; // 0x00000DA4 length: 4
            int field2282_0xda8; // 0x00000DA8 length: 4
            int euroRecruitableCopy_index_6_a; // 0x00000DAC length: 4
            int euroRecruitableCopy_index_1_a; // 0x00000DB0 length: 4
            int euroRecruitableCopy_index_3_a_and_6_b; // 0x00000DB4 length: 4
            int euroRecruitableCopy_index_6_c; // 0x00000DB8 length: 4
            int playerTeams[9]; // 0x00000DBC length: 36
            int difficulty; // 0x00000DE0 length: 4
            short scenarioRationsSetting; // 0x00000DE4 length: 2
            short scenarioTaxesSetting; // 0x00000DE6 length: 2
            short scenarioGold; // 0x00000DE8 length: 2
            short editScenarioExtraOptions; // 0x00000DEA length: 2
            short field2293_0xdec; // 0x00000DEC length: 2
            short field2294_0xdee; // 0x00000DEE length: 2
            short field2295_0xdf0[4][2]; // 0x00000DF0 length: 16
            short field2296_0xe00; // 0x00000E00 length: 2
            short field2297_0xe02; // 0x00000E02 length: 2
            short playerPopulationStatistics[9][300]; // 0x00000E04 length: 5400
            int populationIndex; // 0x0000231C length: 4
            undefined1 padding_0x2320[816]; // 0x00002320 length: 816
            int signpostsMapEdgeDataCounter; // 0x00002650 length: 4
            int field3117_0x2654; // 0x00002654 length: 4
            int field3118_0x2658; // 0x00002658 length: 4
            int field3119_0x265c; // 0x0000265C length: 4
            int field3120_0x2660; // 0x00002660 length: 4
            int field3121_0x2664; // 0x00002664 length: 4
            int field3122_0x2668; // 0x00002668 length: 4
            int field3123_0x266c; // 0x0000266C length: 4
            int field3124_0x2670; // 0x00002670 length: 4
            int field3125_0x2674; // 0x00002674 length: 4
            int field3126_0x2678; // 0x00002678 length: 4
            int field3127_0x267c; // 0x0000267C length: 4
            int field3128_0x2680; // 0x00002680 length: 4
            int field3129_0x2684; // 0x00002684 length: 4
            int field3130_0x2688; // 0x00002688 length: 4
            int field3131_0x268c; // 0x0000268C length: 4
            int field3132_0x2690; // 0x00002690 length: 4
            int field3133_0x2694; // 0x00002694 length: 4
            int field3134_0x2698; // 0x00002698 length: 4
            int field3135_0x269c; // 0x0000269C length: 4
            int field3136_0x26a0; // 0x000026A0 length: 4
            int field3137_0x26a4; // 0x000026A4 length: 4
            int field3138_0x26a8; // 0x000026A8 length: 4
            int field3139_0x26ac; // 0x000026AC length: 4
            int field3140_0x26b0; // 0x000026B0 length: 4
            int field3141_0x26b4; // 0x000026B4 length: 4
            int field3142_0x26b8; // 0x000026B8 length: 4
            int field3143_0x26bc; // 0x000026BC length: 4
            int field3144_0x26c0; // 0x000026C0 length: 4
            int field3145_0x26c4; // 0x000026C4 length: 4
            int field3146_0x26c8; // 0x000026C8 length: 4
            int field3147_0x26cc; // 0x000026CC length: 4
            int field3148_0x26d0; // 0x000026D0 length: 4
            int field3149_0x26d4; // 0x000026D4 length: 4
            int field3150_0x26d8; // 0x000026D8 length: 4
            int field3151_0x26dc; // 0x000026DC length: 4
            int field3152_0x26e0; // 0x000026E0 length: 4
            int field3153_0x26e4; // 0x000026E4 length: 4
            int field3154_0x26e8; // 0x000026E8 length: 4
            int field3155_0x26ec; // 0x000026EC length: 4
            int field3156_0x26f0; // 0x000026F0 length: 4
            int field3157_0x26f4; // 0x000026F4 length: 4
            int field3158_0x26f8; // 0x000026F8 length: 4
            int field3159_0x26fc; // 0x000026FC length: 4
            int field3160_0x2700; // 0x00002700 length: 4
            int field3161_0x2704; // 0x00002704 length: 4
            int field3162_0x2708; // 0x00002708 length: 4
            int field3163_0x270c; // 0x0000270C length: 4
            int field3164_0x2710; // 0x00002710 length: 4
            int field3165_0x2714; // 0x00002714 length: 4
            int field3166_0x2718; // 0x00002718 length: 4
            int field3167_0x271c; // 0x0000271C length: 4
            int field3168_0x2720; // 0x00002720 length: 4
            int field3169_0x2724; // 0x00002724 length: 4
            int field3170_0x2728; // 0x00002728 length: 4
            int field3171_0x272c; // 0x0000272C length: 4
            int field3172_0x2730; // 0x00002730 length: 4
            int field3173_0x2734; // 0x00002734 length: 4
            int field3174_0x2738; // 0x00002738 length: 4
            int field3175_0x273c; // 0x0000273C length: 4
            int field3176_0x2740; // 0x00002740 length: 4
            int field3177_0x2744; // 0x00002744 length: 4
            int field3178_0x2748; // 0x00002748 length: 4
            int field3179_0x274c; // 0x0000274C length: 4
            int field3180_0x2750; // 0x00002750 length: 4
            int field3181_0x2754; // 0x00002754 length: 4
            int field3182_0x2758; // 0x00002758 length: 4
            int field3183_0x275c; // 0x0000275C length: 4
            int field3184_0x2760; // 0x00002760 length: 4
            int field3185_0x2764; // 0x00002764 length: 4
            int field3186_0x2768; // 0x00002768 length: 4
            int field3187_0x276c; // 0x0000276C length: 4
            int field3188_0x2770; // 0x00002770 length: 4
            int gameEventRelatedCountdown; // 0x00002774 length: 4
            int unk_signpostDistance; // 0x00002778 length: 4
            int field3191_0x277c; // 0x0000277C length: 4
            short rabbitSpawnXY[4][2]; // 0x00002780 length: 16
            int field3193_0x2790; // 0x00002790 length: 4
            short camelSpawnXY[4][2]; // 0x00002794 length: 16
            int field3195_0x27a4; // 0x000027A4 length: 4
            int field3196_0x27a8; // 0x000027A8 length: 4
            int field3197_0x27ac; // 0x000027AC length: 4
            int somePlayerID; // 0x000027B0 length: 4
            short playerIsAlive[9]; // 0x000027B4 length: 18
            short field3200_0x27c6; // 0x000027C6 length: 2
            int field3201_0x27c8; // 0x000027C8 length: 4
            int deerCount; // 0x000027CC length: 4
            int armySizeLimit; // 0x000027D0 length: 4
            short field3204_0x27d4; // 0x000027D4 length: 2
            short field3205_0x27d6; // 0x000027D6 length: 2
            short yearCopy; // 0x000027D8 length: 2
            short monthCopy; // 0x000027DA length: 2
            short field3208_0x27dc; // 0x000027DC length: 2
            short field3209_0x27de; // 0x000027DE length: 2
            int noDogs; // 0x000027E0 length: 4
            int field3211_0x27e4; // 0x000027E4 length: 4
            int field3212_0x27e8; // 0x000027E8 length: 4
            int noCowThrowing; // 0x000027EC length: 4
            int totalNoRushTicks; // 0x000027F0 length: 4
            int noRushTicksLeftUnk; // 0x000027F4 length: 4
            int rawDeerCount; // 0x000027F8 length: 4
            undefined1 padding_0x27fc[252]; // 0x000027FC length: 252
            int mercRecruitable[7]; // 0x000028F8 length: 28
            undefined1 padding_0x2914[4]; // 0x00002914 length: 4
            int signpostIDs[8]; // 0x00002918 length: 32
            undefined1 padding_0x2938[32]; // 0x00002938 length: 32
            int signpostEntryData[8][4]; // 0x00002958 length: 128
            undefined1 padding_0x29d8[124]; // 0x000029D8 length: 124
            int strongWalls; // 0x00002A54 length: 4
            XYTileObject signpostsMapEdge[7][50]; // 0x00002A58 length: 5600
            undefined1 padding_0x4038[480]; // 0x00004038 length: 480
            Point8IntXY aiTribeMoveDestinationXYPairArray1[5][8]; // 0x00004218 length: 320
            XYPair unitMoveDestinationXYPairs[8][40]; // 0x00004358 length: 2560
            AttackVector attackVectors[9][50]; // 0x00004D58 length: 7200
            undefined1 padding_0x6978[800]; // 0x00006978 length: 800
            int playerGroupArray[9]; // 0x00006C98 length: 36
            undefined1 padding_0x6cbc[4]; // 0x00006CBC length: 4
            int playerBuildingInfoIndex[9]; // 0x00006CC0 length: 36
            int playerEnemyBuildingIDs[9][2000]; // 0x00006CE4 length: 72000
            int playerEnemyBuildingUID[9][2000]; // 0x00018624 length: 72000
            int playerEnemenyUnitUIDShortList[9][2500]; // 0x00029F64 length: 90000
            int dayTicks; // 0x0003FEF4 length: 4
            int weekTicks; // 0x0003FEF8 length: 4
            int monthTicks; // 0x0003FEFC length: 4
            byte unused_0x3ff00[80]; // 0x0003FF00 length: 80
            int startingTroops[8][20]; // 0x0003FF50 length: 640

        } MapAndTimeState;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(MapAndTimeState) == 262608, MapAndTimeState);
    } // namespace State
} // namespace Game
} // namespace OpenSHC
