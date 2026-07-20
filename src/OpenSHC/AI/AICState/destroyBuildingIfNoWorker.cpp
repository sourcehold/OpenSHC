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
        short _value = DAT_BuildingsState::instance.buildings[buildingID].unknownTickRelatedValue;
        int _owner = (int)DAT_BuildingsState::instance.buildings[buildingID].owner;
        if ((((0 < _value) && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_owner] == -1))
                && (DAT_GameSynchronyState::instance.currentAIArray[_owner] != 0))
            && (DAT_GameSynchronyState::instance.DAT_CurrentGameMode != Game::GM_SOLITARY)) {
            if (DAT_BuildingsState::instance.buildings[buildingID].workers[0] == 0) {
                if (0x13 < _value) {
                    MACRO_CALL_MEMBER(AIVState_Func::set0x13ValueTo10InHeatMap, DAT_AIVState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                        (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y);
                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                        DAT_BuildingsState::ptr)(buildingID, _owner, 0x32);
                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                        buildingID);
                    return 1;
                }
            } else if (DAT_GameState::instance.mapAndTime.monthTicks == _owner) {
                DAT_BuildingsState::instance.buildings[buildingID].unknownTickRelatedValue = _value + -1;
            }
        }
        return 0;
    }
}
}
