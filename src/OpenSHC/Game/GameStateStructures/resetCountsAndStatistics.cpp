#include "../GameStateStructures.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004560F0
    void GameStateStructures::resetCountsAndStatistics()
    {
        this->mapAndTime.field193_0x198 = 0;
        this->mapAndTime.deerCount = 0;
        this->mapAndTime.field3166_0x277c = 0;
        this->mapAndTime.field3168_0x2790 = 0;
        this->mapAndTime.field3170_0x27a4 = 0;
        this->mapAndTime.field3172_0x27ac = 0;
        for (int playerID = 1; playerID < 9; playerID++) {
            if (this->playerDataArray[playerID].someCountdown01 > 0) {
                this->playerDataArray[playerID].someCountdown01 = this->playerDataArray[playerID].someCountdown01 - 1;
            }
            this->playerDataArray[playerID].previousAvailablePeasants
                = this->playerDataArray[playerID].availablePeasantsOrHousedPeasants;
            this->playerDataArray[playerID].previousArmySize = this->playerDataArray[playerID].armySize;
            this->playerDataArray[playerID].previousSiegeWeaponsCount
                = this->playerDataArray[playerID].currentSiegeWeaponCount;
            this->playerDataArray[playerID].previousBlessedPeoplePercentage
                = (short)this->playerDataArray[playerID].blessedPeoplePercentage;
            this->playerDataArray[playerID].countEconomyBuilding_fixme = 0;
            this->playerDataArray[playerID].populationCap = 0;
            this->playerDataArray[playerID].countEntities = 0;
            this->playerDataArray[playerID].availablePeasantsAtFire = 0;
            this->playerDataArray[playerID].availablePeasantsOrHousedPeasants = 0;
            this->playerDataArray[playerID].count = 0;
            this->playerDataArray[playerID].currentPopulation_2 = 0;
            this->playerDataArray[playerID].nonInteractiveCitizenCountUnk = 0;
            this->playerDataArray[playerID].chickenCount2 = 0;
            this->playerDataArray[playerID].someCount02 = 0;
            this->playerDataArray[playerID].someCount03 = 0;
            this->playerDataArray[playerID].someCount04 = 0;
            this->playerDataArray[playerID].armySize = 0;
            this->playerDataArray[playerID].count_2 = 0;
            this->playerDataArray[playerID].currentSiegeWeaponCount = 0;
            this->playerDataArray[playerID].workingInnsCount = 0;
            this->playerDataArray[playerID].countInns = 0;
            this->playerDataArray[playerID].field645_0x2174 = 0;
            this->playerDataArray[playerID].blessedPeopleCountUnk = 0;
            this->playerDataArray[playerID].unblessedPeopleCountUnk = 0;
            this->playerDataArray[playerID].priestCountUnk = 0;
            this->playerDataArray[playerID].breadCount = 0;
            this->playerDataArray[playerID].cheeseCount = 0;
            this->playerDataArray[playerID].meatCount = 0;
            this->playerDataArray[playerID].appleCount = 0;
            this->playerDataArray[playerID].totalFood = 0;
            this->playerDataArray[playerID].foodTypesInStock = 0;
            this->playerDataArray[playerID].blessedPeoplePercentage = 0;
            this->playerDataArray[playerID].hasInitialResourceRecievingStarted = 0;
            this->playerDataArray[playerID].areCarnivalUnitsPresent = FALSE;
            this->playerDataArray[playerID].granaryIsAlmostFilledUp = TRUE;
            this->playerDataArray[playerID].isArmouryAlmostFilledUp = 1;
            this->playerDataArray[playerID].farmsWithoutWorkers = 0;
            this->playerDataArray[playerID].countFarms = 0;
            this->playerDataArray[playerID].countWoodcutters = 0;
            this->playerDataArray[playerID].noLabourerBuildingCount = 0;
            this->playerDataArray[playerID].someCount10 = 0;
            this->playerDataArray[playerID].someCount11 = 0;
            this->playerDataArray[playerID].countIronMines = 0;
            this->playerDataArray[playerID].countPitchRigs = 0;
            this->playerDataArray[playerID].countStoneQuarries = 0;
            this->playerDataArray[playerID].someCount12 = 0;
            this->playerDataArray[playerID].someCount13 = 0;
            this->playerDataArray[playerID].countFletchersPoleturners = 0;
            this->playerDataArray[playerID].countArmorersAndBlacksmiths = 0;
            this->playerDataArray[playerID].countBakers = 0;
            this->playerDataArray[playerID].countBrewers = 0;
            for (int targetSlot = 0; targetSlot < 100; targetSlot += 2) {
                this->playerDataArray[playerID].top100TargetableBuildings[targetSlot] = 0;
                this->playerDataArray[playerID].top100TargetableBuildings[targetSlot + 1] = 0;
            }
            this->playerDataArray[playerID].top100TargetableBuildingsTracker = 0;
            this->playerDataArray[playerID].rallySearchOffsetsUnk[0] = 0;
            this->playerDataArray[playerID].rallySearchOffsetsUnk[1] = 0;
            this->playerDataArray[playerID].rallySearchOffsetsUnk[2] = 0;
            this->playerDataArray[playerID].rallySearchOffsetsUnk[3] = 0;
            this->playerDataArray[playerID].rallySearchOffsetsUnk[4] = 0;
            this->playerDataArray[playerID].rallySearchOffsetsUnk[5] = 0;
            this->playerDataArray[playerID].rallySearchOffset = 0;
            this->playerDataArray[playerID].someCount20 = 0;
            this->playerDataArray[playerID].someCount21 = 0;
            this->playerDataArray[playerID].someCount22 = 0;
            this->playerDataArray[playerID].countArabianArchersRelated = 0;
            this->playerDataArray[playerID].countRelatedToHorseArchers = 0;
            this->playerDataArray[playerID].countSlaves = 0;
            this->playerDataArray[playerID].countAssassinsAndArabianSwordsman = 0;
            this->playerDataArray[playerID].countSlingers = 0;
            this->playerDataArray[playerID].countFireThrowers = 0;
            this->playerDataArray[playerID].someCount23 = 0;
            this->playerDataArray[playerID].someCount24 = 0;
            this->playerDataArray[playerID].someCount25 = 0;
            this->playerDataArray[playerID].someCount26 = 0;
            this->playerDataArray[playerID].currentArchers = 0;
            this->playerDataArray[playerID].currentCrossbowmen = 0;
            this->playerDataArray[playerID].currentSpearmen = 0;
            this->playerDataArray[playerID].currentPikemen = 0;
            this->playerDataArray[playerID].currentMacemen = 0;
            this->playerDataArray[playerID].currentSwordsmen = 0;
            this->playerDataArray[playerID].currentKnights = 0;
            this->playerDataArray[playerID].currentLaddermen = 0;
            this->playerDataArray[playerID].currentEngineers = 0;
            this->playerDataArray[playerID].currentTunnelers = 0;
            this->playerDataArray[playerID].someCount27 = 0;
            this->playerDataArray[playerID].someCount28 = 0;
            this->playerDataArray[playerID].someCount29 = 0;
            this->playerDataArray[playerID].someCount30 = 0;
            this->playerDataArray[playerID].someCount31 = 0;
            this->playerDataArray[playerID].currentResources[0] = 1;
            if (this->playerDataArray[playerID].aleRate < 1) {
                this->playerDataArray[playerID].aleRate = 30;
            }
            if (this->playerDataArray[playerID].someCount32 != 0) {
                this->playerDataArray[playerID].someCount32 = this->playerDataArray[playerID].someCount32 - 1;
            }
            if (this->playerDataArray[playerID].someCount33 != 0) {
                this->playerDataArray[playerID].someCount33 = this->playerDataArray[playerID].someCount33 - 1;
            }
        }
    }
}
}
