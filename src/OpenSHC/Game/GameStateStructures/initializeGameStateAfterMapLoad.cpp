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

    // FUNCTION: STRONGHOLDCRUSADER 0x0045B3E0
    void GameStateStructures::initializeGameStateAfterMapLoad()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == GM_SOLITARY) {
            MACRO_CALL_MEMBER(GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
        }
        DAT_BuildingsState::instance.unknownCountdown01 = 2000;
        this->gameTicksLoadBalancer = 0;
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::setSignpostDataForBuildings, DAT_BuildingsState::ptr)();
        MACRO_CALL_MEMBER(GameStateStructures_Func::clearDataAndSignpostDataIfNecessary, this)();
        MACRO_CALL_MEMBER(GameStateStructures_Func::computeSignPostEntryData, this)();
        this->mapAndTime.multiplayerUnitSameTileLinkageTimeWindow = 0;
        if (DAT_GameCore::instance.gameMode_2 != GM_SKIRMISH_AND_MULTIPLAYER) {
            MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::importTradingCosts, DAT_MapPropertiesState::ptr)();
        }
        MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::commitBuildingAvailability, DAT_MapPropertiesState::ptr)();
        MACRO_CALL_MEMBER(GameStateStructures_Func::updateCrowding, this)();
    }

}
}
