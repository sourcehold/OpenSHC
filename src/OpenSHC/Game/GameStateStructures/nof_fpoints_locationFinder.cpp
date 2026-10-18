#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00456870
    void GameStateStructures::nof_fpoints_locationFinder()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode != GM_SOLITARY) {
            return;
        }
        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
            DAT_PathFindingState::ptr)(DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[0][0],
            DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[0][1], -1, -1, 1000000, 0);
        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::searchCertainPathLayer, DAT_PathFindingState::ptr)();
    }

}
}
