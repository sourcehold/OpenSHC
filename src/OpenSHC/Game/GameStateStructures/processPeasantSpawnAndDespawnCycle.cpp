#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
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

    using OpenSHC::Audio::SFX::SpeechEffectID;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::MapType2;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0045B4A0
    void GameStateStructures::processPeasantSpawnAndDespawnCycle()
    {
        /*
          handle peasant (de)spawning
         */
        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk)
            && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE)) {
            return;
        }
        for (int playerID = 1; playerID < 9; playerID++) {
            if (this->playerDataArray[playerID].lordKilledByPlayerID != 0) {
                continue;
            }
            if ((this->playerDataArray[playerID].playerDeathRelated != 0)
                && (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)) {
                continue;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                this->playerDataArray[playerID].vclockIncrement
                    = DAT_TroopDefinedData::instance
                          .PeasantSpawnClockIncrementSkirmish[this->playerDataArray[playerID].popularity / 500];
            } else {
                int popularityIndex = this->playerDataArray[playerID].popularity / 500;
                if (this->playerDataArray[playerID].currentPopulation > 100) {
                    this->playerDataArray[playerID].vclockIncrement
                        = DAT_TroopDefinedData::instance
                              .PeasantSpawnClockIncrementSolitaryPopMoreThan100[popularityIndex];
                } else {
                    this->playerDataArray[playerID].vclockIncrement
                        = DAT_TroopDefinedData::instance
                              .PeasantSpawnClockIncrementSolitaryPopLessThan101[popularityIndex];
                }
            }
            this->playerDataArray[playerID].vclock
                = this->playerDataArray[playerID].vclockIncrement + this->playerDataArray[playerID].vclock;
            if (this->playerDataArray[playerID].vclock >= 4000) {
                this->playerDataArray[playerID].vclock = 4000;
            } else if (this->playerDataArray[playerID].vclock < 0) {
                this->playerDataArray[playerID].vclock = 0;
            }
            if (this->playerDataArray[playerID].vclockIncrement == 0) {
                this->playerDataArray[playerID].vclock = 2000;
            }
            if (this->playerDataArray[playerID].keep.id <= 0) {
                continue;
            }
            int campgroundID = this->playerDataArray[playerID].campground.id;
            if (campgroundID <= 0) {
                continue;
            }
            if (this->playerDataArray[playerID].vclock >= 4000) {
                if ((this->playerDataArray[playerID].currentPopulation < this->playerDataArray[playerID].populationCap)
                    && (this->playerDataArray[playerID].availablePeasantsOrHousedPeasants < 24)) {
                    /*
                      Havent reached peasant limit.
                     */
                    int x = this->playerDataArray[playerID].campground.xEntry;
                    int y = this->playerDataArray[playerID].campground.yEntry;
                    this->playerDataArray[playerID].vclock = 2000;
                    int peasantUnitID = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(playerID, playerID, x * 8,
                        y * 8, DAT_BuildingsState::instance.buildings[campgroundID].terrainHeightUnk,
                        OpenSHC::Map::Units::UT_PEASANT);
                    if (peasantUnitID != 0) {
                        /*
                          Successfully spawned peasant.
                         */
                        DAT_UnitsState::instance.units[peasantUnitID].animationCycleNumber
                            = DAT_UnitsState::instance.units[peasantUnitID].fixedRng & 0xf;
                        DAT_UnitsState::instance.units[peasantUnitID].isDisappearingUnk = 1;
                        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                            MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialBuildingActionState)(
                                9, OpenSHC::Map::Buildings::BT_HOVEL);
                        }
                    }
                    if (this->playerDataArray[playerID].field26_0x42 == 1) {
                        this->playerDataArray[playerID].field26_0x42 = 0;
                        if ((playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)
                            && (MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying,
                                    DAT_SoundSystemState::ptr)()
                                == FALSE)) {
                            /*
                              people are coming to the castle
                             */
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                                OpenSHC::Audio::SFX::SEID_POP_IMMIGRATE);
                        }
                    }
                }
            } else if ((this->playerDataArray[playerID].vclock <= 0)
                && (this->playerDataArray[playerID].availablePeasantsOrHousedPeasants
                        + this->playerDataArray[playerID].populationRelatedCrowdingCountUnk
                    > 4)) {
                this->playerDataArray[playerID].vclock = 2000;
                /*
                  let a peasant disappear?
                 */
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::despawnPeasantOrWorker, this)(playerID);
                if (this->playerDataArray[playerID].field26_0x42 == 0) {
                    this->playerDataArray[playerID].field26_0x42 = 1;
                    if ((playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)
                        && (MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying,
                                DAT_SoundSystemState::ptr)()
                            == FALSE)) {
                        /*
                          sound is probably about peasants leaving the castle
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                            OpenSHC::Audio::SFX::SEID_POP_EMIGRATE);
                    }
                }
            }
        }
    }
}
}
