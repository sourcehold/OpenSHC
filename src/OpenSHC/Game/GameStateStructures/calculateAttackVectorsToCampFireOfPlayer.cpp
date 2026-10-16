#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Game {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004568B0
    void GameStateStructures::calculateAttackVectorsToCampFireOfPlayer(int playerID)
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculatePathKeepAndWallsGatesNotAllowed,
            DAT_PathFindingState::ptr)(DAT_GameState::instance.playerDataArray[playerID].campground.xEntry,
            DAT_GameState::instance.playerDataArray[playerID].campground.yEntry, -1, -1, 8000);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::computeAttackVectorsBasedOnXAndY,
            DAT_PathFindingState::ptr)(playerID);
    }

}
}
