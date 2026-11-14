#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CounterFoodWarningInterval.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Game {

    using Map::MapType2;
    using Resources::ResourceType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00458AD0
    void GameStateStructures::processFoodConsumption()
    {
        if (DAT_GameCore::instance.gameMode_2 == GM_EDITOR) {
            return;
        }
        if (DAT_GameCore::instance.gameMode_2 == GM_SIEGE_THAT) {
            return;
        }
        if (DAT_GameCore::instance.gameMode_2 == GM_BUILDERUnk
            && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE) {
            return;
        }
        MACRO_CALL_MEMBER(GameStateStructures_Func::updateFoodTypesInStockForAllPlayers, this)();
        for (int playerID = 1; playerID < 9; ++playerID) {
            if (this->playerDataArray[playerID].keep.id <= 0 || this->playerDataArray[playerID].campground.id <= 0) {
                continue;
            }
            this->playerDataArray[playerID].foodStorageLevel = -1;
            if (this->playerDataArray[playerID].foodTypesInStock <= 0) {
                this->playerDataArray[playerID].foodTypesCurrentlyEaten = 0;
                continue;
            }
            int foodClockSpeed = this->playerDataArray[playerID].currentPopulation * 3;
            this->playerDataArray[playerID].foodClockSpeed = foodClockSpeed;
            if (DAT_GameSynchronyState::instance.currentGameMode != GM_SOLITARY
                && MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::isAIPlayer, DAT_GameSynchronyState::ptr)(
                       playerID)
                    != FALSE) {
                this->playerDataArray[playerID].foodClockSpeed = (foodClockSpeed * 60) / 100;
            }
            switch (this->playerDataArray[playerID].rationsSetting) {
            case 0:
                this->playerDataArray[playerID].foodClockSpeed = 0;
                this->playerDataArray[playerID].foodTypesCurrentlyEaten = 0;
                break;
            case 1:
                this->playerDataArray[playerID].foodClockSpeed = this->playerDataArray[playerID].foodClockSpeed / 2;
                break;
            case 3:
                this->playerDataArray[playerID].foodClockSpeed
                    = (this->playerDataArray[playerID].foodClockSpeed * 3) / 2;
                break;
            case 4:
                this->playerDataArray[playerID].foodClockSpeed = this->playerDataArray[playerID].foodClockSpeed * 2;
            }
            int storageLevel = -1;
            if (this->playerDataArray[playerID].foodClockSpeed != 0) {
                storageLevel = ((15000 / this->playerDataArray[playerID].foodClockSpeed)
                                   * this->playerDataArray[playerID].totalFood)
                    / 800;
                this->playerDataArray[playerID].foodStorageLevel = storageLevel;
            }
            if (DAT_GameState::instance.mapAndTime.monthChanged != 0) {
                short leftover = (short)storageLevel;
                short lastMonthLeftover = this->playerDataArray[playerID].foodStorageLevelLastMonth;
                this->playerDataArray[playerID].foodStorageLevelLastLastMonth = lastMonthLeftover;
                this->playerDataArray[playerID].foodStorageLevelLastMonth = leftover;
                if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
                    && DAT_GameState::instance.mapAndTime.singlePlayerHasKeepAndGranary != FALSE) {
                    if (this->playerDataArray[playerID].totalFood == 0) {
                        if (DAT_CounterFoodWarningInterval::instance == 0
                            && MACRO_CALL_MEMBER(
                                   Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying, DAT_SoundSystemState::ptr)()
                                == FALSE) {
                            // "No food distributed this month"
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                "food_warning4.wav");
                        }
                        ++DAT_CounterFoodWarningInterval::instance;
                        if ((int)DAT_CounterFoodWarningInterval::instance > 2) {
                            DAT_CounterFoodWarningInterval::instance = 0;
                        }
                    } else if (leftover < 2 && leftover != lastMonthLeftover
                        && this->playerDataArray[playerID].rationsSetting != 0) {
                        if (leftover == 1) {
                            if (MACRO_CALL_MEMBER(
                                    Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying, DAT_SoundSystemState::ptr)()
                                == FALSE) {
                                // "Granary stocks are very low sire"
                                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    "food_warning2.wav");
                            }
                        } else if (MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying,
                                       DAT_SoundSystemState::ptr)()
                            == FALSE) {
                            // "We are almost out of food sire"
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                "food_warning3.wav");
                        }
                    }
                }
            }
            this->playerDataArray[playerID].foodClock
                = this->playerDataArray[playerID].foodClock + this->playerDataArray[playerID].foodClockSpeed;
            if (this->playerDataArray[playerID].foodClock > 15000) {
                this->playerDataArray[playerID].foodClock = 0;
                this->playerDataArray[playerID].foodTypesCurrentlyEaten
                    = this->playerDataArray[playerID].foodTypesInStock;
                while (true) {
                    this->playerDataArray[playerID].foodTypeToBeEatenNext
                        = this->playerDataArray[playerID].foodTypeToBeEatenNext + 1;
                    if (this->playerDataArray[playerID].foodTypeToBeEatenNext > 3) {
                        this->playerDataArray[playerID].foodTypeToBeEatenNext = 0;
                    }
                    if (this->playerDataArray[playerID].foodTypeToBeEatenNext == 0
                        && this->playerDataArray[playerID].breadCount > 0) {
                        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss,
                            DAT_BuildingsState::ptr)(playerID, Resources::RT_BREAD, 1, 0);
                        break;
                    }
                    if (this->playerDataArray[playerID].foodTypeToBeEatenNext == 1
                        && this->playerDataArray[playerID].cheeseCount > 0) {
                        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss,
                            DAT_BuildingsState::ptr)(playerID, Resources::RT_CHEESE, 1, 0);
                        break;
                    }
                    if (this->playerDataArray[playerID].foodTypeToBeEatenNext == 2
                        && this->playerDataArray[playerID].meatCount > 0) {
                        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss,
                            DAT_BuildingsState::ptr)(playerID, Resources::RT_MEAT, 1, 0);
                        break;
                    }
                    if (this->playerDataArray[playerID].foodTypeToBeEatenNext == 3
                        && this->playerDataArray[playerID].appleCount > 0) {
                        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss,
                            DAT_BuildingsState::ptr)(playerID, Resources::RT_APPLE, 1, 0);
                        break;
                    }
                }
            }
        }
    }

}
}
