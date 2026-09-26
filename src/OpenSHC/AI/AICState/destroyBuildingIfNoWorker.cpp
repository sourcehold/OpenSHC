#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB940
    undefined4 AICState::destroyBuildingIfNoWorker(int buildingID)
    {
        short countdown = DAT_BuildingsState::instance.buildings[buildingID].unknownTickRelatedValue;
        int owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
        if (countdown <= 0)
            return 0;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[owner] != -1)
            return 0;
        if (DAT_GameSynchronyState::instance.currentAIArray[owner] == 0)
            return 0;
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)
            return 0;

        if (DAT_BuildingsState::instance.buildings[buildingID].workers[0] != 0) {
            if (DAT_GameState::instance.mapAndTime.monthTicks == owner)
                DAT_BuildingsState::instance.buildings[buildingID].unknownTickRelatedValue = countdown - 1;
            return 0;
        }
        if (countdown < 20)
            return 0;

        MACRO_CALL_MEMBER(AIVState_Func::resetCountdownInHeatMap, DAT_AIVState::ptr)(
            DAT_BuildingsState::instance.buildings[buildingID].x, DAT_BuildingsState::instance.buildings[buildingID].y);
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
            DAT_BuildingsState::ptr)(buildingID, owner, 50);
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(buildingID);
        return 1;
    }
}
}
