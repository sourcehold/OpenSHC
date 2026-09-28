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
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Map::MapType2;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00458AD0
    void GameStateStructures::processFoodConsumption()
    {
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
            return;
        }
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
            return;
        }
        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk)
            && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE)) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::updateFoodTypesInStockForAllPlayers, this)();
        for (int playerID = 1; playerID < 9; playerID++) {
            if ((this->playerDataArray[playerID].keep.id <= 0)
                || (this->playerDataArray[playerID].campground.id <= 0)) {
                continue;
            }
            this->playerDataArray[playerID].foodStorageLevel = -1;
            if (this->playerDataArray[playerID].foodTypesInStock < 1) {
                this->playerDataArray[playerID].foodTypesCurrentlyEaten = 0;
                continue;
            }
            this->playerDataArray[playerID].foodClockSpeed
                = this->playerDataArray[playerID].currentPopulation * 3;
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                && (MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                        DAT_GameSynchronyState::ptr)(playerID)
                    != FALSE)) {
                this->playerDataArray[playerID].foodClockSpeed
                    = (this->playerDataArray[playerID].currentPopulation * 180) / 100;
            }
            switch (this->playerDataArray[playerID].rationsSetting) {
            case 0:
                this->playerDataArray[playerID].foodClockSpeed = 0;
                this->playerDataArray[playerID].foodTypesCurrentlyEaten = 0;
                break;
            case 1:
                this->playerDataArray[playerID].foodClockSpeed
                    = this->playerDataArray[playerID].foodClockSpeed / 2;
                break;
            case 3:
                this->playerDataArray[playerID].foodClockSpeed
                    = (this->playerDataArray[playerID].foodClockSpeed * 3) / 2;
                break;
            case 4:
                this->playerDataArray[playerID].foodClockSpeed
                    = this->playerDataArray[playerID].foodClockSpeed * 2;
            }
            if (this->playerDataArray[playerID].foodClockSpeed != 0) {
                this->playerDataArray[playerID].foodStorageLevel
                    = ((15000 / this->playerDataArray[playerID].foodClockSpeed)
                          * this->playerDataArray[playerID].totalFood)
                    / 800;
            }
            if (this->mapAndTime.monthChanged != 0) {
                short leftover = (short)this->playerDataArray[playerID].foodStorageLevel;
                short lastMonthLeftover = this->playerDataArray[playerID].foodStorageLevelLastMonth;
                this->playerDataArray[playerID].foodStorageLevelLastLastMonth = lastMonthLeftover;
                this->playerDataArray[playerID].foodStorageLevelLastMonth = leftover;
                if ((playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)
                    && (this->mapAndTime.singlePlayerHasKeepAndGranary != FALSE)) {
                    if (this->playerDataArray[playerID].totalFood == 0) {
                        if ((DAT_CounterFoodWarningInterval::instance == 0)
                            && (MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying,
                                    DAT_SoundSystemState::ptr)()
                                == FALSE)) {
                            /*
                              "No food distributed this month"
                             */
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                "food_warning4.wav");
                        }
                        DAT_CounterFoodWarningInterval::instance = DAT_CounterFoodWarningInterval::instance + 1;
                        if ((int)DAT_CounterFoodWarningInterval::instance > 2) {
                            DAT_CounterFoodWarningInterval::instance = 0;
                        }
                    } else if ((leftover < 2) && (leftover != lastMonthLeftover)
                        && (this->playerDataArray[playerID].rationsSetting != 0)) {
                        if (leftover == 1) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying,
                                    DAT_SoundSystemState::ptr)()
                                == FALSE) {
                                /*
                                  "Granary stocks are very low sire"
                                 */
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX,
                                    DAT_SFXState::ptr)("food_warning2.wav");
                            }
                        } else if (MACRO_CALL_MEMBER(
                                       OpenSHC::Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying,
                                       DAT_SoundSystemState::ptr)()
                            == FALSE) {
                            /*
                              "We are almost out of food sire"
                             */
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                "food_warning3.wav");
                        }
                    }
                }
            }
            this->playerDataArray[playerID].foodClock = this->playerDataArray[playerID].foodClock
                + this->playerDataArray[playerID].foodClockSpeed;
            if (this->playerDataArray[playerID].foodClock > 15000) {
                this->playerDataArray[playerID].foodClock = 0;
                this->playerDataArray[playerID].foodTypesCurrentlyEaten
                    = this->playerDataArray[playerID].foodTypesInStock;
                ResourceType resourceType;
                while (true) {
                    this->playerDataArray[playerID].foodTypeToBeEatenNext
                        = this->playerDataArray[playerID].foodTypeToBeEatenNext + 1;
                    if (this->playerDataArray[playerID].foodTypeToBeEatenNext >= 4) {
                        this->playerDataArray[playerID].foodTypeToBeEatenNext = 0;
                    }
                    if ((this->playerDataArray[playerID].foodTypeToBeEatenNext == 0)
                        && (this->playerDataArray[playerID].breadCount > 0)) {
                        resourceType = OpenSHC::Game::Resources::RT_BREAD;
                        break;
                    }
                    if ((this->playerDataArray[playerID].foodTypeToBeEatenNext == 1)
                        && (this->playerDataArray[playerID].cheeseCount > 0)) {
                        resourceType = OpenSHC::Game::Resources::RT_CHEESE;
                        break;
                    }
                    if ((this->playerDataArray[playerID].foodTypeToBeEatenNext == 2)
                        && (this->playerDataArray[playerID].meatCount > 0)) {
                        resourceType = OpenSHC::Game::Resources::RT_MEAT;
                        break;
                    }
                    if ((this->playerDataArray[playerID].foodTypeToBeEatenNext == 3)
                        && (this->playerDataArray[playerID].appleCount > 0)) {
                        resourceType = OpenSHC::Game::Resources::RT_APPLE;
                        break;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                    DAT_BuildingsState::ptr)(playerID, resourceType, 1, 0);
            }
        }
    }
}
}
