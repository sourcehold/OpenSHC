#include "../AICState.func.hpp"

#include "OpenSHC/AI/AIC/AITargetChoice.hpp"

namespace OpenSHC {
namespace AI {

    using AIC::AITC_ANY;
    using AIC::AITC_BALANCED;
    using AIC::AITC_CLOSEST;
    using AIC::AITC_GOLD;
    using AIC::AITC_PLAYER;

    // FUNCTION: STRONGHOLDCRUSADER 0x004C7D20
    void AICState::setAICParameters_05(int aicIndex)
    {
        this->aics[aicIndex].flagType = 10;
        this->aics[aicIndex].unknown002 = 0;
        this->aics[aicIndex].unknown001 = 0;
        this->aics[aicIndex].unknown003 = 0;
        this->aics[aicIndex].unknown004 = 0;
        this->aics[aicIndex].unknown005 = 0;
        this->aics[aicIndex].criticalPopularity = 4000;
        this->aics[aicIndex].lowestPopularity = 5000;
        this->aics[aicIndex].highestPopularity = 8000;
        this->aics[aicIndex].taxesMin = 3;
        this->aics[aicIndex].taxesMax = 12;
        this->aics[aicIndex].farm1 = 31;
        this->aics[aicIndex].farm2 = 30;
        this->aics[aicIndex].farm3 = 30;
        this->aics[aicIndex].farm4 = 32;
        this->aics[aicIndex].populationPerFarm = 3;
        this->aics[aicIndex].unknown011 = 20;
        this->aics[aicIndex].maxFood = 50;
        this->aics[aicIndex].minimumApples = 5;
        this->aics[aicIndex].minimumCheese = 5;
        this->aics[aicIndex].minimumBread = 5;
        this->aics[aicIndex].minimumWheat = 5;
        this->aics[aicIndex].minimumHop = 5;
        this->aics[aicIndex].tradeAmountFood = 10;
        this->aics[aicIndex].tradeAmountEquipment = 0;
        this->aics[aicIndex].aiRequestDelay = 40;
        this->aics[aicIndex].minimumGoodsRequiredAfterTrade = 20;
        this->aics[aicIndex].doubleRationsFoodThreshold = 20;
        this->aics[aicIndex].maxWood = 60;
        this->aics[aicIndex].maxStone = 50;
        this->aics[aicIndex].maxResourceOther = 10;
        this->aics[aicIndex].maxEquipment = 5;
        this->aics[aicIndex].maxBeer = 10;
        this->aics[aicIndex].maxResourceVariance = 2;
        this->aics[aicIndex].recruitGoldThreshold = 200;
        this->aics[aicIndex].populationPerWoodcutter = 6;
        this->aics[aicIndex].populationPerQuarry = 10;
        this->aics[aicIndex].populationPerIronmine = 12;
        this->aics[aicIndex].populationPerPitchrig = 20;
        this->aics[aicIndex].maxQuarries = 4;
        this->aics[aicIndex].maxIronmines = 4;
        this->aics[aicIndex].maxWoodcutters = 14;
        this->aics[aicIndex].maxPitchrigs = 1;
        this->aics[aicIndex].maxFarms = 15;
        this->aics[aicIndex].buildInterval = 2;
        this->aics[aicIndex].resourceRebuildDelay = 40;
        this->aics[aicIndex].blacksmithSetting = 22;
        this->aics[aicIndex].fletcherSetting = 18;
        this->aics[aicIndex].poleturnerSetting = 20;
        this->aics[aicIndex].defWallPatrolRallyTime = 3;
        this->aics[aicIndex].defSiegeEngineGoldThreshold = 20;
        this->aics[aicIndex].defSiegeEngineBuildDelay = 8;
        this->aics[aicIndex].sellResource08 = 17;
        this->aics[aicIndex].sellResource09 = 18;
        this->aics[aicIndex].sellResource11 = 20;
        this->aics[aicIndex].sellResource12 = 21;
        this->aics[aicIndex].sellResource14 = 23;
        this->aics[aicIndex].defWallPatrolGroups = 4;
        this->aics[aicIndex].unknown072 = 100;
        this->aics[aicIndex].unknown073 = 20;
        this->aics[aicIndex].recruitProbDefWeak = 100;
        this->aics[aicIndex].recruitProbDefDefault = 34;
        this->aics[aicIndex].recruitProbDefStrong = 25;
        this->aics[aicIndex].recruitProbRaidWeak = 0;
        this->aics[aicIndex].recruitProbRaidDefault = 33;
        this->aics[aicIndex].recruitProbRaidStrong = 25;
        this->aics[aicIndex].recruitProbAttackWeak = 0;
        this->aics[aicIndex].recruitProbAttackDefault = 33;
        this->aics[aicIndex].recruitProbAttackStrong = 50;
        this->aics[aicIndex].RecruitIntervalWeak = 1;
        this->aics[aicIndex].RecruitInterval = 1;
        this->aics[aicIndex].RecruitIntervalStrong = 1;
        this->aics[aicIndex].SortieUnitRangedMin = 10;
        this->aics[aicIndex].SortieUnitRanged = 70;
        this->aics[aicIndex].SortieUnitMeleeMin = 7;
        this->aics[aicIndex].SortieUnitMelee = 75;
        this->aics[aicIndex].DefDiggingUnitMax = 4;
        this->aics[aicIndex].DefDiggingUnit = 71;
        this->aics[aicIndex].DefWalls = 50;
        this->aics[aicIndex].DefTotal = 70;
        this->aics[aicIndex].OuterPatrolGroupsCount = 2;
        this->aics[aicIndex].OuterPatrolGroupsMove = 1;
        this->aics[aicIndex].OuterPatrolRallyDelay = 10;
        this->aics[aicIndex].DefUnit1 = 75;
        this->aics[aicIndex].DefUnit2 = 70;
        this->aics[aicIndex].RaidUnitsBase = 10;
        this->aics[aicIndex].RaidUnitsRandom = 5;
        this->aics[aicIndex].DefUnit3 = 70;
        this->aics[aicIndex].DefUnit4 = 70;
        this->aics[aicIndex].DefUnit5 = 76;
        this->aics[aicIndex].RaidUnit1 = 74;
        this->aics[aicIndex].HarassingSiegeEnginesMax = 5;
        this->aics[aicIndex].HarassingSiegeEngine1 = 190;
        this->aics[aicIndex].RaidRetargetDelay = 3;
        this->aics[aicIndex].AttForceBase = 50;
        this->aics[aicIndex].AttForceRandom = 10;
        this->aics[aicIndex].AttForceSupportAllyThreshold = 8;
        this->aics[aicIndex].AttForceRallyPercentage = 80;
        this->aics[aicIndex].AttMovingTribesThreshold = 100;
        this->aics[aicIndex].AttAssaultDelay = 4;
        this->aics[aicIndex].AttUnitPatrolRecommandDelay = 1;
        this->aics[aicIndex].AttCoordinationPreference = 60;
        this->aics[aicIndex].CowThrowInterval = 2000;
        this->aics[aicIndex].SiegeEngine1 = 77;
        this->aics[aicIndex].SiegeEngine2 = 77;
        this->aics[aicIndex].SiegeEngine3 = 39;
        this->aics[aicIndex].SiegeEngine4 = 39;
        this->aics[aicIndex].AttMaxEngineers = 10;
        this->aics[aicIndex].AttDiggingUnit = 71;
        this->aics[aicIndex].AttDiggingUnitMax = 20;
        this->aics[aicIndex].AttMaxAssassins = 5;
        this->aics[aicIndex].AttUnit2 = 74;
        this->aics[aicIndex].AttUnit2Max = 20;
        this->aics[aicIndex].AttMaxLaddermen = 0;
        this->aics[aicIndex].AttMaxTunnelers = 0;
        this->aics[aicIndex].AttUnitPatrol = 74;
        this->aics[aicIndex].AttUnitPatrolMax = 20;
        this->aics[aicIndex].AttUnitPatrolGroupsCount = 1;
        this->aics[aicIndex].AttUnitBackup = 70;
        this->aics[aicIndex].AttUnitBackupMax = 20;
        this->aics[aicIndex].AttUnitBackupGroupsCount = 3;
        this->aics[aicIndex].AttUnitEngageMax = 0;
        this->aics[aicIndex].AttUnitEngage = 76;
        this->aics[aicIndex].AttUnitSiegeDef = 76;
        this->aics[aicIndex].AttUnitSiegeDefMax = 6;
        this->aics[aicIndex].AttUnitSiegeDefGroupsCount = 1;
        this->aics[aicIndex].AttUnitMain1 = 75;
        this->aics[aicIndex].AttMaxDefault = 200;
        this->aics[aicIndex].AttMainGroupsCount = 3;
        this->aics[aicIndex].TargetChoice = AITC_GOLD;
    }
}
}
