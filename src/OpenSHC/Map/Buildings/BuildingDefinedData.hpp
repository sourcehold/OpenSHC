/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Buildings/BuildingDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Common/TruncatedInt.hpp"
#include "OpenSHC/Coordinates/XYPairShort.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeInt.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/Util/FunctionTypes/NoArgCallback.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Common::TruncatedInt;
        using OpenSHC::Coordinates::XYPairShort;
        using OpenSHC::Map::Buildings::BuildingTypeInt;
        using OpenSHC::Map::Buildings::BuildingTypeShort;
        using OpenSHC::Map::Navigation::Algorithms::XYPair;
        using OpenSHC::Map::Units::UnitTypeInt;
        using OpenSHC::Util::FunctionTypes::NoArgCallback;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
        // SIZE: 0x0000B0F4
        typedef struct BuildingDefinedData {

            char FletchersWorkshopAnimationFrames1[52]; // 0x00000000 length: 52
            NoArgCallback* BuildingUpdateFunctions[110]; // 0x00000034 length: 440
            BuildingTypeShort BuildingPrioritiesWhenNoFire[32]; // 0x000001EC length: 64
            BuildingTypeShort BuildingPrioritiesWhenFire[32]; // 0x0000022C length: 64
            UnitTypeInt WorkerTypeForBuildingType[110]; // 0x0000026C length: 440
            BOOLEnum ABuildingTypeValueArray[110]; // 0x00000424 length: 440
            int BuildingPlacement_HeightLimit[110]; // 0x000005DC length: 440
            int BuildingPlacement_MaxHeightDifference[110]; // 0x00000794 length: 440
            int BuildingPlacement_Property_3[110]; // 0x0000094C length: 440
            int BuildingPlacement_Property_4[110]; // 0x00000B04 length: 440
            int BuildingPlacement_Property_5[110]; // 0x00000CBC length: 440
            int BuildingPlacement_Property_6[110]; // 0x00000E74 length: 440
            int BuildingPlacement_Property_7[110]; // 0x0000102C length: 440
            TruncatedInt EmployeeCountPerBuildingType[110]; // 0x000011E4 length: 440
            int StorageLimitResourceTypeArray[26]; // 0x0000139C length: 104
            TruncatedInt field15_0x1404[110]; // 0x00001404 length: 440
            TruncatedInt BuildingFlag1Defaults[110]; // 0x000015BC length: 440
            BOOLEnum field17_0x1774[110]; // 0x00001774 length: 440
            TruncatedInt BuildingFlag4Defaults[110]; // 0x0000192C length: 440
            int BuildingTypeHasHealth[110]; // 0x00001AE4 length: 440
            int BuildingIsGateHouseArray[110]; // 0x00001C9C length: 440
            int BuildingIsKeepArray[110]; // 0x00001E54 length: 440
            BOOLEnum IsGateOrTowerArray[110]; // 0x0000200C length: 440
            BOOLEnum field23_0x21c4[110]; // 0x000021C4 length: 440
            TruncatedInt BuildingFlag2Defaults[110]; // 0x0000237C length: 440
            int BuildingShowRubbleWhenDestroyed[110]; // 0x00002534 length: 440
            int BuildingTypeOwnable[110]; // 0x000026EC length: 440
            TruncatedInt BuildingHP[110]; // 0x000028A4 length: 440
            BuildingTypeInt StorageBuildingTypeArray[26]; // 0x00002A5C length: 104
            TruncatedInt BuildingNumberOfPopulationProvided[110]; // 0x00002AC4 length: 440
            int field30_0x2c7c[88]; // 0x00002C7C length: 352
            int WheatFieldTile_Unknown[36]; // 0x00002DDC length: 144
            TruncatedInt Building_SpriteSheet_ID_Array_1[110]; // 0x00002E6C length: 440
            int Building_Sprite_ID_Array_1[110]; // 0x00003024 length: 440
            int Building_Sprite_ID_Array_2[110]; // 0x000031DC length: 440
            int VisuallyActiveSpriteIDOffsets[110]; // 0x00003394 length: 440
            int GFXOffsets[110]; // 0x0000354C length: 440
            int GFXOffsets3[110]; // 0x00003704 length: 440
            TruncatedInt SpriteIDs2[110]; // 0x000038BC length: 440
            short SpriteOffsets1[110][2][2]; // 0x00003A74 length: 880
            int AnimAdvanceThrottles[110]; // 0x00003DE4 length: 440
            int BuildingHeights[110]; // 0x00003F9C length: 440
            int BuildingDestroyedScoreWeight[110]; // 0x00004154 length: 440
            byte field43_0x430c[312]; // 0x0000430C length: 312
            char FletcherWorkshopAnimationCycle[160]; // 0x00004444 length: 160
            byte field45_0x44e4[400]; // 0x000044E4 length: 400
            byte field46_0x4674[608]; // 0x00004674 length: 608
            char FletchersWorkshopAnimationFrames2[56]; // 0x000048D4 length: 56
            char ArmorersWorkshopAnimationFrames1[448]; // 0x0000490C length: 448
            char ArmorersWorkshopAnimationFrames2[112]; // 0x00004ACC length: 112
            char ArmorersWorkshopAnimationFrames3[20]; // 0x00004B3C length: 20
            char HuntersPostAnimationFrames1[24]; // 0x00004B50 length: 24
            char HuntersPostAnimationFrames2[40]; // 0x00004B68 length: 40
            char HuntersPostAnimationFrames3[28]; // 0x00004B90 length: 28
            char WoodcuttersHutAnimationFrames[104]; // 0x00004BAC length: 104
            char BakeryAnimationFrames1[396]; // 0x00004C14 length: 396
            char BakeryAnimationFrames2[20]; // 0x00004DA0 length: 20
            char BreweryAnimationFrames1[420]; // 0x00004DB4 length: 420
            char BreweryAnimationFrames2[44]; // 0x00004F58 length: 44
            char BreweryAnimationFrames3[48]; // 0x00004F84 length: 48
            char BreweryAnimationFrames4[36]; // 0x00004FB4 length: 36
            char BreweryAnimationFrames5[36]; // 0x00004FD8 length: 36
            char BlacksmithsWorkshopAnimationFrames1[20]; // 0x00004FFC length: 20
            char BlacksmithsWorkshopAnimationFrames2[44]; // 0x00005010 length: 44
            char BlacksmithsWorkshopAnimationFrames3[88]; // 0x0000503C length: 88
            char BlacksmithsWorkshopAnimationFrames4[44]; // 0x00005094 length: 44
            char BlacksmithsWorkshopAnimationFrames5[12]; // 0x000050C0 length: 12
            char BlacksmithsWorkshopAnimationFrames6[64]; // 0x000050CC length: 64
            char BlacksmithsWorkshopAnimationFrames7[56]; // 0x0000510C length: 56
            char BlacksmithsWorkshopAnimationFrames8[72]; // 0x00005144 length: 72
            char BlacksmithsWorkshopAnimationFrames9[80]; // 0x0000518C length: 80
            char BlacksmithsWorkshopAnimationFrames10[244]; // 0x000051DC length: 244
            char BlacksmithsWorkshopAnimationFrames11[36]; // 0x000052D0 length: 36
            char BlacksmithsWorkshopAnimationFrames12[112]; // 0x000052F4 length: 112
            char PoleturnersWorkshopAnimationFrames1[88]; // 0x00005364 length: 88
            byte field75_0x53bc[200]; // 0x000053BC length: 200
            char PoleturnersWorkshopAnimationFrames2[36]; // 0x00005484 length: 36
            char PoleturnersWorkshopAnimationFrames3[36]; // 0x000054A8 length: 36
            byte field78_0x54cc[144]; // 0x000054CC length: 144
            char PoleturnersWorkshopAnimationFrames4[72]; // 0x0000555C length: 72
            char PoleturnersWorkshopAnimationFrames5[28]; // 0x000055A4 length: 28
            char SecondaryOverlayAnimationFrames[20]; // 0x000055C0 length: 20
            char BreweryAnimationFrames6[260]; // 0x000055D4 length: 260
            char AnimTannerSolitary[44]; // 0x000056D8 length: 44
            char AnimTanner[12]; // 0x00005704 length: 12
            char AnimTanner3[28]; // 0x00005710 length: 28
            char AnimTanner4[32]; // 0x0000572C length: 32
            char AnimTannerSolitary2[56]; // 0x0000574C length: 56
            char AnimTanner2[16]; // 0x00005784 length: 16
            char TannersWorkshopAnimationFrames1[92]; // 0x00005794 length: 92
            char TannersWorkshopAnimationFrames2[36]; // 0x000057F0 length: 36
            char AnimTanner5[40]; // 0x00005814 length: 40
            char AnimTannerSolitary4[152]; // 0x0000583C length: 152
            char AnimTanner6[152]; // 0x000058D4 length: 152
            char AnimTanner7[172]; // 0x0000596C length: 172
            char TunnelAnimationFrames[52]; // 0x00005A18 length: 52
            char CampGroundAnimationFrames[36]; // 0x00005A4C length: 36
            char QuarryAnimationFrames1[28]; // 0x00005A70 length: 28
            char QuarryAnimationFrames2[64]; // 0x00005A8C length: 64
            char QuarryAnimationFrames3[20]; // 0x00005ACC length: 20
            char QuarryAnimationFrames4[24]; // 0x00005AE0 length: 24
            char QuarryAnimationFrames5[28]; // 0x00005AF8 length: 28
            char QuarryAnimationFrames6[56]; // 0x00005B14 length: 56
            char SomeAnimationNumbersUnk[24]; // 0x00005B4C length: 24
            char QuarryAnimationFrames7[32]; // 0x00005B64 length: 32
            char QuarryAnimationFrames8[16]; // 0x00005B84 length: 16
            char QuarryAnimationFrames9[64]; // 0x00005B94 length: 64
            char QuarryAnimationFrames10[112]; // 0x00005BD4 length: 112
            char QuarryAnimationFrames11[20]; // 0x00005C44 length: 20
            char QuarryAnimationFrames12[40]; // 0x00005C58 length: 40
            char QuarryAnimationFrames13[60]; // 0x00005C80 length: 60
            char QuarryAnimationFrames14[72]; // 0x00005CBC length: 72
            char QuarryAnimationFrames15[24]; // 0x00005D04 length: 24
            char QuarryAnimationFrames16[64]; // 0x00005D1C length: 64
            char QuarryAnimationFrames17[16]; // 0x00005D5C length: 16
            char QuarryAnimationFrames18[376]; // 0x00005D6C length: 376
            char QuarryAnimationFrames19[264]; // 0x00005EE4 length: 264
            char QuarryAnimationFrames20[304]; // 0x00005FEC length: 304
            char QuarryAnimationFrames21[384]; // 0x0000611C length: 384
            char IronMineAnimationFrames1[88]; // 0x0000629C length: 88
            char IronMineAnimationFrames2[80]; // 0x000062F4 length: 80
            char IronMineAnimationFrames3[472]; // 0x00006344 length: 472
            char IronMineAnimationFrames4[112]; // 0x0000651C length: 112
            char IronMineAnimationFrames5[104]; // 0x0000658C length: 104
            char IronMineAnimationFrames6[184]; // 0x000065F4 length: 184
            char IronMineAnimationFrames7[24]; // 0x000066AC length: 24
            char IronMineAnimationFrames8[12]; // 0x000066C4 length: 12
            char IronMineAnimationFrames9[60]; // 0x000066D0 length: 60
            char IronMineAnimationFrames10[452]; // 0x0000670C length: 452
            char IronMineAnimationFrames11[36]; // 0x000068D0 length: 36
            char IronMineAnimationFrames12[84]; // 0x000068F4 length: 84
            char PitchRigAnimationFrames1[52]; // 0x00006948 length: 52
            char PitchRigAnimationFrames2[56]; // 0x0000697C length: 56
            char PitchRigAnimationFrames3[104]; // 0x000069B4 length: 104
            char MillAnimationFrames1[16]; // 0x00006A1C length: 16
            char MillAnimationFrames2[16]; // 0x00006A2C length: 16
            char MillAnimationFrames3[16]; // 0x00006A3C length: 16
            char MillAnimationFrames4[136]; // 0x00006A4C length: 136
            char MillAnimationFrames5[16]; // 0x00006AD4 length: 16
            char DrawBridgeAnimationFrames1[32]; // 0x00006AE4 length: 32
            char DrawBridgeAnimationFrames2[36]; // 0x00006B04 length: 36
            char GateHouseLargeAnimationFrames[28]; // 0x00006B28 length: 28
            char GateHouseOverlayAnimationFrames[32]; // 0x00006B44 length: 32
            char DairyFarmAnimationFrames1[264]; // 0x00006B64 length: 264
            char DairyFarmAnimationFrames2[664]; // 0x00006C6C length: 664
            char DairyFarmAnimationFrames3[448]; // 0x00006F04 length: 448
            char DairyFarmAnimationFrames4[152]; // 0x000070C4 length: 152
            char StablesAnimationFrames[644]; // 0x0000715C length: 644
            char OilSmelterAnimationFrames1[52]; // 0x000073E0 length: 52
            char OilSmelterAnimationFrames2[80]; // 0x00007414 length: 80
            char OilSmelterAnimationFrames3[48]; // 0x00007464 length: 48
            char OilSmelterAnimationFrames4[48]; // 0x00007494 length: 48
            char OilSmelterAnimationFrames5[48]; // 0x000074C4 length: 48
            char OilSmelterAnimationFrames6[48]; // 0x000074F4 length: 48
            char OilSmelterAnimationFrames7[48]; // 0x00007524 length: 48
            char OilSmelterAnimationFrames8[48]; // 0x00007554 length: 48
            char OilSmelterAnimationFrames9[40]; // 0x00007584 length: 40
            char OilSmelterAnimationFrames10[80]; // 0x000075AC length: 80
            char BadBuildingGallowsAnimationFrames[40]; // 0x000075FC length: 40
            char BadBuildingStocksAnimationFrames[72]; // 0x00007624 length: 72
            char BadBuildingDungeonAnimationFrames[80]; // 0x0000766C length: 80
            char BadBuildingDunkingStoolAnimationFrames[172]; // 0x000076BC length: 172
            char BadBuildingGibbetAnimationFrames[36]; // 0x00007768 length: 36
            char BadBuildingBurningStakeAnimationFrames[88]; // 0x0000778C length: 88
            char BadBuildingStretchingRackAnimationFrames[160]; // 0x000077E4 length: 160
            char BadBuildingChoppingBlockAnimationFrames[200]; // 0x00007884 length: 200
            char DogCageAnimationFrames[40]; // 0x0000794C length: 40
            char GoodBuildingMaypoleAnimationFrames1[80]; // 0x00007974 length: 80
            char GoodBuildingMaypoleAnimationFrames2[80]; // 0x000079C4 length: 80
            char GoodBuildingDancingBearAnimationFrames[344]; // 0x00007A14 length: 344
            char AnimMarketPlace[104]; // 0x00007B6C length: 104
            char ApothecaryAnimationFrames[104]; // 0x00007BD4 length: 104
            char InnAnimationFrames1[88]; // 0x00007C3C length: 88
            char InnAnimationFrames2[136]; // 0x00007C94 length: 136
            char InnAnimationFrames3[140]; // 0x00007D1C length: 140
            char InnAnimationFrames4[36]; // 0x00007DA8 length: 36
            char InnAnimationFrames5[80]; // 0x00007DCC length: 80
            char SharedOverlayAnimationFrames[52]; // 0x00007E1C length: 52
            int BuildingAccessibleTilesCountForOneLarger[15]; // 0x00007E50 length: 60
            XYPair field179_0x7e8c[8]; // 0x00007E8C length: 64
            XYPair field180_0x7ecc[12]; // 0x00007ECC length: 96
            XYPair field181_0x7f2c[16]; // 0x00007F2C length: 128
            XYPair field182_0x7fac[20]; // 0x00007FAC length: 160
            XYPair field183_0x804c[24]; // 0x0000804C length: 192
            XYPair field184_0x810c[28]; // 0x0000810C length: 224
            XYPair field185_0x81ec[32]; // 0x000081EC length: 256
            XYPair field186_0x82ec[36]; // 0x000082EC length: 288
            XYPair field187_0x840c[40]; // 0x0000840C length: 320
            XYPair field188_0x854c[44]; // 0x0000854C length: 352
            XYPair field189_0x86ac[48]; // 0x000086AC length: 384
            XYPair field190_0x882c[52]; // 0x0000882C length: 416
            XYPair field191_0x89cc[116]; // 0x000089CC length: 928
            int BuildingAccessibleTilesCount[15]; // 0x00008D6C length: 60
            XYPair field193_0x8da8[4]; // 0x00008DA8 length: 32
            undefined1 padding_0x8dc8[4]; // 0x00008DC8 length: 4
            XYPair field198_0x8dcc[8]; // 0x00008DCC length: 64
            XYPair field199_0x8e0c[12]; // 0x00008E0C length: 96
            XYPair field200_0x8e6c[16]; // 0x00008E6C length: 128
            XYPair field201_0x8eec[20]; // 0x00008EEC length: 160
            XYPair field202_0x8f8c[24]; // 0x00008F8C length: 192
            XYPair field203_0x904c[28]; // 0x0000904C length: 224
            XYPair field204_0x912c[32]; // 0x0000912C length: 256
            XYPair field205_0x922c[36]; // 0x0000922C length: 288
            XYPair field206_0x934c[40]; // 0x0000934C length: 320
            XYPair field207_0x948c[44]; // 0x0000948C length: 352
            XYPair field208_0x95ec[48]; // 0x000095EC length: 384
            XYPair field209_0x976c[52]; // 0x0000976C length: 416
            XYPair field210_0x990c[56]; // 0x0000990C length: 448
            undefined1 padding_0x9acc[156]; // 0x00009ACC length: 156
            int GardenVariations[12]; // 0x00009B68 length: 48
            int UnknownVariations[13]; // 0x00009B98 length: 52
            int SomeSpriteArray1[7]; // 0x00009BCC length: 28
            int CesspitVariations[4]; // 0x00009BE8 length: 16
            int StatueVariations[5]; // 0x00009BF8 length: 20
            int ShrineVariations[5]; // 0x00009C0C length: 20
            int PondVariations[5]; // 0x00009C20 length: 20
            XYPairShort PlayerDataUnknownStructureRelatedArray_3[2][24]; // 0x00009C34 length: 192
            int PlayerDataUnknownStructureRelatedArray_1[6]; // 0x00009CF4 length: 24
            int PlayerDataUnknownStructureRelatedArray_2[6][3]; // 0x00009D0C length: 72
            XYPairShort SearchRelatedXYOffsets_1[49]; // 0x00009D54 length: 196
            undefined1 padding_0x9e18[4]; // 0x00009E18 length: 4
            int field382_0x9e1c[7][4]; // 0x00009E1C length: 112
            int field383_0x9e8c[4]; // 0x00009E8C length: 16
            int field384_0x9e9c[7][4]; // 0x00009E9C length: 112
            undefined1 padding_0x9f0c[16]; // 0x00009F0C length: 16
            int field401_0x9f1c[2][4]; // 0x00009F1C length: 32
            XYPairShort TunnelersGuildParadegroundLocationOffsets[25]; // 0x00009F3C length: 100
            undefined1 padding_0x9fa0[4]; // 0x00009FA0 length: 4
            XYPairShort EngineersParagroundOffsets[25]; // 0x00009FA4 length: 100
            undefined1 padding_0xa008[4]; // 0x0000A008 length: 4
            XYPairShort field412_0xa00c[16]; // 0x0000A00C length: 64
            int SpawnUnitProperties[16][13]; // 0x0000A04C length: 832
            int DrawBridgeAnimationFrames[4]; // 0x0000A38C length: 16
            int field415_0xa39c[52]; // 0x0000A39C length: 208
            int field416_0xa46c[52]; // 0x0000A46C length: 208
            int field417_0xa53c[26]; // 0x0000A53C length: 104
            int field418_0xa5a4[102]; // 0x0000A5A4 length: 408
            int field419_0xa73c[16]; // 0x0000A73C length: 64
            int field420_0xa77c[24]; // 0x0000A77C length: 96
            int field421_0xa7dc[32]; // 0x0000A7DC length: 128
            int BuildingCost[110][5]; // 0x0000A85C length: 2200

        } BuildingDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(BuildingDefinedData) == 45300, BuildingDefinedData);
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
