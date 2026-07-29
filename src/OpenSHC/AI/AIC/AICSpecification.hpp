/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AIC/AICSpecification.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIC/AITargetChoiceInt.hpp"

namespace OpenSHC {
namespace AI {
    namespace AIC {

        using OpenSHC::AI::AIC::AITargetChoiceInt;

#pragma pack(push, 1)
        // SIZE: 0x000002A4
        typedef struct AICSpecification {

            int flagType; // 0x00000000 length: 4
            int unknown001; // 0x00000004 length: 4
            int unknown002; // 0x00000008 length: 4
            int unknown003; // 0x0000000C length: 4
            int unknown004; // 0x00000010 length: 4
            int unknown005; // 0x00000014 length: 4
            int criticalPopularity; // 0x00000018 length: 4
            int lowestPopularity; // 0x0000001C length: 4
            int highestPopularity; // 0x00000020 length: 4
            int taxesMin; // 0x00000024 length: 4
            int taxesMax; // 0x00000028 length: 4
            int unknown011; // 0x0000002C length: 4
            int farm1; // 0x00000030 length: 4
            int farm2; // 0x00000034 length: 4
            int farm3; // 0x00000038 length: 4
            int farm4; // 0x0000003C length: 4
            int farm5; // 0x00000040 length: 4
            int farm6; // 0x00000044 length: 4
            int farm7; // 0x00000048 length: 4
            int farm8; // 0x0000004C length: 4
            int populationPerFarm; // 0x00000050 length: 4
            int populationPerWoodcutter; // 0x00000054 length: 4
            int populationPerQuarry; // 0x00000058 length: 4
            int populationPerIronmine; // 0x0000005C length: 4
            int populationPerPitchrig; // 0x00000060 length: 4
            int maxQuarries; // 0x00000064 length: 4
            int maxIronmines; // 0x00000068 length: 4
            int maxWoodcutters; // 0x0000006C length: 4
            int maxPitchrigs; // 0x00000070 length: 4
            int maxFarms; // 0x00000074 length: 4
            int buildInterval; // 0x00000078 length: 4
            int resourceRebuildDelay; // 0x0000007C length: 4
            int maxFood; // 0x00000080 length: 4
            int minimumApples; // 0x00000084 length: 4
            int minimumCheese; // 0x00000088 length: 4
            int minimumBread; // 0x0000008C length: 4
            int minimumWheat; // 0x00000090 length: 4
            int minimumHop; // 0x00000094 length: 4
            int tradeAmountFood; // 0x00000098 length: 4
            int tradeAmountEquipment; // 0x0000009C length: 4
            int aiRequestDelay; // 0x000000A0 length: 4
            int minimumGoodsRequiredAfterTrade; // 0x000000A4 length: 4
            int doubleRationsFoodThreshold; // 0x000000A8 length: 4
            int maxWood; // 0x000000AC length: 4
            int maxStone; // 0x000000B0 length: 4
            int maxResourceOther; // 0x000000B4 length: 4
            int maxEquipment; // 0x000000B8 length: 4
            int maxBeer; // 0x000000BC length: 4
            int maxResourceVariance; // 0x000000C0 length: 4
            int recruitGoldThreshold; // 0x000000C4 length: 4
            int blacksmithSetting; // 0x000000C8 length: 4
            int fletcherSetting; // 0x000000CC length: 4
            int poleturnerSetting; // 0x000000D0 length: 4
            int sellResource01; // 0x000000D4 length: 4
            int sellResource02; // 0x000000D8 length: 4
            int sellResource03; // 0x000000DC length: 4
            int sellResource04; // 0x000000E0 length: 4
            int sellResource05; // 0x000000E4 length: 4
            int sellResource06; // 0x000000E8 length: 4
            int sellResource07; // 0x000000EC length: 4
            int sellResource08; // 0x000000F0 length: 4
            int sellResource09; // 0x000000F4 length: 4
            int sellResource10; // 0x000000F8 length: 4
            int sellResource11; // 0x000000FC length: 4
            int sellResource12; // 0x00000100 length: 4
            int sellResource13; // 0x00000104 length: 4
            int sellResource14; // 0x00000108 length: 4
            int sellResource15; // 0x0000010C length: 4
            int defWallPatrolRallyTime; // 0x00000110 length: 4
            int defWallPatrolGroups; // 0x00000114 length: 4
            int defSiegeEngineGoldThreshold; // 0x00000118 length: 4
            int defSiegeEngineBuildDelay; // 0x0000011C length: 4
            int unknown072; // 0x00000120 length: 4
            int unknown073; // 0x00000124 length: 4
            int recruitProbDefDefault; // 0x00000128 length: 4
            int recruitProbDefWeak; // 0x0000012C length: 4
            int recruitProbDefStrong; // 0x00000130 length: 4
            int recruitProbRaidDefault; // 0x00000134 length: 4
            int recruitProbRaidWeak; // 0x00000138 length: 4
            int recruitProbRaidStrong; // 0x0000013C length: 4
            int recruitProbAttackDefault; // 0x00000140 length: 4
            int recruitProbAttackWeak; // 0x00000144 length: 4
            int recruitProbAttackStrong; // 0x00000148 length: 4
            int SortieUnitRangedMin; // 0x0000014C length: 4
            int SortieUnitRanged; // 0x00000150 length: 4
            int SortieUnitMeleeMin; // 0x00000154 length: 4
            int SortieUnitMelee; // 0x00000158 length: 4
            int DefDiggingUnitMax; // 0x0000015C length: 4
            int DefDiggingUnit; // 0x00000160 length: 4
            int RecruitInterval; // 0x00000164 length: 4
            int RecruitIntervalWeak; // 0x00000168 length: 4
            int RecruitIntervalStrong; // 0x0000016C length: 4
            int DefTotal; // 0x00000170 length: 4
            int OuterPatrolGroupsCount; // 0x00000174 length: 4
            int OuterPatrolGroupsMove; // 0x00000178 length: 4
            int OuterPatrolRallyDelay; // 0x0000017C length: 4
            int DefWalls; // 0x00000180 length: 4
            int DefUnit1; // 0x00000184 length: 4
            int DefUnit2; // 0x00000188 length: 4
            int DefUnit3; // 0x0000018C length: 4
            int DefUnit4; // 0x00000190 length: 4
            int DefUnit5; // 0x00000194 length: 4
            int DefUnit6; // 0x00000198 length: 4
            int DefUnit7; // 0x0000019C length: 4
            int DefUnit8; // 0x000001A0 length: 4
            int RaidUnitsBase; // 0x000001A4 length: 4
            int RaidUnitsRandom; // 0x000001A8 length: 4
            int RaidUnit1; // 0x000001AC length: 4
            int RaidUnit2; // 0x000001B0 length: 4
            int RaidUnit3; // 0x000001B4 length: 4
            int RaidUnit4; // 0x000001B8 length: 4
            int RaidUnit5; // 0x000001BC length: 4
            int RaidUnit6; // 0x000001C0 length: 4
            int RaidUnit7; // 0x000001C4 length: 4
            int RaidUnit8; // 0x000001C8 length: 4
            int HarassingSiegeEngine1; // 0x000001CC length: 4
            int HarassingSiegeEngine2; // 0x000001D0 length: 4
            int HarassingSiegeEngine3; // 0x000001D4 length: 4
            int HarassingSiegeEngine4; // 0x000001D8 length: 4
            int HarassingSiegeEngine5; // 0x000001DC length: 4
            int HarassingSiegeEngine6; // 0x000001E0 length: 4
            int HarassingSiegeEngine7; // 0x000001E4 length: 4
            int HarassingSiegeEngine8; // 0x000001E8 length: 4
            int HarassingSiegeEnginesMax; // 0x000001EC length: 4
            int RaidRetargetDelay; // 0x000001F0 length: 4
            int AttForceBase; // 0x000001F4 length: 4
            int AttForceRandom; // 0x000001F8 length: 4
            int AttForceSupportAllyThreshold; // 0x000001FC length: 4
            int AttForceRallyPercentage; // 0x00000200 length: 4
            int AttMovingTribesThreshold; // 0x00000204 length: 4
            int AttAssaultDelay; // 0x00000208 length: 4
            int AttUnitPatrolRecommandDelay; // 0x0000020C length: 4
            int AttCoordinationPreference; // 0x00000210 length: 4
            int SiegeEngine1; // 0x00000214 length: 4
            int SiegeEngine2; // 0x00000218 length: 4
            int SiegeEngine3; // 0x0000021C length: 4
            int SiegeEngine4; // 0x00000220 length: 4
            int SiegeEngine5; // 0x00000224 length: 4
            int SiegeEngine6; // 0x00000228 length: 4
            int SiegeEngine7; // 0x0000022C length: 4
            int SiegeEngine8; // 0x00000230 length: 4
            int CowThrowInterval; // 0x00000234 length: 4
            int Unknown142; // 0x00000238 length: 4
            int AttMaxEngineers; // 0x0000023C length: 4
            int AttDiggingUnit; // 0x00000240 length: 4
            int AttDiggingUnitMax; // 0x00000244 length: 4
            int AttUnit2; // 0x00000248 length: 4
            int AttUnit2Max; // 0x0000024C length: 4
            int AttMaxAssassins; // 0x00000250 length: 4
            int AttMaxLaddermen; // 0x00000254 length: 4
            int AttMaxTunnelers; // 0x00000258 length: 4
            int AttUnitPatrol; // 0x0000025C length: 4
            int AttUnitPatrolMax; // 0x00000260 length: 4
            int AttUnitPatrolGroupsCount; // 0x00000264 length: 4
            int AttUnitBackup; // 0x00000268 length: 4
            int AttUnitBackupMax; // 0x0000026C length: 4
            int AttUnitBackupGroupsCount; // 0x00000270 length: 4
            int AttUnitEngage; // 0x00000274 length: 4
            int AttUnitEngageMax; // 0x00000278 length: 4
            int AttUnitSiegeDef; // 0x0000027C length: 4
            int AttUnitSiegeDefMax; // 0x00000280 length: 4
            int AttUnitSiegeDefGroupsCount; // 0x00000284 length: 4
            int AttUnitMain1; // 0x00000288 length: 4
            int AttUnitMain2; // 0x0000028C length: 4
            int AttUnitMain3; // 0x00000290 length: 4
            int AttUnitMain4; // 0x00000294 length: 4
            int AttMaxDefault; // 0x00000298 length: 4
            int AttMainGroupsCount; // 0x0000029C length: 4
            AITargetChoiceInt TargetChoice; // 0x000002A0 length: 4

        } AICSpecification;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(AICSpecification) == 676, AICSpecification);
    } // namespace AIC
} // namespace AI
} // namespace OpenSHC
