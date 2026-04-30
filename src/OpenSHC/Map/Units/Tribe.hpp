/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Units/Tribe.hpp'
*/

#pragma once

#include "OpenSHC/AI/Tribes/AITribeTypeShort.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnumShort.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::AI::Tribes::AITribeTypeShort;
        using OpenSHC::Map::Units::SomeTribeBehaviorTypeShort;
        using OpenSHC::Map::Units::UnitTypeShort;
        using OpenSHC::Map::Units::Behavior::UnitStanceEnumShort;

#pragma pack(push, 1)
        // SIZE: 0x00000334
        typedef struct Tribe {

            undefined1 padding_0x0[2]; // 0x00000000 length: 2
            short time; // 0x00000002 length: 2
            int owner; // 0x00000004 length: 4
            undefined1 padding_0x8[4]; // 0x00000008 length: 4
            int uid; // 0x0000000C length: 4
            undefined1 padding_0x10[8]; // 0x00000010 length: 8
            short tribeState; // 0x00000018 length: 2
            AITribeTypeShort tribeType; // 0x0000001A length: 2
            short field19_0x1c; // 0x0000001C length: 2
            short field20_0x1e; // 0x0000001E length: 2
            short facingDirection_1; // 0x00000020 length: 2
            short facingDirection_2; // 0x00000022 length: 2
            short facingDirection_3; // 0x00000024 length: 2
            short field24_0x26; // 0x00000026 length: 2
            SomeTribeBehaviorTypeShort tribeBehaviorType; // 0x00000028 length: 2
            undefined1 padding_0x2a[2]; // 0x0000002A length: 2
            short someUpdateUpperLimit; // 0x0000002C length: 2
            short unknownAttackRelatedUpdateCounter; // 0x0000002E length: 2
            short field30_0x30; // 0x00000030 length: 2
            short selectionTargetUnitID; // 0x00000032 length: 2
            short size; // 0x00000034 length: 2
            short size2Unk; // 0x00000036 length: 2
            short unitSelectionBitMasked[200]; // 0x00000038 length: 400
            undefined1 padding_0x1c8[12]; // 0x000001C8 length: 12
            short someUnitArray[10]; // 0x000001D4 length: 20
            short countdown2; // 0x000001E8 length: 2
            undefined1 padding_0x1ea[6]; // 0x000001EA length: 6
            short freeUnitSpeeds; // 0x000001F0 length: 2
            short field56_0x1f2; // 0x000001F2 length: 2
            int uid2; // 0x000001F4 length: 4
            short tribeID; // 0x000001F8 length: 2
            short minimumMovementSpeed; // 0x000001FA length: 2
            short movementSpeed; // 0x000001FC length: 2
            short maximumMovementSpeed; // 0x000001FE length: 2
            short field62_0x200; // 0x00000200 length: 2
            short field63_0x202; // 0x00000202 length: 2
            short field64_0x204; // 0x00000204 length: 2
            short isRallyingUnk; // 0x00000206 length: 2
            short field66_0x208; // 0x00000208 length: 2
            short unitsHealthPercentage; // 0x0000020A length: 2
            short field68_0x20c; // 0x0000020C length: 2
            short targetX; // 0x0000020E length: 2
            short targetY; // 0x00000210 length: 2
            short field71_0x212; // 0x00000212 length: 2
            undefined1 padding_0x214[20]; // 0x00000214 length: 20
            UnitTypeShort unitType; // 0x00000228 length: 2
            short field93_0x22a; // 0x0000022A length: 2
            undefined1 padding_0x22c[12]; // 0x0000022C length: 12
            short rallyPointArray[9][2]; // 0x00000238 length: 36
            undefined1 padding_0x25c[4]; // 0x0000025C length: 4
            short currentRallyPointIndex; // 0x00000260 length: 2
            short rallyPointCount; // 0x00000262 length: 2
            undefined1 padding_0x264[20]; // 0x00000264 length: 20
            short field133_0x278; // 0x00000278 length: 2
            short field134_0x27a; // 0x0000027A length: 2
            short unkIsAnimalTribe; // 0x0000027C length: 2
            short field136_0x27e; // 0x0000027E length: 2
            short field137_0x280; // 0x00000280 length: 2
            short field138_0x282; // 0x00000282 length: 2
            short field139_0x284; // 0x00000284 length: 2
            short unknownCounter01; // 0x00000286 length: 2
            undefined1 padding_0x288[2]; // 0x00000288 length: 2
            short unknownBool02; // 0x0000028A length: 2
            short unknownBool01; // 0x0000028C length: 2
            short countdown; // 0x0000028E length: 2
            short someUnitArrayIndex; // 0x00000290 length: 2
            short someIndex; // 0x00000292 length: 2
            short attackWave; // 0x00000294 length: 2
            short percentageDyingUnk; // 0x00000296 length: 2
            short percentageMovingUnk; // 0x00000298 length: 2
            short percentageAttackingUnk; // 0x0000029A length: 2
            short field152_0x29c; // 0x0000029C length: 2
            short percentageShootingUnk; // 0x0000029E length: 2
            short field154_0x2a0; // 0x000002A0 length: 2
            short percentageSomething; // 0x000002A2 length: 2
            short attackInfo_someCounter1; // 0x000002A4 length: 2
            short archerRelated; // 0x000002A6 length: 2
            short archerRelated2; // 0x000002A8 length: 2
            short supportPointIndex; // 0x000002AA length: 2
            short oldSupportPointIndex; // 0x000002AC length: 2
            short field161_0x2ae; // 0x000002AE length: 2
            short siegeIndexValue1; // 0x000002B0 length: 2
            short siegeIndexValue2; // 0x000002B2 length: 2
            int someTile2; // 0x000002B4 length: 4
            UnitStanceEnumShort unitStance; // 0x000002B8 length: 2
            short orientation; // 0x000002BA length: 2
            short someCounter1; // 0x000002BC length: 2
            short field168_0x2be; // 0x000002BE length: 2
            short someUnitID; // 0x000002C0 length: 2
            undefined1 padding_0x2c2[2]; // 0x000002C2 length: 2
            int someUnitUID; // 0x000002C4 length: 4
            int someTile; // 0x000002C8 length: 4
            short highestID; // 0x000002CC length: 2
            short targetPlayer_outpost; // 0x000002CE length: 2
            short targetBuildingID; // 0x000002D0 length: 2
            undefined1 padding_0x2d2[2]; // 0x000002D2 length: 2
            int targetBuildingUID; // 0x000002D4 length: 4
            int someUnitUIDArray[10]; // 0x000002D8 length: 40
            short tribeSubtype1; // 0x00000300 length: 2
            short counter; // 0x00000302 length: 2
            int randomNumber; // 0x00000304 length: 4
            undefined1 padding_0x308[44]; // 0x00000308 length: 44

        } Tribe;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(Tribe) == 820, Tribe);
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
