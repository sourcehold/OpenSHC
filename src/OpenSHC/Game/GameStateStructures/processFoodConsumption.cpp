#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
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

    // The original walks a pointer to foodClockSpeed and reaches every other PlayerData field by its distance from it.
    // Indexing playerDataArray[playerID] instead makes MSVC base the loop on another field, which shifts every
    // displacement, and reading foodStorageLevel back from the field (as the original does) then costs 20 points.
#define PLAYER_FIELD(type, field)                                                                                      \
    (*(type*)((char*)foodClockSpeed + offsetof(PlayerData, field) - offsetof(PlayerData, foodClockSpeed)))

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
        int playerID = 1;
        int* foodClockSpeed = &this->playerDataArray[1].foodClockSpeed;
        for (; playerID < 9; ++playerID, foodClockSpeed += sizeof(PlayerData) / sizeof(int)) {
            if (PLAYER_FIELD(int, buildingEntryInfos[Player::Enums::BEIE_KEEP].id) <= 0
                || PLAYER_FIELD(int, buildingEntryInfos[Player::Enums::BEIE_CAMPGROUND].id) <= 0) {
                continue;
            }
            PLAYER_FIELD(int, foodStorageLevel) = -1;
            if (PLAYER_FIELD(int, foodTypesInStock) <= 0) {
                PLAYER_FIELD(int, foodTypesCurrentlyEaten) = 0;
                continue;
            }
            int clockSpeed = PLAYER_FIELD(int, currentPopulation) * 3;
            PLAYER_FIELD(int, foodClockSpeed) = clockSpeed;
            if (DAT_GameSynchronyState::instance.currentGameMode != GM_SOLITARY
                && MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::isAIPlayer, DAT_GameSynchronyState::ptr)(
                       playerID)
                    != FALSE) {
                PLAYER_FIELD(int, foodClockSpeed) = (clockSpeed * 60) / 100;
            }
            switch (PLAYER_FIELD(int, rationsSetting)) {
            case 0:
                PLAYER_FIELD(int, foodClockSpeed) = 0;
                PLAYER_FIELD(int, foodTypesCurrentlyEaten) = 0;
                break;
            case 1:
                PLAYER_FIELD(int, foodClockSpeed) = PLAYER_FIELD(int, foodClockSpeed) / 2;
                break;
            case 3:
                PLAYER_FIELD(int, foodClockSpeed) = (PLAYER_FIELD(int, foodClockSpeed) * 3) / 2;
                break;
            case 4:
                PLAYER_FIELD(int, foodClockSpeed) = PLAYER_FIELD(int, foodClockSpeed) * 2;
            }
            if (PLAYER_FIELD(int, foodClockSpeed) != 0) {
                PLAYER_FIELD(int, foodStorageLevel)
                    = ((15000 / PLAYER_FIELD(int, foodClockSpeed)) * PLAYER_FIELD(int, totalFood)) / 800;
            }
            if (DAT_GameState::instance.mapAndTime.monthChanged != 0) {
                short leftover = (short)PLAYER_FIELD(int, foodStorageLevel);
                PLAYER_FIELD(short, foodStorageLevelLastLastMonth) = PLAYER_FIELD(short, foodStorageLevelLastMonth);
                PLAYER_FIELD(short, foodStorageLevelLastMonth) = leftover;
                if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
                    && DAT_GameState::instance.mapAndTime.singlePlayerHasKeepAndGranary != FALSE) {
                    if (PLAYER_FIELD(int, totalFood) == 0) {
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
                    } else if (leftover < 2 && leftover != PLAYER_FIELD(short, foodStorageLevelLastLastMonth)
                        && PLAYER_FIELD(int, rationsSetting) != 0) {
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
            PLAYER_FIELD(int, foodClock) = PLAYER_FIELD(int, foodClock) + PLAYER_FIELD(int, foodClockSpeed);
            if (PLAYER_FIELD(int, foodClock) > 15000) {
                PLAYER_FIELD(int, foodClock) = 0;
                PLAYER_FIELD(int, foodTypesCurrentlyEaten) = PLAYER_FIELD(int, foodTypesInStock);
                while (true) {
                    PLAYER_FIELD(int, foodTypeToBeEatenNext) = PLAYER_FIELD(int, foodTypeToBeEatenNext) + 1;
                    if (PLAYER_FIELD(int, foodTypeToBeEatenNext) > 3) {
                        PLAYER_FIELD(int, foodTypeToBeEatenNext) = 0;
                    }
                    if (PLAYER_FIELD(int, foodTypeToBeEatenNext) == 0 && PLAYER_FIELD(int, breadCount) > 0) {
                        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss,
                            DAT_BuildingsState::ptr)(playerID, Resources::RT_BREAD, 1, 0);
                        break;
                    }
                    if (PLAYER_FIELD(int, foodTypeToBeEatenNext) == 1 && PLAYER_FIELD(int, cheeseCount) > 0) {
                        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss,
                            DAT_BuildingsState::ptr)(playerID, Resources::RT_CHEESE, 1, 0);
                        break;
                    }
                    if (PLAYER_FIELD(int, foodTypeToBeEatenNext) == 2 && PLAYER_FIELD(int, meatCount) > 0) {
                        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss,
                            DAT_BuildingsState::ptr)(playerID, Resources::RT_MEAT, 1, 0);
                        break;
                    }
                    if (PLAYER_FIELD(int, foodTypeToBeEatenNext) == 3 && PLAYER_FIELD(int, appleCount) > 0) {
                        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss,
                            DAT_BuildingsState::ptr)(playerID, Resources::RT_APPLE, 1, 0);
                        break;
                    }
                }
            }
        }
    }

#undef PLAYER_FIELD

}
}
