#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Audio/SFX.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;

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
    // FUNCTION: STRONGHOLDCRUSADER 0x0045CA20
    void GameStateStructures::processSingleTimeTick()
    {
        if (this->gameTicksLoadBalancer != 0) {
            if ((this->gameTicksLoadBalancer >= 10) && (this->gameTicksLoadBalancer < 19)) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::recomputeTroopValuesForPlayer,
                    DAT_UnitsState::ptr)(this->gameTicksLoadBalancer - 10);
            } else if (this->gameTicksLoadBalancer == 20) {
                /*
                  no work scheduled for this tick
                 */
            } else if (this->gameTicksLoadBalancer == 25) {
                MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::setTreeSpreadInterval, DAT_LandscapeState::ptr)();
            } else if (this->gameTicksLoadBalancer == 30) {
                /*
                  no work scheduled for this tick
                 */
            } else if (this->gameTicksLoadBalancer == 31) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::createStatsPopUpEntities, this)();
            } else if (this->gameTicksLoadBalancer == 34) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::recountTotalTroopValue,
                    DAT_TroopValueState::ptr)();
            } else if (this->gameTicksLoadBalancer == 40) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::updateMoatCountdownTimers, DAT_TileMapState::ptr)();
            } else if (this->gameTicksLoadBalancer == 50) {
                /*
                  no work scheduled for this tick
                 */
            } else if ((this->gameTicksLoadBalancer >= 60) && (this->gameTicksLoadBalancer < 69)) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::recomputeTroopValuesForPlayer,
                    DAT_UnitsState::ptr)(this->gameTicksLoadBalancer - 60);
            } else if ((this->gameTicksLoadBalancer >= 71) && (this->gameTicksLoadBalancer < 79)) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateEnemyBuildings,
                    DAT_BuildingsState::ptr)(this->gameTicksLoadBalancer - 70);
            } else if (this->gameTicksLoadBalancer == 80) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::spawnMotherOrChild, this)();
            } else if (this->gameTicksLoadBalancer == 90) {
                /*
                  no work scheduled for this tick
                 */
            } else if (this->gameTicksLoadBalancer == 93) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::recomputeTotalTroopValueOfTroopsNearKeep,
                    DAT_TroopValueState::ptr)();
            } else if (this->gameTicksLoadBalancer == 95) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processPeasantsForBuildings, this)();
            } else if (this->gameTicksLoadBalancer == 99) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::showPopAndGoldPopup, this)();
            } else if (this->gameTicksLoadBalancer == 100) {
                /*
                  no work scheduled for this tick
                 */
            } else if ((this->gameTicksLoadBalancer >= 100) && (this->gameTicksLoadBalancer < 109)) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::recomputeTroopValuesForPlayer,
                    DAT_UnitsState::ptr)(this->gameTicksLoadBalancer - 100);
            } else if ((this->gameTicksLoadBalancer >= 110) && (this->gameTicksLoadBalancer < 150)) {
                MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateWildlifeGrid, DAT_WildlifeState::ptr)(
                    this->gameTicksLoadBalancer - 110);
            } else if (this->gameTicksLoadBalancer == 150) {
                MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateWildlife, DAT_WildlifeState::ptr)();
            } else if (this->gameTicksLoadBalancer == 151) {
                MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateSection1034Info, DAT_WildlifeState::ptr)();
            } else if (this->gameTicksLoadBalancer == 152) {
                MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateNofFpoints, DAT_WildlifeState::ptr)();
            } else if ((this->gameTicksLoadBalancer >= 160) && (this->gameTicksLoadBalancer < 169)) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::recomputeTroopValuesForPlayer,
                    DAT_UnitsState::ptr)(this->gameTicksLoadBalancer - 160);
            } else if (this->gameTicksLoadBalancer == 170) {
                /*
                  no work scheduled for this tick
                 */
            } else if (this->gameTicksLoadBalancer == 180) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::spawnChicken, this)();
            } else if (this->gameTicksLoadBalancer == 190) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::recountStablesAndHorses, this)();
            }
        }
        if (this->mapAndTime.skirmishNoRushTicks != 0) {
            this->mapAndTime.skirmishNoRushTicks = this->mapAndTime.skirmishNoRushTicks - 1;
        }
        if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
            && (DAT_GameSynchronyState::instance.currentGameMode
                != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
            MACRO_CALL_MEMBER(
                OpenSHC::Synchrony::GameSynchronyState_Func::checkGameSync, DAT_GameSynchronyState::ptr)();
        }
        this->gameTicksLoadBalancer = this->gameTicksLoadBalancer + 1;
        if (this->gameTicksLoadBalancer >= 200) {
            this->gameTicksLoadBalancer = 0;
            MACRO_CALL(OpenSHC::Audio::SFX_Func::UpdateUnitLossSpeechFeedback)();
        }
        if (((int)DAT_GameCore::instance.mapTimeInTicks % 200 == 0)
            && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
            && (DAT_GameSynchronyState::instance.currentGameMode
                != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
            /*
              check game sync
             */
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::recomputeHashesAndSendResync,
                DAT_GameSynchronyState::ptr)(0);
        }
        this->mapAndTime.totalGameTicksUnk = this->mapAndTime.totalGameTicksUnk + 1;
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
            return;
        }
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::updateDateAndTime, this)(
            this->gameTicksLoadBalancer == 0, this->gameTicksLoadBalancer);
        if (this->mapAndTime.weekChanged != 0) {
            DAT_GameSynchronyState::instance.finalResults.yearEnd = this->mapAndTime.year;
            DAT_GameSynchronyState::instance.finalResults.monthEnd = this->mapAndTime.month;
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::updateCrowding, this)();
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::updateTrader, this)();
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::updateTaxing, this)();
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::updateAleRate, this)();
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::recomputeAllFearFactors, DAT_BuildingsState::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::updateFearFactorProductivity, this)();
        }
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::updatePopularity, this)();
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processPeasantSpawnAndDespawnCycle, this)();
    }
}
}
