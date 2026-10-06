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
            for (int targetSlot = 0; targetSlot < 100; targetSlot++) {
                this->playerDataArray[playerID].top100TargetableBuildings[targetSlot] = 0;
            }
            this->playerDataArray[playerID].top100TargetableBuildingsTracker = 0;
            /*
              clears the 20 counters from rallySearchOffsetsUnk up to and including someCount26 as one array,
              exactly as the original binary does
             */
            for (int counterIndex = 0; counterIndex < 20; counterIndex++) {
                this->playerDataArray[playerID].rallySearchOffsetsUnk[counterIndex] = 0;
            }
            /*
              clears the 10 troop counters from currentArchers up to and including currentTunnelers as one array
             */
            for (int troopIndex = 0; troopIndex < 10; troopIndex++) {
                (&this->playerDataArray[playerID].currentArchers)[troopIndex] = 0;
            }
            this->playerDataArray[playerID].someCount27 = 0;
            this->playerDataArray[playerID].someCount28 = 0;
            this->playerDataArray[playerID].someCount29 = 0;
            this->playerDataArray[playerID].someCount30 = 0;
            this->playerDataArray[playerID].someCount31 = 0;
            this->playerDataArray[playerID].currentResources[0] = 1;
            if (this->playerDataArray[playerID].aleRate <= 0) {
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
