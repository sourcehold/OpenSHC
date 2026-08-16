#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIC/AITargetChoice.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIC::AITargetChoice;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */
    // FUNCTION: STRONGHOLDCRUSADER 0x004C8D20
    void AICState ::setAICParameters_09(int param_1)
    {
        this->aics[param_1].unknown004 = 1;
        this->aics[param_1].unknown005 = 1;
        this->aics[param_1].minimumApples = 5;
        this->aics[param_1].minimumCheese = 5;
        this->aics[param_1].minimumBread = -1;
        this->aics[param_1].minimumWheat = -1;
        this->aics[param_1].minimumHop = -1;
        this->aics[param_1].maxWood = 0x3c;
        this->aics[param_1].maxStone = 0x3c;
        this->aics[param_1].flagType = 0xd;
        this->aics[param_1].unknown002 = 0;
        this->aics[param_1].unknown001 = 0;
        this->aics[param_1].unknown003 = 0;
        this->aics[param_1].criticalPopularity = 4000;
        this->aics[param_1].lowestPopularity = 0x157c;
        this->aics[param_1].highestPopularity = 9000;
        this->aics[param_1].taxesMin = 3;
        this->aics[param_1].taxesMax = 10;
        this->aics[param_1].farm1 = 0x21;
        this->aics[param_1].farm2 = 0x20;
        this->aics[param_1].farm3 = 0x1f;
        this->aics[param_1].populationPerFarm = 4;
        this->aics[param_1].unknown011 = 0xc;
        this->aics[param_1].maxFood = 200;
        this->aics[param_1].tradeAmountFood = 10;
        this->aics[param_1].tradeAmountEquipment = 0;
        this->aics[param_1].aiRequestDelay = 0x16;
        this->aics[param_1].minimumGoodsRequiredAfterTrade = 10;
        this->aics[param_1].doubleRationsFoodThreshold = 0x28;
        this->aics[param_1].maxResourceOther = 0xf;
        this->aics[param_1].maxEquipment = 0x14;
        this->aics[param_1].maxBeer = 10;
        this->aics[param_1].maxResourceVariance = 4;
        this->aics[param_1].recruitGoldThreshold = 200;
        this->aics[param_1].populationPerWoodcutter = 7;
        this->aics[param_1].populationPerQuarry = 0xc;
        this->aics[param_1].populationPerIronmine = 10;
        this->aics[param_1].populationPerPitchrig = 0;
        this->aics[param_1].maxQuarries = 4;
        this->aics[param_1].maxIronmines = 5;
        this->aics[param_1].maxWoodcutters = 0xc;
        this->aics[param_1].maxPitchrigs = 1;
        this->aics[param_1].maxFarms = 0xc;
        this->aics[param_1].buildInterval = 4;
        this->aics[param_1].resourceRebuildDelay = 0x1e;
        this->aics[param_1].blacksmithSetting = 0x16;
        this->aics[param_1].fletcherSetting = -999;
        this->aics[param_1].poleturnerSetting = 0x14;
        this->aics[param_1].sellResource04 = 7;
        this->aics[param_1].sellResource05 = 9;
        this->aics[param_1].sellResource07 = 0x10;
        this->aics[param_1].sellResource10 = 0x13;
        this->aics[param_1].sellResource11 = 0x14;
        this->aics[param_1].sellResource12 = 0x15;
        this->aics[param_1].defWallPatrolRallyTime = 8;
        this->aics[param_1].defWallPatrolGroups = 2;
        this->aics[param_1].defSiegeEngineGoldThreshold = 200;
        this->aics[param_1].defSiegeEngineBuildDelay = 2;
        this->aics[param_1].unknown072 = 100;
        this->aics[param_1].unknown073 = 0x14;
        this->aics[param_1].recruitProbDefWeak = 100;
        this->aics[param_1].recruitProbDefDefault = 0x32;
        this->aics[param_1].recruitProbDefStrong = 0x14;
        this->aics[param_1].recruitProbRaidWeak = 0;
        this->aics[param_1].recruitProbRaidDefault = 0x14;
        this->aics[param_1].AttForceSupportAllyThreshold = 0x14;
        this->aics[param_1].RecruitInterval = 4;
        this->aics[param_1].RecruitIntervalStrong = 4;
        this->aics[param_1].SortieUnitRanged = 0x16;
        this->aics[param_1].SortieUnitMeleeMin = 4;
        this->aics[param_1].DefDiggingUnitMax = 10;
        this->aics[param_1].DefDiggingUnit = 0x16;
        this->aics[param_1].OuterPatrolRallyDelay = 10;
        this->aics[param_1].DefUnit1 = 0x16;
        this->aics[param_1].DefUnit2 = 0x16;
        this->aics[param_1].RaidUnitsBase = 4;
        this->aics[param_1].AttForceRandom = 4;
        this->aics[param_1].recruitProbRaidStrong = 0x1e;
        this->aics[param_1].recruitProbAttackWeak = 0;
        this->aics[param_1].recruitProbAttackDefault = 0x1e;
        this->aics[param_1].recruitProbAttackStrong = 0x32;
        this->aics[param_1].RecruitIntervalWeak = 1;
        this->aics[param_1].SortieUnitRangedMin = 0xc;
        this->aics[param_1].SortieUnitMelee = 0x1b;
        this->aics[param_1].DefWalls = 0x32;
        this->aics[param_1].DefTotal = 0x50;
        this->aics[param_1].OuterPatrolGroupsCount = 2;
        this->aics[param_1].OuterPatrolGroupsMove = 1;
        this->aics[param_1].DefUnit3 = 0x17;
        this->aics[param_1].RaidUnitsRandom = 0;
        this->aics[param_1].RaidUnit1 = 0x1c;
        this->aics[param_1].HarassingSiegeEnginesMax = 2;
        this->aics[param_1].HarassingSiegeEngine1 = 0xbe;
        this->aics[param_1].RaidRetargetDelay = 6;
        this->aics[param_1].AttForceBase = 0x1e;
        this->aics[param_1].AttForceRallyPercentage = 0x32;
        this->aics[param_1].AttMovingTribesThreshold = 100;
        this->aics[param_1].AttAssaultDelay = 0x14;
        this->aics[param_1].AttUnitPatrolRecommandDelay = 5;
        this->aics[param_1].AttCoordinationPreference = 0x32;
        this->aics[param_1].CowThrowInterval = 10000;
        this->aics[param_1].SiegeEngine1 = 0x28;
        this->aics[param_1].SiegeEngine2 = 0x28;
        this->aics[param_1].SiegeEngine3 = 0x28;
        this->aics[param_1].SiegeEngine4 = 0x28;
        this->aics[param_1].SiegeEngine5 = 0x28;
        this->aics[param_1].SiegeEngine6 = 0x28;
        this->aics[param_1].AttMaxEngineers = 0x12;
        this->aics[param_1].AttDiggingUnit = 0x16;
        this->aics[param_1].AttDiggingUnitMax = 0x14;
        this->aics[param_1].AttMaxAssassins = 0;
        this->aics[param_1].AttUnit2 = 0;
        this->aics[param_1].AttUnit2Max = 0;
        this->aics[param_1].AttMaxLaddermen = 0;
        this->aics[param_1].AttMaxTunnelers = 0;
        this->aics[param_1].AttUnitPatrol = 0x17;
        this->aics[param_1].AttUnitPatrolMax = 0x14;
        this->aics[param_1].AttUnitPatrolGroupsCount = 1;
        this->aics[param_1].AttUnitBackup = 0x16;
        this->aics[param_1].AttUnitBackupMax = 0x1e;
        this->aics[param_1].AttUnitBackupGroupsCount = 2;
        this->aics[param_1].AttUnitEngageMax = 0;
        this->aics[param_1].AttUnitEngage = 0;
        this->aics[param_1].AttUnitSiegeDef = 0x17;
        this->aics[param_1].AttUnitSiegeDefMax = 10;
        this->aics[param_1].AttUnitSiegeDefGroupsCount = 1;
        this->aics[param_1].AttUnitMain1 = 0x1b;
        this->aics[param_1].AttUnitMain2 = 0x1b;
        this->aics[param_1].AttMaxDefault = 200;
        this->aics[param_1].AttMainGroupsCount = 4;
        this->aics[param_1].TargetChoice = OpenSHC::AI::AIC::AITC_GOLD;
        return;
    }
}
}
