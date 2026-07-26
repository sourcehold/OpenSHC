#include "OpenSHC/AI/AICState.func.hpp"
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

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE3B0
    void AICState ::setNextMoveLocationForUnits(int playerID)

    {

        if ((short)DAT_TileMapState::instance.OrganismLayer
                [DAT_ViewportRenderState::instance
                        .translationMatrix[DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY]
                        .addXgetTile
                    + DAT_GameState::instance.playerDataArray[playerID].shortestDistanceX]
            != 0) {

            MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(
                (int)(short)DAT_TileMapState::instance.OrganismLayer
                    [DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY]
                            .addXgetTile
                        + DAT_GameState::instance.playerDataArray[playerID].shortestDistanceX]);
        }

        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
            DAT_PathFindingState::ptr)(DAT_GameState::instance.playerDataArray[playerID].shortestDistanceX,
            (uint)((int)(DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY)), -1, -1, 4000, FALSE);

        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::setDestinationPairsBasedOnPreviousSearch,
            DAT_PathFindingState::ptr)(
            playerID + -1, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID);

        return;
    }

}
}
