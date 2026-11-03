#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004568B0
    void GameStateStructures::calculateAttackVectorsToCampFireOfPlayer(int playerID)
    {
        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::calculatePathKeepAndWallsGatesNotAllowed,
            DAT_PathFindingState::ptr)(
            DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_CAMPGROUND].xEntry,
            DAT_GameState::instance.playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_CAMPGROUND].yEntry,
            -1, -1, 8000);
        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::computeAttackVectorsBasedOnXAndY,
            DAT_PathFindingState::ptr)(playerID);
    }

}
}
