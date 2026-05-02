/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/AttackInfo.hpp'
*/

#pragma once

#include "OpenSHC/AI/Siege/EngineerBuildingAndCountPair.hpp"
#include "OpenSHC/Map/AttackInfoPitchRelated.hpp"
#include "OpenSHC/Map/AttackInfoSubArrayElement1.hpp"
#include "OpenSHC/Map/AttackInfoSubArrayElement2.hpp"
#include "OpenSHC/Map/AttackInfoSubArrayElement3.hpp"
#include "OpenSHC/Map/AttackInfoSubElement.hpp"
#include "OpenSHC/Map/Units/Attack/TribeSizesPerTribeType.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::AI::Siege::EngineerBuildingAndCountPair;
    using OpenSHC::Map::AttackInfoPitchRelated;
    using OpenSHC::Map::AttackInfoSubArrayElement1;
    using OpenSHC::Map::AttackInfoSubArrayElement2;
    using OpenSHC::Map::AttackInfoSubArrayElement3;
    using OpenSHC::Map::AttackInfoSubElement;
    using OpenSHC::Map::Units::Attack::TribeSizesPerTribeType;

#pragma pack(push, 1)
    // SIZE: 0x0010375C
    typedef struct AttackInfo {

        undefined1 padding_0x0[80144]; // 0x00000000 length: 80144
        int high1; // 0x00013910 length: 4
        int high2; // 0x00013914 length: 4
        int high3; // 0x00013918 length: 4
        AttackInfoSubArrayElement1 high2ValuesArray[1000]; // 0x0001391C length: 16000
        undefined1 padding_0x1779c[16]; // 0x0001779C length: 16
        int arch1; // 0x000177AC length: 4
        int arch2; // 0x000177B0 length: 4
        int arch3; // 0x000177B4 length: 4
        AttackInfoSubArrayElement1 arch2ValuesArray[1000]; // 0x000177B8 length: 16000
        undefined1 padding_0x1b638[16]; // 0x0001B638 length: 16
        int archerPoints; // 0x0001B648 length: 4
        int archerPointsNext; // 0x0001B64C length: 4
        undefined1 padding_0x1b650[6432]; // 0x0001B650 length: 6432
        int targetedBuildingTilesArray[4000]; // 0x0001CF70 length: 16000
        int targetedBuildingTilesArraySize; // 0x00020DF0 length: 4
        int startCon; // 0x00020DF4 length: 4
        int keepCon; // 0x00020DF8 length: 4
        int counter; // 0x00020DFC length: 4
        undefined1 padding_0x20e00[4]; // 0x00020E00 length: 4
        int field86627_0x20e04; // 0x00020E04 length: 4
        int index; // 0x00020E08 length: 4
        undefined1 padding_0x20e0c[340]; // 0x00020E0C length: 340
        int catapults; // 0x00020F60 length: 4
        int engineers; // 0x00020F64 length: 4
        int pikemenSwordsmenAndMore; // 0x00020F68 length: 4
        int laddermen; // 0x00020F6C length: 4
        int spearmenAndMacemen; // 0x00020F70 length: 4
        int field86974_0x20f74; // 0x00020F74 length: 4
        int attacker; // 0x00020F78 length: 4
        undefined1 padding_0x20f7c[4]; // 0x00020F7C length: 4
        int aiTroops; // 0x00020F80 length: 4
        undefined1 padding_0x20f84[4]; // 0x00020F84 length: 4
        int biggestZone; // 0x00020F88 length: 4
        int startZone; // 0x00020F8C length: 4
        int unknownOne_0x20f90; // 0x00020F90 length: 4
        int scaleZone; // 0x00020F94 length: 4
        int field86989_0x20f98; // 0x00020F98 length: 4
        int field86990_0x20f9c; // 0x00020F9C length: 4
        int someCounter1; // 0x00020FA0 length: 4
        undefined1 padding_0x20fa4[4]; // 0x00020FA4 length: 4
        short nof_fpointsArray[50][8]; // 0x00020FA8 length: 800
        undefined1 padding_0x212c8[2416]; // 0x000212C8 length: 2416
        int nof_fpoints; // 0x00021C38 length: 4
        int lowTroopValueRelated; // 0x00021C3C length: 4
        int size; // 0x00021C40 length: 4
        int value10; // 0x00021C44 length: 4
        int field89417_0x21c48; // 0x00021C48 length: 4
        int field89418_0x21c4c; // 0x00021C4C length: 4
        int casDis; // 0x00021C50 length: 4
        undefined1 padding_0x21c54[16036]; // 0x00021C54 length: 16036
        int zoneSize; // 0x00025AF8 length: 4
        int someDistanceLimit; // 0x00025AFC length: 4
        int field105458_0x25b00; // 0x00025B00 length: 4
        int playerTotalTroopValueArray[9]; // 0x00025B04 length: 36
        int field105460_0x25b28; // 0x00025B28 length: 4
        int playerTotalTroopValueOfTroopsNearKeep[9]; // 0x00025B2C length: 36
        undefined1 padding_0x25b50[20480]; // 0x00025B50 length: 20480
        int someIntArray2[50]; // 0x0002AB50 length: 200
        undefined1 padding_0x2ac18[1596]; // 0x0002AC18 length: 1596
        AttackInfoPitchRelated field127539_0x2b254[100]; // 0x0002B254 length: 800
        int field127540_0x2b574; // 0x0002B574 length: 4
        int field127541_0x2b578; // 0x0002B578 length: 4
        short unitIDArray_0x2b57c[1000]; // 0x0002B57C length: 2000
        int unitIDIndex_0x2bd4c; // 0x0002BD4C length: 4
        int tileArray_0x2bd50[200]; // 0x0002BD50 length: 800
        short unitIDArray_0x2c070[200]; // 0x0002C070 length: 400
        int uidArray_0x2c200[200]; // 0x0002C200 length: 800
        int unitIDIndex_0x2c520; // 0x0002C520 length: 4
        int macemenTribeCount; // 0x0002C524 length: 4
        int knightTribeCount; // 0x0002C528 length: 4
        int macemenTribeArray[100]; // 0x0002C52C length: 400
        int knightTribeArray[100]; // 0x0002C6BC length: 400
        int pitchRelatedPlayerID; // 0x0002C84C length: 4
        int playerID_0x2c850; // 0x0002C850 length: 4
        undefined1 padding_0x2c854[4]; // 0x0002C854 length: 4
        int someArea; // 0x0002C858 length: 4
        int field127559_0x2c85c; // 0x0002C85C length: 4
        int lord1; // 0x0002C860 length: 4
        int lord3; // 0x0002C864 length: 4
        int lord2; // 0x0002C868 length: 4
        AttackInfoSubArrayElement1 lordValuesArray[917]; // 0x0002C86C length: 14672
        undefined1 padding_0x301bc[4]; // 0x000301BC length: 4
        int unknownPlayerID_0x301c0; // 0x000301C0 length: 4
        int hackValue1; // 0x000301C4 length: 4
        int hackValue2; // 0x000301C8 length: 4
        int hackValue3; // 0x000301CC length: 4
        AttackInfoSubArrayElement2 hackValuesArray[82]; // 0x000301D0 length: 1312
        undefined1 padding_0x306f0[12]; // 0x000306F0 length: 12
        int inv_count; // 0x000306FC length: 4
        int value3Array01[50]; // 0x00030700 length: 200
        int attackWaveTicker[50]; // 0x000307C8 length: 200
        byte nof_tribes[50]; // 0x00030890 length: 50
        byte unknownByteArray02[50]; // 0x000308C2 length: 50
        byte attackWavePlayerIDArray[50]; // 0x000308F4 length: 50
        byte someSinglePlayerScore[50][10]; // 0x00030926 length: 500
        short field127592_0x30b1a[50]; // 0x00030B1A length: 100
        undefined1 padding_0x30b7e[2]; // 0x00030B7E length: 2
        TribeSizesPerTribeType aiTribeSizesPerTribeType; // 0x00030B80 length: 160
        int supportPoints; // 0x00030C20 length: 4
        int supportPointsNext; // 0x00030C24 length: 4
        AttackInfoSubArrayElement3 supportPointsArray[201]; // 0x00030C28 length: 6432
        int tentPoints; // 0x00032548 length: 4
        int tentPointsNext; // 0x0003254C length: 4
        AttackInfoSubArrayElement3 tentPointsValues[216]; // 0x00032550 length: 6912
        undefined1 padding_0x34050[16]; // 0x00034050 length: 16
        int unknownDistance_0x34060; // 0x00034060 length: 4
        int field127619_0x34064; // 0x00034064 length: 4
        undefined1 padding_0x34068[4]; // 0x00034068 length: 4
        int stoneValue1; // 0x0003406C length: 4
        int scaleValue1; // 0x00034070 length: 4
        int scaleValue2; // 0x00034074 length: 4
        int scaleValue3; // 0x00034078 length: 4
        AttackInfoSubArrayElement1 scaleValuesArray[1001]; // 0x0003407C length: 16016
        int townValue1; // 0x00037F0C length: 4
        int townValue22; // 0x00037F10 length: 4
        int townValue2; // 0x00037F14 length: 4
        AttackInfoSubArrayElement2 townValuesArray[1001]; // 0x00037F18 length: 16016
        int gateValue1; // 0x0003BDA8 length: 4
        int gateValue15; // 0x0003BDAC length: 4
        int gateValue2; // 0x0003BDB0 length: 4
        AttackInfoSubArrayElement1 gateValuesArray[1001]; // 0x0003BDB4 length: 16016
        int moat1; // 0x0003FC44 length: 4
        int moat2; // 0x0003FC48 length: 4
        int moat3; // 0x0003FC4C length: 4
        AttackInfoSubArrayElement1 moatValuesArray[562]; // 0x0003FC50 length: 8992
        int createTribeAmount; // 0x00041F70 length: 4
        EngineerBuildingAndCountPair field127642_0x41f74[250]; // 0x00041F74 length: 2000
        undefined1 padding_0x42744[4]; // 0x00042744 length: 4
        int people1; // 0x00042748 length: 4
        int people2; // 0x0004274C length: 4
        int people3; // 0x00042750 length: 4
        AttackInfoSubArrayElement1 peopleValuesArray[312]; // 0x00042754 length: 4992
        undefined1 padding_0x43ad4[12]; // 0x00043AD4 length: 12
        int wide1; // 0x00043AE0 length: 4
        int wide2; // 0x00043AE4 length: 4
        int wide3; // 0x00043AE8 length: 4
        AttackInfoSubArrayElement1 wideValuesArray[687]; // 0x00043AEC length: 10992
        undefined1 padding_0x465dc[8]; // 0x000465DC length: 8
        int tribeIDArraySize; // 0x000465E4 length: 4
        int unknownTribeCounterRelated; // 0x000465E8 length: 4
        int tribeIDArray[50]; // 0x000465EC length: 200
        int field127678_0x466b4[50]; // 0x000466B4 length: 200
        int tribeRelatedArrayValue0UpTo12[50]; // 0x0004677C length: 200
        undefined1 padding_0x46844[200]; // 0x00046844 length: 200
        int unknownSignpostRelatedArray; // 0x0004690C length: 4
        undefined1 padding_0x46910[196]; // 0x00046910 length: 196
        int field128077_0x469d4; // 0x000469D4 length: 4
        undefined1 padding_0x469d8[4]; // 0x000469D8 length: 4
        int field128082_0x469dc; // 0x000469DC length: 4
        undefined1 padding_0x469e0[4]; // 0x000469E0 length: 4
        int knights; // 0x000469E4 length: 4
        int ranged; // 0x000469E8 length: 4
        undefined1 padding_0x469ec[8]; // 0x000469EC length: 8
        int tilemapOffset; // 0x000469F4 length: 4
        undefined1 padding_0x469f8[3972]; // 0x000469F8 length: 3972
        AttackInfoSubElement playerInfo[8]; // 0x0004797C length: 769504

    } AttackInfo;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(AttackInfo) == 1062748, AttackInfo);
} // namespace Map
} // namespace OpenSHC
