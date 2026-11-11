#include "../AICState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using namespace OpenSHC::Game::Resources;
    using namespace OpenSHC::Map::Buildings;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CBA50
    void AICState::planToBuyWhenLowOnResourceAndSnoozeBuildings(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL) {
            return;
        }

        BOOLEnum allowFletchers = TRUE;
        BOOLEnum allowFarms = TRUE;
        BOOLEnum allowIronMines = TRUE;
        BOOLEnum allowQuarries = TRUE;
        BOOLEnum allowPitchRigs = TRUE;
        BOOLEnum allowWoodcutters = TRUE;
        BOOLEnum allowPoleturners = TRUE;
        BOOLEnum allowBlacksmiths = TRUE;
        BOOLEnum allowArmourers = TRUE;
        BOOLEnum allowTanners = TRUE;
        BOOLEnum allowBakeries = TRUE;
        BOOLEnum allowBreweries = TRUE;
        BOOLEnum allowInns = TRUE;
        BOOLEnum allowWells = TRUE;

        int buildingBurning = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::playerHasBurningBuilding, DAT_BuildingsState::ptr)(playerID);
        int wood = DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_WOOD];

        if (wood <= 0) {
            DAT_GameState::instance.playerDataArray[playerID].noWoodTracker++;
        } else {
            DAT_GameState::instance.playerDataArray[playerID].noWoodTracker = 0;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_IRON] <= 0) {
            DAT_GameState::instance.playerDataArray[playerID].noIronTracker++;
        } else {
            DAT_GameState::instance.playerDataArray[playerID].noIronTracker = 0;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_FLOUR] <= 0) {
            DAT_GameState::instance.playerDataArray[playerID].noFlourTracker++;
        } else {
            DAT_GameState::instance.playerDataArray[playerID].noFlourTracker = 0;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_HOPS] <= 0) {
            DAT_GameState::instance.playerDataArray[playerID].noHopsTracker++;
        } else {
            DAT_GameState::instance.playerDataArray[playerID].noHopsTracker = 0;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_ALE] <= 0) {
            DAT_GameState::instance.playerDataArray[playerID].noBeerCounterUnk++;
        } else {
            DAT_GameState::instance.playerDataArray[playerID].noBeerCounterUnk = 0;
        }
        DAT_GameState::instance.playerDataArray[playerID].someResourceCounter++;

        if (DAT_GameState::instance.playerDataArray[playerID].countFletchersPoleturners <= 0) {
            DAT_GameState::instance.playerDataArray[playerID].noWoodTracker = 0;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].countArmorersAndBlacksmiths <= 0) {
            DAT_GameState::instance.playerDataArray[playerID].noIronTracker = 0;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].countBakers <= 0) {
            DAT_GameState::instance.playerDataArray[playerID].noFlourTracker = 0;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].countBrewers <= 0) {
            DAT_GameState::instance.playerDataArray[playerID].noHopsTracker = 0;
        }

        int population = DAT_GameState::instance.playerDataArray[playerID].currentPopulation;
        if (population < 10) {
            if (DAT_GameState::instance.playerDataArray[playerID].farmsWithoutWorkers != 0) {
                allowQuarries = FALSE;
            } else if (DAT_GameState::instance.playerDataArray[playerID].countWoodcutters > 2) {
                allowQuarries = FALSE;
            }
        }

        if (wood >= 20 && population < 10 && DAT_GameState::instance.playerDataArray[playerID].farmsWithoutWorkers != 0
            && DAT_GameState::instance.playerDataArray[playerID].totalFood < 8) {
            allowWoodcutters = FALSE;
        }

        if (buildingBurning == 0
            && DAT_GameState::instance.playerDataArray[playerID].farmsWithoutWorkers
                >= DAT_GameState::instance.playerDataArray[playerID].countFarms
            && DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_GOLD] < 500) {
            allowWells = FALSE;
        }

        if (DAT_GameState::instance.playerDataArray[playerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                .id
            == 0) {
            allowFletchers = FALSE;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].noWoodTracker > 36) {
            allowFletchers = FALSE;
        }
        if (DAT_GameState::instance.playerDataArray[playerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                .id
            == 0) {
            allowPoleturners = FALSE;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].noWoodTracker > 36) {
            allowPoleturners = FALSE;
        }
        if (DAT_GameState::instance.playerDataArray[playerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                .id
            == 0) {
            allowBlacksmiths = FALSE;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].noIronTracker > 36) {
            allowBlacksmiths = FALSE;
        }
        if (DAT_GameState::instance.playerDataArray[playerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                .id
            == 0) {
            allowArmourers = FALSE;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].noIronTracker > 36) {
            allowArmourers = FALSE;
        }
        if (DAT_GameState::instance.playerDataArray[playerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                .id
            == 0) {
            allowTanners = FALSE;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].someResourceCounter > 36) {
            allowTanners = FALSE;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].noFlourTracker > 36) {
            allowBakeries = FALSE;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].noHopsTracker > 72) {
            allowBreweries = FALSE;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].noBeerCounterUnk > 72) {
            allowInns = FALSE;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker > 0) {
            allowFletchers = TRUE;
            allowFarms = FALSE;
            allowQuarries = FALSE;
            allowIronMines = FALSE;
            allowPitchRigs = FALSE;
            allowWoodcutters = FALSE;
            allowPoleturners = TRUE;
            allowBlacksmiths = TRUE;
            allowArmourers = TRUE;
            allowTanners = TRUE;
            allowBakeries = FALSE;
            allowBreweries = FALSE;
            allowInns = FALSE;
        }

        if (allowWells) {
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_WELL] = false;
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_WATERPOT] = false;
        } else {
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_WELL] = true;
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_WATERPOT] = true;
        }

        if (allowQuarries) {
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_QUARRY] = false;
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_OXTETHER] = false;
        } else {
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_QUARRY] = true;
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_OXTETHER] = true;
        }

        DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_WOODCUTTERSHUT] = !allowWoodcutters;
        DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_IRONMINE] = !allowIronMines;
        DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_PITCHRIG] = !allowPitchRigs;
        DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_FLETCHER] = !allowFletchers;
        DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_POLETURNER] = !allowPoleturners;
        DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_BLACKSMITH] = !allowBlacksmiths;
        DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_ARMOURER] = !allowArmourers;
        DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_TANNER] = !allowTanners;
        DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_BAKERY] = !allowBakeries;
        DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_BREWERY] = !allowBreweries;
        DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_INN] = !allowInns;

        if (allowFarms) {
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_WHEATFARM] = false;
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_HOPFARM] = false;
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_APPLEFARM] = false;
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_DAIRYFARM] = false;
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_HUNTERSHUT] = false;
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_MILL] = false;
        } else {
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_WHEATFARM] = true;
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_HOPFARM] = true;
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_APPLEFARM] = true;
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_DAIRYFARM] = true;
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_HUNTERSHUT] = true;
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[BT_MILL] = true;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].canStartSpending == 0) {
            return;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].noWoodTracker > 36
            && DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[RT_WOOD] == 0) {
            DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[RT_WOOD] = 5;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].noIronTracker > 36
            && DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[RT_IRON] == 0) {
            DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[RT_IRON] = 2;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].noFlourTracker > 36
            && DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[RT_FLOUR] == 0) {
            DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[RT_FLOUR] = 2;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].noHopsTracker > 72
            && DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[RT_HOPS] == 0) {
            DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[RT_HOPS] = 2;
        }
    }

}
}
