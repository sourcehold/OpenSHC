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

            dword flagType; // 0x00000000 length: 4
            dword unknown001; // 0x00000004 length: 4
            dword unknown002; // 0x00000008 length: 4
            dword unknown003; // 0x0000000C length: 4
            dword unknown004; // 0x00000010 length: 4
            dword unknown005; // 0x00000014 length: 4
            dword criticalPopularity; // 0x00000018 length: 4
            dword lowestPopularity; // 0x0000001C length: 4
            dword highestPopularity; // 0x00000020 length: 4
            dword taxesMin; // 0x00000024 length: 4
            dword taxesMax; // 0x00000028 length: 4
            dword unknown011; // 0x0000002C length: 4
            dword farm1; // 0x00000030 length: 4
            dword farm2; // 0x00000034 length: 4
            dword farm3; // 0x00000038 length: 4
            dword farm4; // 0x0000003C length: 4
            dword farm5; // 0x00000040 length: 4
            dword farm6; // 0x00000044 length: 4
            dword farm7; // 0x00000048 length: 4
            dword farm8; // 0x0000004C length: 4
            dword populationPerFarm; // 0x00000050 length: 4
            dword populationPerWoodcutter; // 0x00000054 length: 4
            dword populationPerQuarry; // 0x00000058 length: 4
            dword populationPerIronmine; // 0x0000005C length: 4
            dword populationPerPitchrig; // 0x00000060 length: 4
            dword maxQuarries; // 0x00000064 length: 4
            dword maxIronmines; // 0x00000068 length: 4
            dword maxWoodcutters; // 0x0000006C length: 4
            dword maxPitchrigs; // 0x00000070 length: 4
            dword maxFarms; // 0x00000074 length: 4
            dword buildInterval; // 0x00000078 length: 4
            dword resourceRebuildDelay; // 0x0000007C length: 4
            dword maxFood; // 0x00000080 length: 4
            dword minimumApples; // 0x00000084 length: 4
            dword minimumCheese; // 0x00000088 length: 4
            dword minimumBread; // 0x0000008C length: 4
            dword minimumWheat; // 0x00000090 length: 4
            dword minimumHop; // 0x00000094 length: 4
            dword tradeAmountFood; // 0x00000098 length: 4
            dword tradeAmountEquipment; // 0x0000009C length: 4
            dword aiRequestDelay; // 0x000000A0 length: 4
            dword minimumGoodsRequiredAfterTrade; // 0x000000A4 length: 4
            dword doubleRationsFoodThreshold; // 0x000000A8 length: 4
            dword maxWood; // 0x000000AC length: 4
            dword maxStone; // 0x000000B0 length: 4
            dword maxResourceOther; // 0x000000B4 length: 4
            dword maxEquipment; // 0x000000B8 length: 4
            dword maxBeer; // 0x000000BC length: 4
            dword maxResourceVariance; // 0x000000C0 length: 4
            dword recruitGoldThreshold; // 0x000000C4 length: 4
            int blacksmithSetting; // 0x000000C8 length: 4
            int fletcherSetting; // 0x000000CC length: 4
            int poleturnerSetting; // 0x000000D0 length: 4
            dword sellResource01; // 0x000000D4 length: 4
            dword sellResource02; // 0x000000D8 length: 4
            dword sellResource03; // 0x000000DC length: 4
            dword sellResource04; // 0x000000E0 length: 4
            dword sellResource05; // 0x000000E4 length: 4
            dword sellResource06; // 0x000000E8 length: 4
            dword sellResource07; // 0x000000EC length: 4
            dword sellResource08; // 0x000000F0 length: 4
            dword sellResource09; // 0x000000F4 length: 4
            dword sellResource10; // 0x000000F8 length: 4
            dword sellResource11; // 0x000000FC length: 4
            dword sellResource12; // 0x00000100 length: 4
            dword sellResource13; // 0x00000104 length: 4
            dword sellResource14; // 0x00000108 length: 4
            dword sellResource15; // 0x0000010C length: 4
            dword defWallPatrolRallyTime; // 0x00000110 length: 4
            dword defWallPatrolGroups; // 0x00000114 length: 4
            dword defSiegeEngineGoldThreshold; // 0x00000118 length: 4
            dword defSiegeEngineBuildDelay; // 0x0000011C length: 4
            dword unknown072; // 0x00000120 length: 4
            dword unknown073; // 0x00000124 length: 4
            dword recruitProbDefDefault; // 0x00000128 length: 4
            dword recruitProbDefWeak; // 0x0000012C length: 4
            dword recruitProbDefStrong; // 0x00000130 length: 4
            dword recruitProbRaidDefault; // 0x00000134 length: 4
            dword recruitProbRaidWeak; // 0x00000138 length: 4
            dword recruitProbRaidStrong; // 0x0000013C length: 4
            dword recruitProbAttackDefault; // 0x00000140 length: 4
            dword recruitProbAttackWeak; // 0x00000144 length: 4
            dword recruitProbAttackStrong; // 0x00000148 length: 4
            dword SortieUnitRangedMin; // 0x0000014C length: 4
            dword SortieUnitRanged; // 0x00000150 length: 4
            dword SortieUnitMeleeMin; // 0x00000154 length: 4
            dword SortieUnitMelee; // 0x00000158 length: 4
            dword DefDiggingUnitMax; // 0x0000015C length: 4
            dword DefDiggingUnit; // 0x00000160 length: 4
            dword RecruitInterval; // 0x00000164 length: 4
            dword RecruitIntervalWeak; // 0x00000168 length: 4
            dword RecruitIntervalStrong; // 0x0000016C length: 4
            dword DefTotal; // 0x00000170 length: 4
            dword OuterPatrolGroupsCount; // 0x00000174 length: 4
            dword OuterPatrolGroupsMove; // 0x00000178 length: 4
            dword OuterPatrolRallyDelay; // 0x0000017C length: 4
            dword DefWalls; // 0x00000180 length: 4
            dword DefUnit1; // 0x00000184 length: 4
            dword DefUnit2; // 0x00000188 length: 4
            dword DefUnit3; // 0x0000018C length: 4
            dword DefUnit4; // 0x00000190 length: 4
            dword DefUnit5; // 0x00000194 length: 4
            dword DefUnit6; // 0x00000198 length: 4
            dword DefUnit7; // 0x0000019C length: 4
            dword DefUnit8; // 0x000001A0 length: 4
            dword RaidUnitsBase; // 0x000001A4 length: 4
            dword RaidUnitsRandom; // 0x000001A8 length: 4
            dword RaidUnit1; // 0x000001AC length: 4
            dword RaidUnit2; // 0x000001B0 length: 4
            dword RaidUnit3; // 0x000001B4 length: 4
            dword RaidUnit4; // 0x000001B8 length: 4
            dword RaidUnit5; // 0x000001BC length: 4
            dword RaidUnit6; // 0x000001C0 length: 4
            dword RaidUnit7; // 0x000001C4 length: 4
            dword RaidUnit8; // 0x000001C8 length: 4
            dword HarassingSiegeEngine1; // 0x000001CC length: 4
            dword HarassingSiegeEngine2; // 0x000001D0 length: 4
            dword HarassingSiegeEngine3; // 0x000001D4 length: 4
            dword HarassingSiegeEngine4; // 0x000001D8 length: 4
            dword HarassingSiegeEngine5; // 0x000001DC length: 4
            dword HarassingSiegeEngine6; // 0x000001E0 length: 4
            dword HarassingSiegeEngine7; // 0x000001E4 length: 4
            dword HarassingSiegeEngine8; // 0x000001E8 length: 4
            dword HarassingSiegeEnginesMax; // 0x000001EC length: 4
            dword RaidRetargetDelay; // 0x000001F0 length: 4
            dword AttForceBase; // 0x000001F4 length: 4
            dword AttForceRandom; // 0x000001F8 length: 4
            dword AttForceSupportAllyThreshold; // 0x000001FC length: 4
            dword AttForceRallyPercentage; // 0x00000200 length: 4
            dword Unknown129; // 0x00000204 length: 4
            dword AttAssaultDelay; // 0x00000208 length: 4
            dword AttUnitPatrolRecommandDelay; // 0x0000020C length: 4
            dword Unknown132; // 0x00000210 length: 4
            dword SiegeEngine1; // 0x00000214 length: 4
            dword SiegeEngine2; // 0x00000218 length: 4
            dword SiegeEngine3; // 0x0000021C length: 4
            dword SiegeEngine4; // 0x00000220 length: 4
            dword SiegeEngine5; // 0x00000224 length: 4
            dword SiegeEngine6; // 0x00000228 length: 4
            dword SiegeEngine7; // 0x0000022C length: 4
            dword SiegeEngine8; // 0x00000230 length: 4
            dword CowThrowInterval; // 0x00000234 length: 4
            dword Unknown142; // 0x00000238 length: 4
            dword AttMaxEngineers; // 0x0000023C length: 4
            dword AttDiggingUnit; // 0x00000240 length: 4
            dword AttDiggingUnitMax; // 0x00000244 length: 4
            dword AttUnit2; // 0x00000248 length: 4
            dword AttUnit2Max; // 0x0000024C length: 4
            dword AttMaxAssassins; // 0x00000250 length: 4
            dword AttMaxLaddermen; // 0x00000254 length: 4
            dword AttMaxTunnelers; // 0x00000258 length: 4
            dword AttUnitPatrol; // 0x0000025C length: 4
            dword AttUnitPatrolMax; // 0x00000260 length: 4
            dword AttUnitPatrolGroupsCount; // 0x00000264 length: 4
            dword AttUnitBackup; // 0x00000268 length: 4
            dword AttUnitBackupMax; // 0x0000026C length: 4
            dword AttUnitBackupGroupsCount; // 0x00000270 length: 4
            dword AttUnitEngage; // 0x00000274 length: 4
            dword AttUnitEngageMax; // 0x00000278 length: 4
            dword AttUnitSiegeDef; // 0x0000027C length: 4
            dword AttUnitSiegeDefMax; // 0x00000280 length: 4
            dword AttUnitSiegeDefGroupsCount; // 0x00000284 length: 4
            dword AttUnitMain1; // 0x00000288 length: 4
            dword AttUnitMain2; // 0x0000028C length: 4
            dword AttUnitMain3; // 0x00000290 length: 4
            dword AttUnitMain4; // 0x00000294 length: 4
            dword AttMaxDefault; // 0x00000298 length: 4
            dword AttMainGroupsCount; // 0x0000029C length: 4
            AITargetChoiceInt TargetChoice; // 0x000002A0 length: 4

        } AICSpecification;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(AICSpecification) == 676, AICSpecification);
    } // namespace AIC
} // namespace AI
} // namespace OpenSHC
