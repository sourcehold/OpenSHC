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

            byte fletchersWorkshopCfg_0x0[52]; // 0x00000000 length: 52
            NoArgCallback* PTR_BuildingUpdateFunctions; // 0x00000034 length: 4
            undefined1 padding_0x38[436]; // 0x00000038 length: 436
            BuildingTypeShort DAT_BuildingPrioritiesWhenNoFire[32]; // 0x000001EC length: 64
            BuildingTypeShort DAT_BuildingPrioritiesWhenFire[32]; // 0x0000022C length: 64
            UnitTypeInt DAT_WorkerTypeForBuildingType[110]; // 0x0000026C length: 440
            BOOLEnum DAT_ABuildingTypeValueArray[110]; // 0x00000424 length: 440
            int DAT_BuildingPlacement_HeightLimit[110]; // 0x000005DC length: 440
            int DAT_BuildingPlacement_MaxHeightDifference[110]; // 0x00000794 length: 440
            int DAT_BuildingPlacement_Property_3[110]; // 0x0000094C length: 440
            int DAT_BuildingPlacement_Property_4[110]; // 0x00000B04 length: 440
            int DAT_BuildingPlacement_Property_5[110]; // 0x00000CBC length: 440
            int DAT_BuildingPlacement_Property_6[110]; // 0x00000E74 length: 440
            int DAT_BuildingPlacement_Property_7[110]; // 0x0000102C length: 440
            TruncatedInt DAT_EmployeeCountPerBuildingType[110]; // 0x000011E4 length: 440
            int DAT_StorageLimitResourceTypeArray[26]; // 0x0000139C length: 104
            TruncatedInt buildingTypeProp_0x1404[110]; // 0x00001404 length: 440
            TruncatedInt buildingTypeProp_0x15bc[110]; // 0x000015BC length: 440
            BOOLEnum pathLinkageCfg_0x1774[110]; // 0x00001774 length: 440
            TruncatedInt buildingTypeProp_0x192c[110]; // 0x0000192C length: 440
            int DAT_BuildingTypeHasHealth[110]; // 0x00001AE4 length: 440
            int DAT_BuildingIsGateHouseArray[110]; // 0x00001C9C length: 440
            int DAT_BuildingIsKeepArray[110]; // 0x00001E54 length: 440
            BOOLEnum DAT_IsGateOrTowerArray[110]; // 0x0000200C length: 440
            BOOLEnum field23_0x21c4[110]; // 0x000021C4 length: 440
            TruncatedInt buildingTypeProp_0x237c[110]; // 0x0000237C length: 440
            int DAT_BuildingShowRubbleWhenDestroyed[110]; // 0x00002534 length: 440
            int DAT_BuildingTypeOwnable[110]; // 0x000026EC length: 440
            TruncatedInt DAT_BUILDING_HP[110]; // 0x000028A4 length: 440
            BuildingTypeInt DAT_StorageBuildingTypeArray[26]; // 0x00002A5C length: 104
            TruncatedInt DAT_BUILDING_NumberOfPopulationProvided[110]; // 0x00002AC4 length: 440
            int field30_0x2c7c[88]; // 0x00002C7C length: 352
            int DAT_WheatFieldTile_Unknown[36]; // 0x00002DDC length: 144
            TruncatedInt DAT_Building_SpriteSheet_ID_Array_1[110]; // 0x00002E6C length: 440
            int DAT_Building_Sprite_ID_Array_1[110]; // 0x00003024 length: 440
            int DAT_Building_Sprite_ID_Array_2[110]; // 0x000031DC length: 440
            int visuallyActiveSpriteIDOffsets[110]; // 0x00003394 length: 440
            int gfxOffsets[110]; // 0x0000354C length: 440
            int gfxOffsets3[110]; // 0x00003704 length: 440
            TruncatedInt spriteIDs2[110]; // 0x000038BC length: 440
            short tannersWorkshopCfg_0x3a74[110][2][2]; // 0x00003A74 length: 880
            int buildingTypeProp_0x3de4[110]; // 0x00003DE4 length: 440
            int DAT_BuildingHeights[110]; // 0x00003F9C length: 440
            int buildingDamageCfg_0x4154[110]; // 0x00004154 length: 440
            byte fletchersWorkshopCfg_0x430c[312]; // 0x0000430C length: 312
            byte DAT_FletcherWorkshopAnimationCycle[160]; // 0x00004444 length: 160
            byte fletchersWorkshopCfg_0x44e4[400]; // 0x000044E4 length: 400
            byte fletchersWorkshopCfg_0x4674[608]; // 0x00004674 length: 608
            byte fletchersWorkshopCfg_0x48d4[56]; // 0x000048D4 length: 56
            byte armorersWorkshopCfg_0x490c[448]; // 0x0000490C length: 448
            byte armorersWorkshopCfg_0x4acc[112]; // 0x00004ACC length: 112
            byte armorersWorkshopCfg_0x4b3c[20]; // 0x00004B3C length: 20
            byte huntersPostCfg_0x4b50[24]; // 0x00004B50 length: 24
            byte huntersPostCfg_0x4b68[40]; // 0x00004B68 length: 40
            byte huntersPostCfg_0x4b90[28]; // 0x00004B90 length: 28
            byte woodcuttersHutCfg_0x4bac[104]; // 0x00004BAC length: 104
            byte bakeryCfg_0x4c14[396]; // 0x00004C14 length: 396
            byte bakeryCfg_0x4da0[20]; // 0x00004DA0 length: 20
            byte breweryCfg_0x4db4[420]; // 0x00004DB4 length: 420
            byte breweryCfg_0x4f58[44]; // 0x00004F58 length: 44
            byte breweryCfg_0x4f84[48]; // 0x00004F84 length: 48
            byte breweryCfg_0x4fb4[36]; // 0x00004FB4 length: 36
            byte breweryCfg_0x4fd8[36]; // 0x00004FD8 length: 36
            byte blacksmithsWorkshopCfg_0x4ffc[20]; // 0x00004FFC length: 20
            byte blacksmithsWorkshopCfg_0x5010[44]; // 0x00005010 length: 44
            byte blacksmithsWorkshopCfg_0x503c[88]; // 0x0000503C length: 88
            byte blacksmithsWorkshopCfg_0x5094[44]; // 0x00005094 length: 44
            byte blacksmithsWorkshopCfg_0x50c0[12]; // 0x000050C0 length: 12
            byte blacksmithsWorkshopCfg_0x50cc[64]; // 0x000050CC length: 64
            byte blacksmithsWorkshopCfg_0x510c[56]; // 0x0000510C length: 56
            byte blacksmithsWorkshopCfg_0x5144[72]; // 0x00005144 length: 72
            byte blacksmithsWorkshopCfg_0x518c[80]; // 0x0000518C length: 80
            byte blacksmithsWorkshopCfg_0x51dc[244]; // 0x000051DC length: 244
            byte blacksmithsWorkshopCfg_0x52d0[36]; // 0x000052D0 length: 36
            byte blacksmithsWorkshopCfg_0x52f4[112]; // 0x000052F4 length: 112
            byte poleturnersWorkshopCfg_0x5364[88]; // 0x00005364 length: 88
            byte poleturnersWorkshopCfg_0x53bc[200]; // 0x000053BC length: 200
            byte poleturnersWorkshopCfg_0x5484[36]; // 0x00005484 length: 36
            byte poleturnersWorkshopCfg_0x54a8[36]; // 0x000054A8 length: 36
            byte poleturnersWorkshopCfg_0x54cc[144]; // 0x000054CC length: 144
            byte poleturnersWorkshopCfg_0x555c[72]; // 0x0000555C length: 72
            byte poleturnersWorkshopCfg_0x55a4[28]; // 0x000055A4 length: 28
            byte blacksmithsWorkshopCfg_0x55c0[20]; // 0x000055C0 length: 20
            byte breweryCfg_0x55d4[260]; // 0x000055D4 length: 260
            byte tannersWorkshopCfg_0x56d8[44]; // 0x000056D8 length: 44
            byte tannersWorkshopCfg_0x5704[12]; // 0x00005704 length: 12
            byte tannersWorkshopCfg_0x5710[28]; // 0x00005710 length: 28
            byte tannersWorkshopCfg_0x572c[32]; // 0x0000572C length: 32
            byte tannersWorkshopCfg_0x574c[56]; // 0x0000574C length: 56
            byte tannersWorkshopCfg_0x5784[16]; // 0x00005784 length: 16
            byte tannersWorkshopCfg_0x5794[92]; // 0x00005794 length: 92
            byte tannersWorkshopCfg_0x57f0[36]; // 0x000057F0 length: 36
            byte tannersWorkshopCfg_0x5814[40]; // 0x00005814 length: 40
            byte tannersWorkshopCfg_0x583c[152]; // 0x0000583C length: 152
            byte tannersWorkshopCfg_0x58d4[152]; // 0x000058D4 length: 152
            byte tannersWorkshopCfg_0x596c[172]; // 0x0000596C length: 172
            byte tunnelCfg_0x5a18[52]; // 0x00005A18 length: 52
            byte campGroundCfg_0x5a4c[36]; // 0x00005A4C length: 36
            byte quarryCfg_0x5a70[28]; // 0x00005A70 length: 28
            byte quarryCfg_0x5a8c[64]; // 0x00005A8C length: 64
            byte quarryCfg_0x5acc[20]; // 0x00005ACC length: 20
            byte quarryCfg_0x5ae0[24]; // 0x00005AE0 length: 24
            byte quarryCfg_0x5af8[28]; // 0x00005AF8 length: 28
            byte quarryCfg_0x5b14[56]; // 0x00005B14 length: 56
            byte PTR_SomeAnimationNumbersUnk[24]; // 0x00005B4C length: 24
            byte quarryCfg_0x5b64[32]; // 0x00005B64 length: 32
            byte quarryCfg_0x5b84[16]; // 0x00005B84 length: 16
            byte quarryCfg_0x5b94[64]; // 0x00005B94 length: 64
            byte quarryCfg_0x5bd4[112]; // 0x00005BD4 length: 112
            byte quarryCfg_0x5c44[20]; // 0x00005C44 length: 20
            byte quarryCfg_0x5c58[40]; // 0x00005C58 length: 40
            byte quarryCfg_0x5c80[60]; // 0x00005C80 length: 60
            byte quarryCfg_0x5cbc[72]; // 0x00005CBC length: 72
            byte quarryCfg_0x5d04[24]; // 0x00005D04 length: 24
            byte quarryCfg_0x5d1c[64]; // 0x00005D1C length: 64
            byte quarryCfg_0x5d5c[16]; // 0x00005D5C length: 16
            byte quarryCfg_0x5d6c[376]; // 0x00005D6C length: 376
            byte quarryCfg_0x5ee4[264]; // 0x00005EE4 length: 264
            byte quarryCfg_0x5fec[304]; // 0x00005FEC length: 304
            byte quarryCfg_0x611c[384]; // 0x0000611C length: 384
            byte ironMineCfg_0x629c[88]; // 0x0000629C length: 88
            byte ironMineCfg_0x62f4[80]; // 0x000062F4 length: 80
            byte ironMineCfg_0x6344[472]; // 0x00006344 length: 472
            byte ironMineCfg_0x651c[112]; // 0x0000651C length: 112
            byte ironMineCfg_0x658c[104]; // 0x0000658C length: 104
            byte ironMineCfg_0x65f4[184]; // 0x000065F4 length: 184
            byte ironMineCfg_0x66ac[24]; // 0x000066AC length: 24
            byte ironMineCfg_0x66c4[12]; // 0x000066C4 length: 12
            byte ironMineCfg_0x66d0[60]; // 0x000066D0 length: 60
            byte ironMineCfg_0x670c[452]; // 0x0000670C length: 452
            byte ironMineCfg_0x68d0[36]; // 0x000068D0 length: 36
            byte ironMineCfg_0x68f4[84]; // 0x000068F4 length: 84
            byte pitchRigCfg_0x6948[52]; // 0x00006948 length: 52
            byte pitchRigCfg_0x697c[56]; // 0x0000697C length: 56
            byte pitchRigCfg_0x69b4[104]; // 0x000069B4 length: 104
            byte millCfg_0x6a1c[16]; // 0x00006A1C length: 16
            byte millCfg_0x6a2c[16]; // 0x00006A2C length: 16
            byte millCfg_0x6a3c[16]; // 0x00006A3C length: 16
            byte millCfg_0x6a4c[136]; // 0x00006A4C length: 136
            byte millCfg_0x6ad4[16]; // 0x00006AD4 length: 16
            byte drawBridgeCfg_0x6ae4[32]; // 0x00006AE4 length: 32
            byte drawBridgeCfg_0x6b04[36]; // 0x00006B04 length: 36
            byte gateHouseLargeCfg_0x6b28[28]; // 0x00006B28 length: 28
            byte gateHouseLargeCfg_0x6b44[32]; // 0x00006B44 length: 32
            byte dairyFarmCfg_0x6b64[264]; // 0x00006B64 length: 264
            byte dairyFarmCfg_0x6c6c[664]; // 0x00006C6C length: 664
            byte dairyFarmCfg_0x6f04[448]; // 0x00006F04 length: 448
            byte dairyFarmCfg_0x70c4[152]; // 0x000070C4 length: 152
            byte stablesCfg_0x715c[644]; // 0x0000715C length: 644
            byte oilSmelterCfg_0x73e0[52]; // 0x000073E0 length: 52
            byte oilSmelterCfg_0x7414[80]; // 0x00007414 length: 80
            byte oilSmelterCfg_0x7464[48]; // 0x00007464 length: 48
            byte oilSmelterCfg_0x7494[48]; // 0x00007494 length: 48
            byte oilSmelterCfg_0x74c4[48]; // 0x000074C4 length: 48
            byte oilSmelterCfg_0x74f4[48]; // 0x000074F4 length: 48
            byte oilSmelterCfg_0x7524[48]; // 0x00007524 length: 48
            byte oilSmelterCfg_0x7554[48]; // 0x00007554 length: 48
            byte oilSmelterCfg_0x7584[40]; // 0x00007584 length: 40
            byte oilSmelterCfg_0x75ac[80]; // 0x000075AC length: 80
            byte badBuildingGallowsCfg_0x75fc[40]; // 0x000075FC length: 40
            byte badBuildingStocksCfg_0x7624[72]; // 0x00007624 length: 72
            byte badBuildingDungeonCfg_0x766c[80]; // 0x0000766C length: 80
            byte badBuildingDunkingStoolCfg_0x76bc[172]; // 0x000076BC length: 172
            byte badBuildingGibbetCfg_0x7768[36]; // 0x00007768 length: 36
            byte badBuildingBurningStakeCfg_0x778c[88]; // 0x0000778C length: 88
            byte badBuildingStretchingRackCfg_0x77e4[160]; // 0x000077E4 length: 160
            byte badBuildingChoppingBlockCfg_0x7884[200]; // 0x00007884 length: 200
            byte dogCageCfg_0x794c[40]; // 0x0000794C length: 40
            byte goodBuildingMaypoleCfg_0x7974[80]; // 0x00007974 length: 80
            byte goodBuildingMaypoleCfg_0x79c4[80]; // 0x000079C4 length: 80
            byte dancingBearCfg_0x7a14[344]; // 0x00007A14 length: 344
            byte ANIM_MarketPlace[104]; // 0x00007B6C length: 104
            byte apothecaryCfg_0x7bd4[104]; // 0x00007BD4 length: 104
            byte innCfg_0x7c3c[88]; // 0x00007C3C length: 88
            byte innCfg_0x7c94[136]; // 0x00007C94 length: 136
            byte innCfg_0x7d1c[140]; // 0x00007D1C length: 140
            byte innCfg_0x7da8[36]; // 0x00007DA8 length: 36
            byte innCfg_0x7dcc[80]; // 0x00007DCC length: 80
            byte woodcuttersHutCfg_0x7e1c[52]; // 0x00007E1C length: 52
            int DAT_BuildingAccessibleTilesCountForOneLarger[15]; // 0x00007E50 length: 60
            XYPair candidateOffsets_0x7e8c[8]; // 0x00007E8C length: 64
            XYPair candidateOffsets_0x7ecc[12]; // 0x00007ECC length: 96
            XYPair candidateOffsets_0x7f2c[16]; // 0x00007F2C length: 128
            XYPair candidateOffsets_0x7fac[20]; // 0x00007FAC length: 160
            XYPair candidateOffsets_0x804c[24]; // 0x0000804C length: 192
            XYPair candidateOffsets_0x810c[28]; // 0x0000810C length: 224
            XYPair candidateOffsets_0x81ec[32]; // 0x000081EC length: 256
            XYPair candidateOffsets_0x82ec[36]; // 0x000082EC length: 288
            XYPair candidateOffsets_0x840c[40]; // 0x0000840C length: 320
            XYPair candidateOffsets_0x854c[44]; // 0x0000854C length: 352
            XYPair candidateOffsets_0x86ac[48]; // 0x000086AC length: 384
            XYPair candidateOffsets_0x882c[52]; // 0x0000882C length: 416
            XYPair candidateOffsets_0x89cc[116]; // 0x000089CC length: 928
            int DAT_BuildingAccessibleTilesCount[15]; // 0x00008D6C length: 60
            XYPair entranceOffsets_0x8da8[4]; // 0x00008DA8 length: 32
            undefined1 padding_0x8dc8[4]; // 0x00008DC8 length: 4
            XYPair entranceOffsets_0x8dcc[8]; // 0x00008DCC length: 64
            XYPair entranceOffsets_0x8e0c[12]; // 0x00008E0C length: 96
            XYPair entranceOffsets_0x8e6c[16]; // 0x00008E6C length: 128
            XYPair entranceOffsets_0x8eec[20]; // 0x00008EEC length: 160
            XYPair entranceOffsets_0x8f8c[24]; // 0x00008F8C length: 192
            XYPair entranceOffsets_0x904c[28]; // 0x0000904C length: 224
            XYPair entranceOffsets_0x912c[32]; // 0x0000912C length: 256
            XYPair entranceOffsets_0x922c[36]; // 0x0000922C length: 288
            XYPair entranceOffsets_0x934c[40]; // 0x0000934C length: 320
            XYPair entranceOffsets_0x948c[44]; // 0x0000948C length: 352
            XYPair entranceOffsets_0x95ec[48]; // 0x000095EC length: 384
            XYPair entranceOffsets_0x976c[52]; // 0x0000976C length: 416
            XYPair field210_0x990c[56]; // 0x0000990C length: 448
            undefined1 padding_0x9acc[156]; // 0x00009ACC length: 156
            int gardenVariations[12]; // 0x00009B68 length: 48
            int unknownVariations[13]; // 0x00009B98 length: 52
            int DAT_SomeSpriteArray1[7]; // 0x00009BCC length: 28
            int cesspitVariations[4]; // 0x00009BE8 length: 16
            int statueVariations[5]; // 0x00009BF8 length: 20
            int shrineVariations[5]; // 0x00009C0C length: 20
            int pondVariations[5]; // 0x00009C20 length: 20
            XYPairShort DAT_PlayerDataUnknownStructureRelatedArray_3[2][24]; // 0x00009C34 length: 192
            int DAT_PlayerDataUnknownStructureRelatedArray_1[6]; // 0x00009CF4 length: 24
            int DAT_PlayerDataUnknownStructureRelatedArray_2[6][3]; // 0x00009D0C length: 72
            XYPairShort DAT_SearchRelatedXYOffsets_1[49]; // 0x00009D54 length: 196
            undefined1 padding_0x9e18[4]; // 0x00009E18 length: 4
            int assemblyPointCfg_0x9e1c[7][4]; // 0x00009E1C length: 112
            int assemblyPointCfg_0x9e8c[4]; // 0x00009E8C length: 16
            int assemblyPointCfg_0x9e9c[7][4]; // 0x00009E9C length: 112
            undefined1 padding_0x9f0c[16]; // 0x00009F0C length: 16
            int assemblyPointCfg_0x9f1c[2][4]; // 0x00009F1C length: 32
            XYPairShort DAT_BuildingPositionRelatedArray_1[25]; // 0x00009F3C length: 100
            undefined1 padding_0x9fa0[4]; // 0x00009FA0 length: 4
            XYPairShort engineerCampgroundCfg_0x9fa4[25]; // 0x00009FA4 length: 100
            undefined1 padding_0xa008[4]; // 0x0000A008 length: 4
            XYPairShort oilSmelterCfg_0xa00c[16]; // 0x0000A00C length: 64
            int outpostBuildingCfg_0xa04c[16][13]; // 0x0000A04C length: 832
            int drawBridgeCfg_0xa38c[4]; // 0x0000A38C length: 16
            int campGroundCfg_0xa39c[52]; // 0x0000A39C length: 208
            int campGroundCfg_0xa46c[52]; // 0x0000A46C length: 208
            int killingPitCfg_0xa53c[26]; // 0x0000A53C length: 104
            int killingPitCfg_0xa5a4[102]; // 0x0000A5A4 length: 408
            int tower2Cfg_0xa73c[16]; // 0x0000A73C length: 64
            int tower3Cfg_0xa77c[24]; // 0x0000A77C length: 96
            int tower4Cfg_0xa7dc[32]; // 0x0000A7DC length: 128
            int DAT_BUILDING_COST[110][5]; // 0x0000A85C length: 2200

        } BuildingDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(BuildingDefinedData) == 45300, BuildingDefinedData);
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
