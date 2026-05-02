/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/Unit.hpp'
*/

#pragma once

#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnumShort.hpp"
#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"
#include "OpenSHC/Map/Units/States/UnitStateUnion.hpp"
#include "OpenSHC/Map/Units/UnitInstructionTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitLogicStateShort.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitInstructionTypeShort;
        using OpenSHC::Map::Units::UnitLogicStateShort;
        using OpenSHC::Map::Units::UnitTypeShort;
        using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnumShort;
        using OpenSHC::Map::Units::States::UnitStateShort;
        using OpenSHC::Map::Units::States::UnitStateUnion;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
        // SIZE: 0x00000490
        typedef struct Unit {

            undefined1 padding_0x0[4]; // 0x00000000 length: 4
            int gfxNumber; // 0x00000004 length: 4
            int animationSheetFrameOffset; // 0x00000008 length: 4
            short spriteID; // 0x0000000C length: 2
            undefined1 padding_0xe[2]; // 0x0000000E length: 2
            int calculatedOwnerPlayerIndex; // 0x00000010 length: 4
            short drawX; // 0x00000014 length: 2
            short drawY; // 0x00000016 length: 2
            short drawWidth; // 0x00000018 length: 2
            short drawHeight1; // 0x0000001A length: 2
            undefined1 padding_0x1c[2]; // 0x0000001C length: 2
            short spriteWidthUnk; // 0x0000001E length: 2
            short spriteHeightUnk; // 0x00000020 length: 2
            short drawXOffset; // 0x00000022 length: 2
            short someDrawYOffset; // 0x00000024 length: 2
            short orientationRelatedPositionX; // 0x00000026 length: 2
            short orientationRelatedPositionY; // 0x00000028 length: 2
            short field22_0x2a; // 0x0000002A length: 2
            int unknownV; // 0x0000002C length: 4
            int field_0x30_animRelated; // 0x00000030 length: 4
            short isSelected; // 0x00000034 length: 2
            undefined1 padding_0x36[2]; // 0x00000036 length: 2
            short healthbar; // 0x00000038 length: 2
            undefined1 padding_0x3a[2]; // 0x0000003A length: 2
            int animationLeapTicksTotal; // 0x0000003C length: 4
            int animationTicker; // 0x00000040 length: 4
            int animationSpeed; // 0x00000044 length: 4
            int animationFrame; // 0x00000048 length: 4
            undefined1 padding_0x4c[4]; // 0x0000004C length: 4
            BOOLEnum animationCycleNumberHasJustIncremented; // 0x00000050 length: 4
            short facingDirectionMapOrientationCorrected; // 0x00000054 length: 2
            short field41_0x56; // 0x00000056 length: 2
            short field42_0x58; // 0x00000058 length: 2
            short field43_0x5a; // 0x0000005A length: 2
            int field44_0x5c; // 0x0000005C length: 4
            int field45_0x60; // 0x00000060 length: 4
            int field46_0x64; // 0x00000064 length: 4
            int vanish; // 0x00000068 length: 4
            short field48_0x6c; // 0x0000006C length: 2
            short field49_0x6e; // 0x0000006E length: 2
            byte negativeHeight; // 0x00000070 length: 1
            byte antelopeBasedRngValue; // 0x00000071 length: 1
            undefined1 padding_0x72[2]; // 0x00000072 length: 2
            int imageIDUnk; // 0x00000074 length: 4
            int imageID2; // 0x00000078 length: 4
            short unitSpeedMatchingRelatedUnk; // 0x0000007C length: 2
            short gmIDUnk; // 0x0000007E length: 2
            short displayColorPlayerID; // 0x00000080 length: 2
            undefined1 heightDiv10; // 0x00000082 length: 1
            undefined1 padding_0x83[1]; // 0x00000083 length: 1
            short field61_0x84; // 0x00000084 length: 2
            short field62_0x86; // 0x00000086 length: 2
            short field63_0x88; // 0x00000088 length: 2
            short drawYOffset; // 0x0000008A length: 2
            UnitLogicStateShort logicalState; // 0x0000008C length: 2
            UnitTypeShort unitType; // 0x0000008E length: 2
            short field67_0x90; // 0x00000090 length: 2
            undefined1 padding_0x92[2]; // 0x00000092 length: 2
            short moveRelatedFlag; // 0x00000094 length: 2
            short owner; // 0x00000096 length: 2
            int uid; // 0x00000098 length: 4
            int time; // 0x0000009C length: 4
            int targetUID; // 0x000000A0 length: 4
            undefined1 padding_0xa4[12]; // 0x000000A4 length: 12
            short goToRallyPoint; // 0x000000B0 length: 2
            short ifSelectedThenPlayerID; // 0x000000B2 length: 2
            short selectionRelatedFlag; // 0x000000B4 length: 2
            short microXPosition; // 0x000000B6 length: 2
            short microYPosition; // 0x000000B8 length: 2
            short terrainOrClimbHeight; // 0x000000BA length: 2
            short buildingHeight; // 0x000000BC length: 2
            short shootTargetMicroX; // 0x000000BE length: 2
            short shootTargetMicroY; // 0x000000C0 length: 2
            short shootTargetZ; // 0x000000C2 length: 2
            short x; // 0x000000C4 length: 2
            short y; // 0x000000C6 length: 2
            short destinationXPosition; // 0x000000C8 length: 2
            short destinationYPosition; // 0x000000CA length: 2
            short ladderExitXPosition; // 0x000000CC length: 2
            short ladderExitYPosition; // 0x000000CE length: 2
            short field103_0xd0; // 0x000000D0 length: 2
            short field104_0xd2; // 0x000000D2 length: 2
            int tile; // 0x000000D4 length: 4
            int destinationTilePosition; // 0x000000D8 length: 4
            int previousTilePosition; // 0x000000DC length: 4
            short mimicCurrentXPosition; // 0x000000E0 length: 2
            short mimicCurrentYPosition; // 0x000000E2 length: 2
            int nextTileUnk; // 0x000000E4 length: 4
            int field111_0xe8; // 0x000000E8 length: 4
            short destinationX_2Unk; // 0x000000EC length: 2
            short destinationY_2Unk; // 0x000000EE length: 2
            short _someX_2; // 0x000000F0 length: 2
            short _someY_2; // 0x000000F2 length: 2
            short moveDelay; // 0x000000F4 length: 2
            short tunnelerFinishedDigging; // 0x000000F6 length: 2
            short movementRelated; // 0x000000F8 length: 2
            short currentIndexInPathPlan; // 0x000000FA length: 2
            short totalSizeOfPathPlan; // 0x000000FC length: 2
            byte pathPlanStart[400]; // 0x000000FE length: 400
            short moveInstructionSpeedDelayTracker; // 0x0000028E length: 2
            short leftover; // 0x00000290 length: 2
            short wallDataID; // 0x00000292 length: 2
            short climbDataID; // 0x00000294 length: 2
            undefined1 padding_0x296[2]; // 0x00000296 length: 2
            int climbDataRelated; // 0x00000298 length: 4
            short climbDirection; // 0x0000029C length: 2
            short usingTeleport; // 0x0000029E length: 2
            short dying; // 0x000002A0 length: 2
            ushort nextUnitOnTheSameTile; // 0x000002A2 length: 2
            short isSelectable_OR_matchTime; // 0x000002A4 length: 2
            short closestEnemyMicroDistance; // 0x000002A6 length: 2
            short field135_0x2a8; // 0x000002A8 length: 2
            short targetShootRelated; // 0x000002AA length: 2
            short field137_0x2ac; // 0x000002AC length: 2
            short graphicSize; // 0x000002AE length: 2
            int animationCycleNumber; // 0x000002B0 length: 4
            short facingDirection; // 0x000002B4 length: 2
            undefined1 padding_0x2b6[4]; // 0x000002B6 length: 4
            short unitOrderWhenOnSameTile; // 0x000002BA length: 2
            short movementRunUpTime; // 0x000002BC length: 2
            short stateBasedSpeed; // 0x000002BE length: 2
            UnitStateUnion state; // 0x000002C0 length: 2
            UnitStateShort cachedState; // 0x000002C2 length: 2
            short field150_0x2c4; // 0x000002C4 length: 2
            UnitStateUnion state_3; // 0x000002C6 length: 2
            short updateTickTracker; // 0x000002C8 length: 2
            UnitTypeShort unitTypeToChangeInto; // 0x000002CA length: 2
            short state_2; // 0x000002CC length: 2
            UnitTypeShort unitType_3; // 0x000002CE length: 2
            short someUnitStat2_meleeDamageUnk; // 0x000002D0 length: 2
            short unknownMovementRelated_0x2d2; // 0x000002D2 length: 2
            short healthPercentage; // 0x000002D4 length: 2
            short selectionTargetUnitID; // 0x000002D6 length: 2
            short tribeID; // 0x000002D8 length: 2
            short idInTribe; // 0x000002DA length: 2
            short plannedDestinationX; // 0x000002DC length: 2
            short plannedDestinationY; // 0x000002DE length: 2
            short topSpeedDelayIndex; // 0x000002E0 length: 2
            short movementDistance; // 0x000002E2 length: 2
            int tribeUID; // 0x000002E4 length: 4
            int workTimer; // 0x000002E8 length: 4
            int workRelatedA; // 0x000002EC length: 4
            int workRelatedB; // 0x000002F0 length: 4
            int workRelatedC; // 0x000002F4 length: 4
            int av; // 0x000002F8 length: 4
            short working; // 0x000002FC length: 2
            short field173_0x2fe; // 0x000002FE length: 2
            short field174_0x300; // 0x00000300 length: 2
            short unknownDigMoatOrWallAttackFlag1015; // 0x00000302 length: 2
            short productivityMod100; // 0x00000304 length: 2
            short productivityDiv100; // 0x00000306 length: 2
            short field178_0x308; // 0x00000308 length: 2
            short idle; // 0x0000030A length: 2
            short banked; // 0x0000030C length: 2
            short target; // 0x0000030E length: 2
            short targetX; // 0x00000310 length: 2
            short targetY; // 0x00000312 length: 2
            short manningEngineerRef[4]; // 0x00000314 length: 8
            int manningEngineerUIDRef; // 0x0000031C length: 4
            undefined1 padding_0x320[12]; // 0x00000320 length: 12
            byte unknownTestAgainst0_1; // 0x0000032C length: 1
            char field199_0x32d; // 0x0000032D length: 1
            byte disappearFadeAlphaCountdown; // 0x0000032E length: 1
            byte engineerManningSiegeStateRef_checkType; // 0x0000032F length: 1
            int someMatchTimeVariable; // 0x00000330 length: 4
            undefined1 padding_0x334[2]; // 0x00000334 length: 2
            short targetID_OR_targetBuildingID; // 0x00000336 length: 2
            short workplaceBuildingID_1; // 0x00000338 length: 2
            short targetX_2; // 0x0000033A length: 2
            short targetY_2; // 0x0000033C length: 2
            short attackedUnitID; // 0x0000033E length: 2
            int field210_0x340; // 0x00000340 length: 4
            short shootTargetedUnit; // 0x00000344 length: 2
            short movementType_OR_targetUnitID; // 0x00000346 length: 2
            short workplaceBuildingTilePosition; // 0x00000348 length: 2
            short calculatedMovementSpeed; // 0x0000034A length: 2
            short movementSpeed; // 0x0000034C length: 2
            undefined1 padding_0x34e[2]; // 0x0000034E length: 2
            int field218_0x350; // 0x00000350 length: 4
            int field219_0x354; // 0x00000354 length: 4
            short unknownTestAgainst0_2; // 0x00000358 length: 2
            short distanceToEnemyUnitLadders; // 0x0000035A length: 2
            short field222_0x35c; // 0x0000035C length: 2
            short climbingDirection; // 0x0000035E length: 2
            short unitCanClimb; // 0x00000360 length: 2
            short stoneAmmunition; // 0x00000362 length: 2
            int climbingState; // 0x00000364 length: 4
            int workplaceBuildingUID; // 0x00000368 length: 4
            short traderHorsesTrader; // 0x0000036C length: 2
            short someUnitStat4; // 0x0000036E length: 2
            short cannotClimb; // 0x00000370 length: 2
            short isDisappearingUnk; // 0x00000372 length: 2
            DestinationNeededEnumShort destinationNeeded; // 0x00000374 length: 2
            short unknownStateCopyClimbRelated; // 0x00000376 length: 2
            short field234_0x378; // 0x00000378 length: 2
            short field235_0x37a; // 0x0000037A length: 2
            short field236_0x37c; // 0x0000037C length: 2
            short field237_0x37e; // 0x0000037E length: 2
            short substate; // 0x00000380 length: 2
            undefined1 padding_0x382[2]; // 0x00000382 length: 2
            uint fixedRng; // 0x00000384 length: 4
            short resourceToDeposit; // 0x00000388 length: 2
            short jugglerCount; // 0x0000038A length: 2
            short tunnelerFrame; // 0x0000038C length: 2
            undefined1 padding_0x38e[4]; // 0x0000038E length: 4
            short seated; // 0x00000392 length: 2
            short resourcesGatheredCount; // 0x00000394 length: 2
            short workerIndex; // 0x00000396 length: 2
            short buildingID; // 0x00000398 length: 2
            short field253_0x39a; // 0x0000039A length: 2
            UnitInstructionTypeShort targetingType; // 0x0000039C length: 2
            short targetedUnitID__OR__engineerMannedSiegeEngineRef; // 0x0000039E length: 2
            int targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID; // 0x000003A0
                                                                                                      // length: 4
            short unkAttackRelated; // 0x000003A4 length: 2
            undefined1 padding_0x3a6[2]; // 0x000003A6 length: 2
            uint targetedBuildingTile; // 0x000003A8 length: 4
            short lookForEnemy; // 0x000003AC length: 2
            short attackedBy; // 0x000003AE length: 2
            short field263_0x3b0; // 0x000003B0 length: 2
            short huntedBy; // 0x000003B2 length: 2
            short digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300; // 0x000003B4 length: 2
            short digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine; // 0x000003B6 length: 2
            int digTileTarget; // 0x000003B8 length: 4
            int field268_0x3bc; // 0x000003BC length: 4
            short field269_0x3c0; // 0x000003C0 length: 2
            char field270_0x3c2; // 0x000003C2 length: 1
            undefined1 padding_0x3c3[1]; // 0x000003C3 length: 1
            byte field272_0x3c4; // 0x000003C4 length: 1
            byte field273_0x3c5; // 0x000003C5 length: 1
            short field274_0x3c6; // 0x000003C6 length: 2
            int health; // 0x000003C8 length: 4
            int maxHealth; // 0x000003CC length: 4
            byte occupancyOrFlag; // 0x000003D0 length: 1
            byte field278_0x3d1; // 0x000003D1 length: 1
            short field279_0x3d2; // 0x000003D2 length: 2
            short unknownBool01; // 0x000003D4 length: 2
            short horseOriginStablesBuildingIndexUnk; // 0x000003D6 length: 2
            short shootBeforeStop; // 0x000003D8 length: 2
            undefined1 padding_0x3da[2]; // 0x000003DA length: 2
            short field285_0x3dc; // 0x000003DC length: 2
            short field286_0x3de; // 0x000003DE length: 2
            undefined1 horseOriginStableIDUnk; // 0x000003E0 length: 1
            undefined1 padding_0x3e1[3]; // 0x000003E1 length: 3
            int blessedAmount; // 0x000003E4 length: 4
            short attackAtTileX; // 0x000003E8 length: 2
            short attackAtTileY; // 0x000003EA length: 2
            byte firstNameIndex; // 0x000003EC length: 1
            byte rng1_to_70; // 0x000003ED length: 1
            char nextAttackHurtsWall; // 0x000003EE length: 1
            undefined1 poleturner_spearOrPike; // 0x000003EF length: 1
            short killedFlagUnk; // 0x000003F0 length: 2
            short field299_0x3f2; // 0x000003F2 length: 2
            short field300_0x3f4; // 0x000003F4 length: 2
            undefined1 padding_0x3f6[2]; // 0x000003F6 length: 2
            byte field303_0x3f8; // 0x000003F8 length: 1
            undefined1 unkLadderClimbRelated; // 0x000003F9 length: 1
            byte fadeCounter; // 0x000003FA length: 1
            byte fadeType; // 0x000003FB length: 1
            short SA; // 0x000003FC length: 2
            byte unknownSiegeTentRelated02; // 0x000003FE length: 1
            byte field309_0x3ff; // 0x000003FF length: 1
            short lastEncounteredEnemyPlayerID; // 0x00000400 length: 2
            byte unknownCountdown_0x402; // 0x00000402 length: 1
            byte wasOnStoneGate; // 0x00000403 length: 1
            int currentTilePosition_2Unk; // 0x00000404 length: 4
            short counter; // 0x00000408 length: 2
            short field315_0x40a; // 0x0000040A length: 2
            bool isMatchingSpeed; // 0x0000040C length: 1
            undefined1 padding_0x40d[3]; // 0x0000040D length: 3
            byte field320_0x410; // 0x00000410 length: 1
            undefined1 padding_0x411[1]; // 0x00000411 length: 1
            byte ownerOfAssassinScaledObject; // 0x00000412 length: 1
            byte field323_0x413; // 0x00000413 length: 1
            short assassinHeightDifference; // 0x00000414 length: 2
            short assassinClimbingUpUnk_OR_previousFacingDirection; // 0x00000416 length: 2
            short field326_0x418; // 0x00000418 length: 2
            undefined2 field327_0x41a; // 0x0000041A length: 2
            int field328_0x41c; // 0x0000041C length: 4
            int field329_0x420; // 0x00000420 length: 4
            short horseArcherShootingVariation; // 0x00000424 length: 2
            short horseArcherShootCheckInterval; // 0x00000426 length: 2
            short field332_0x428; // 0x00000428 length: 2
            short aiUnitBehaviourType; // 0x0000042A length: 2
            short rallyRelatedFlag; // 0x0000042C length: 2
            short engineerRelatedUnk; // 0x0000042E length: 2
            short field336_0x430; // 0x00000430 length: 2
            short siegeTargetPlayerID; // 0x00000432 length: 2
            short unknownLordTypeBasedMissionSpecificValue_01; // 0x00000434 length: 2
            short lastEncounteredEnemyUnitIDUnk; // 0x00000436 length: 2
            int assassinsMicroDistanceToEnemyUnk; // 0x00000438 length: 4
            int enemyNoticeFrequencyUnk; // 0x0000043C length: 4
            ushort field342_0x440; // 0x00000440 length: 2
            short field343_0x442; // 0x00000442 length: 2
            short idleCounterUnk; // 0x00000444 length: 2
            short moveableUnk; // 0x00000446 length: 2
            short friendlyFireCounterUnk; // 0x00000448 length: 2
            short maxHealthRatingLord; // 0x0000044A length: 2
            short unknownCagedogRelatedValue3_01; // 0x0000044C length: 2
            undefined1 padding_0x44e[66]; // 0x0000044E length: 66

        } Unit;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(Unit) == 1168, Unit);
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
