#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

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
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0045B3E0
    void GameStateStructures::initializeGameStateAfterMapLoad()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
        }
        DAT_BuildingsState::instance.unknownCountdown01 = 2000;
        this->gameTicksLoadBalancer = 0;
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setSignpostDataForBuildings, DAT_BuildingsState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::clearDataAndSignpostDataIfNecessary, this)();
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeSignPostEntryData, this)();
        this->mapAndTime.multiplayerUnitSameTileLinkageTimeWindow = 0;
        if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
            MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::importTradingCosts, DAT_MapPropertiesState::ptr)();
        }
        MACRO_CALL_MEMBER(
            OpenSHC::Map::MapPropertiesState_Func::commitBuildingAvailability, DAT_MapPropertiesState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::updateCrowding, this)();
    }
}
}
