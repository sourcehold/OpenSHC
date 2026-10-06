#include "../GameStateStructures.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Game::TrailType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00455E10
    void GameStateStructures::resetVariousCountsAndStatisticsAndStartGoodsAndResources()
    {
        for (int playerID = 1; playerID < 9; playerID++) {
            this->playerDataArray[playerID].weeksWithoutFood = 0;
            this->playerDataArray[playerID].foodTypesCurrentlyEaten = 0;
            this->playerDataArray[playerID].someCount40 = 0;
            this->playerDataArray[playerID].foodStorageLevelLastLastMonth = 0;
            this->playerDataArray[playerID].foodStorageLevelLastMonth = 0;
            this->playerDataArray[playerID].vclock = 2000;
            this->playerDataArray[playerID].someCount43 = 0;
            int startingPopularity = this->mapAndTime.startingPopularity * 10;
            this->playerDataArray[playerID].popularity = startingPopularity;
            this->playerDataArray[playerID].storedPopularityPercent = startingPopularity;
            this->playerDataArray[playerID].someCount44 = (short)startingPopularity;
            this->playerDataArray[playerID].taxesSetting = 3;
            this->playerDataArray[playerID].rationsSetting = 2;
            int currentPlayerRations
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .rationsSetting;
            this->playerDataArray[playerID].rationsSetting2 = currentPlayerRations;
            this->playerDataArray[playerID].rationsSetting3 = currentPlayerRations;
            this->playerDataArray[playerID].someCount45 = 1;
            this->playerDataArray[playerID].someCount46 = 1;
            this->playerDataArray[playerID].someCount47 = 0;
            this->playerDataArray[playerID].textYOffset = 0x3c;
            this->playerDataArray[playerID].someCountdown01 = 0;
            this->playerDataArray[playerID].playerDeathRelated = 0;
            this->playerDataArray[playerID].previousBlessedPeoplePercentage = 0;
            this->playerDataArray[playerID].popularityReligionBasedDiv25 = 0;
            this->playerDataArray[playerID].someCount48 = 0;
            this->playerDataArray[playerID].someCount49 = 0;
            this->playerDataArray[playerID].someCount50 = 0;
            this->playerDataArray[playerID].someCount51 = 0;
            this->playerDataArray[playerID].someCount52 = 0;
            this->playerDataArray[playerID].someCount53 = 0;
            this->playerDataArray[playerID].someCount54 = 0;
            this->playerDataArray[playerID].someCount55 = 0;
            this->playerDataArray[playerID].someCount56 = 0;
            this->playerDataArray[playerID].someCount57 = 0;
            this->playerDataArray[playerID].someCount58 = 0;
            this->playerDataArray[playerID].someCount59 = 0;
            this->playerDataArray[playerID].someCount60 = 0;
            this->playerDataArray[playerID].keepEnclosementRelatedCountdown = 0;
            this->playerDataArray[playerID].defensesDamagedByPlayer = 0;
            for (int resourceType = 0; resourceType < 25; resourceType++) {
                this->playerDataArray[playerID].startResources[resourceType]
                    = this->mapAndTime.startGoods[resourceType];
            }
            MACRO_CALL(OpenSHC::OS_Func::_memset)(this->playerDataArray[playerID].snoozedBuildings, 0, 100);
            this->playerDataArray[playerID].troopsKilled = 0;
            this->playerDataArray[playerID].troopsLost = 0;
            this->playerDataArray[playerID].weightedLosses = 0;
            this->playerDataArray[playerID].field25_0x40 = 0;
            this->playerDataArray[playerID].field26_0x42 = 0;
            if (this->mapAndTime.editScenarioExtraOptions != 0) {
                this->playerDataArray[playerID].taxesSetting = this->mapAndTime.scenarioTaxesSetting;
                int scenarioRations = this->mapAndTime.scenarioRationsSetting;
                this->playerDataArray[playerID].rationsSetting2 = scenarioRations;
                this->playerDataArray[playerID].rationsSetting3 = scenarioRations;
                this->playerDataArray[playerID].rationsSetting = scenarioRations;
                this->playerDataArray[playerID].currentResources[0xf] = this->mapAndTime.scenarioGold;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                int gameTypeMultiplier = 1;
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER)
                    && (DAT_GameCore::instance.isSkirmishTrail == TRUE)
                    && (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME)) {
                    gameTypeMultiplier = 3;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1) {
                    this->playerDataArray[playerID].startResources[0xf]
                        = DAT_RenderingDefinedData::instance
                              .field451_0x53bb4[(DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance
                                                    + DAT_GameSynchronyState::instance.skirmishGameIntensityType * 5)
                                      * 2
                                  + 0xc]
                        * gameTypeMultiplier;
                } else if (DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
                    this->playerDataArray[playerID].startResources[0xf]
                        = DAT_RenderingDefinedData::instance
                              .field451_0x53bb4[(DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance
                                                    + DAT_GameSynchronyState::instance.skirmishGameIntensityType * 5)
                                      * 2
                                  + 0xd]
                        * gameTypeMultiplier;
                }
            }
            DAT_GameState::instance.mapAndTime.populationIndex = 0;
            this->playerDataArray[playerID].beforeLastMonthsGold
                = (short)this->playerDataArray[playerID].currentResources[0xf];
            this->playerDataArray[playerID].lastMonthsGold
                = (short)this->playerDataArray[playerID].currentResources[0xf];
            this->playerDataArray[playerID].aiControlStatusRelated = -1000;
            for (int foodType = 0; foodType < 4; foodType++) {
                this->playerDataArray[playerID].isFoodTypeBanned[foodType] = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setCurrentAttackStrength, DAT_AICState::ptr)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setCurrentAttackRaidParameter, DAT_AICState::ptr)(playerID);
            DAT_GameState::instance.playerDataArray[playerID].nervousBikCountdown = 0x30;
            this->playerDataArray[playerID].tacticalPowersBarLevel = 0;
            this->playerDataArray[playerID].goldDonation = 0;
        }
    }
}
}
