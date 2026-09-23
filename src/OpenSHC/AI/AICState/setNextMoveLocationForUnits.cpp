#include "../AICState.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE3B0
    void AICState::setNextMoveLocationForUnits(int playerID)
    {
        int organismID
            = (short)DAT_TileMapState::instance.OrganismLayer
                  [DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY]
                          .addXgetTile
                      + DAT_GameState::instance.playerDataArray[playerID].shortestDistanceX];
        if (organismID != 0) {
            MACRO_CALL_MEMBER(Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(organismID);
        }

        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
            DAT_PathFindingState::ptr)(DAT_GameState::instance.playerDataArray[playerID].shortestDistanceX,
            DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY, -1, -1, 4000, FALSE);
        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::setDestinationPairsBasedOnPreviousSearch,
            DAT_PathFindingState::ptr)(
            playerID - 1, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID);
    }

}
}
