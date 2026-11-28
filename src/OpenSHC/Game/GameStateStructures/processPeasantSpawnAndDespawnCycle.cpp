#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TroopDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    using Audio::SFX::SpeechEffectID;
    using Map::MapType2;
    using Map::Buildings::BuildingType;
    using Map::Units::UnitType;
    using WindowsHelper::Enums::BOOLEnum;

// The original walks a pointer to vclockIncrement and reaches the other PlayerData fields by their distance from
// it. Indexing playerDataArray[playerID] instead makes MSVC base the loop on popularity.
#define PLAYER_FIELD(type, field)                                                                                      \
    (*(type*)((char*)vclockIncrement + offsetof(PlayerData, field) - offsetof(PlayerData, vclockIncrement)))

    // FUNCTION: STRONGHOLDCRUSADER 0x0045B4A0
    void GameStateStructures::processPeasantSpawnAndDespawnCycle()
    {
        // handle peasant (de)spawning
        if (DAT_GameCore::instance.gameMode_2 == GM_BUILDERUnk
            && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE) {
            return;
        }
        int playerID = 1;
        int* vclockIncrement = &this->playerDataArray[1].vclockIncrement;
        for (; playerID < 9; ++playerID, vclockIncrement += sizeof(PlayerData) / sizeof(int)) {
            if (PLAYER_FIELD(int, lordKilledByPlayerID) != 0) {
                continue;
            }
            if (PLAYER_FIELD(int, playerDeathRelated) != 0
                && DAT_GameSynchronyState::instance.currentGameMode == GM_SOLITARY) {
                continue;
            }
            // The original picks the increment into a register and stores it once, then reuses that register for
            // the sum and for the zero test below.
            int increment;
            if (DAT_GameSynchronyState::instance.currentGameMode != GM_SOLITARY) {
                increment = DAT_TroopDefinedData::instance
                                .PeasantSpawnClockIncrementSkirmish[PLAYER_FIELD(int, popularity) / 500];
            } else {
                int popularityIndex = PLAYER_FIELD(int, popularity) / 500;
                if (PLAYER_FIELD(int, currentPopulation) > 100) {
                    increment = DAT_TroopDefinedData::instance
                                    .PeasantSpawnClockIncrementSolitaryPopMoreThan100[popularityIndex];
                } else {
                    increment = DAT_TroopDefinedData::instance
                                    .PeasantSpawnClockIncrementSolitaryPopLessThan101[popularityIndex];
                }
            }
            PLAYER_FIELD(int, vclockIncrement) = increment;
            int const vclock = PLAYER_FIELD(int, vclock) + increment;
            PLAYER_FIELD(int, vclock) = vclock;
            if (vclock >= 4000) {
                PLAYER_FIELD(int, vclock) = 4000;
            } else if (vclock < 0) {
                PLAYER_FIELD(int, vclock) = 0;
            }
            if (increment == 0) {
                PLAYER_FIELD(int, vclock) = 2000;
            }
            if (PLAYER_FIELD(int, buildingEntryInfos[Player::Enums::BEIE_KEEP].id) <= 0) {
                continue;
            }
            int campgroundID = PLAYER_FIELD(int, buildingEntryInfos[Player::Enums::BEIE_CAMPGROUND].id);
            if (campgroundID <= 0) {
                continue;
            }
            if (PLAYER_FIELD(int, vclock) >= 4000) {
                if (PLAYER_FIELD(int, currentPopulation) < PLAYER_FIELD(int, populationCap)
                    && PLAYER_FIELD(int, availablePeasantsOrHousedPeasants) < 24) {
                    // Havent reached peasant limit.
                    int x = PLAYER_FIELD(int, buildingEntryInfos[Player::Enums::BEIE_CAMPGROUND].xEntry) * 8;
                    int y = PLAYER_FIELD(int, buildingEntryInfos[Player::Enums::BEIE_CAMPGROUND].yEntry) * 8;
                    PLAYER_FIELD(int, vclock) = 2000;
                    int peasantUnitID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                        playerID, playerID, x, y, DAT_BuildingsState::instance.buildings[campgroundID].terrainHeightUnk,
                        Map::Units::UT_PEASANT);
                    if (peasantUnitID != 0) {
                        // Successfully spawned peasant.
                        DAT_UnitsState::instance.units[peasantUnitID].animationCycleNumber
                            = DAT_UnitsState::instance.units[peasantUnitID].fixedRng & 0xf;
                        DAT_UnitsState::instance.units[peasantUnitID].isDisappearingUnk = 1;
                        if (DAT_GameCore::instance.gameMode_2 == GM_CRUSADER_TUTORIAL) {
                            MACRO_CALL(UI::Helpers_Func::SetTutorialBuildingActionState)(9, Map::Buildings::BT_HOVEL);
                        }
                    }
                    if (PLAYER_FIELD(short, field_0x42) == 1) {
                        PLAYER_FIELD(short, field_0x42) = 0;
                        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
                            && MACRO_CALL_MEMBER(
                                   Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying, DAT_SoundSystemState::ptr)()
                                == FALSE) {
                            // people are coming to the castle
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                                Audio::SFX::SEID_POP_IMMIGRATE);
                        }
                    }
                }
            } else if (PLAYER_FIELD(int, vclock) <= 0
                && PLAYER_FIELD(int, availablePeasantsOrHousedPeasants)
                        + PLAYER_FIELD(int, populationRelatedCrowdingCountUnk)
                    > 4) {
                PLAYER_FIELD(int, vclock) = 2000;
                // let a peasant disappear?
                MACRO_CALL_MEMBER(GameStateStructures_Func::despawnPeasantOrWorker, this)(playerID);
                if (PLAYER_FIELD(short, field_0x42) == 0) {
                    PLAYER_FIELD(short, field_0x42) = 1;
                    if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
                        && MACRO_CALL_MEMBER(
                               Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying, DAT_SoundSystemState::ptr)()
                            == FALSE) {
                        // sound is probably about peasants leaving the castle
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                            Audio::SFX::SEID_POP_EMIGRATE);
                    }
                }
            }
        }
    }

#undef PLAYER_FIELD

}
}
