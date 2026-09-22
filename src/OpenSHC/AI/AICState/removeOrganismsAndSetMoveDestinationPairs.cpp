#include "../AICState.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE430
    void AICState::removeOrganismsAndSetMoveDestinationPairs(int playerID)
    {
        // Clear a tree standing on the target tile
        int organismID = (short)DAT_TileMapState::instance.OrganismLayer
            [DAT_ViewportRenderState::instance
                    .translationMatrix[DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY]
                    .addXgetTile
                + DAT_GameState::instance.playerDataArray[playerID].shortestDistanceX];
        if (organismID != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(organismID);
        }

        // Hardcoded exception: the Sultan keeps a smaller distance than all other AIs
        int extraDistance = DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_SULTAN ? 8 : 20;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
            DAT_PathFindingState::ptr)(DAT_GameState::instance.playerDataArray[playerID].shortestDistanceX,
            DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY, -1, -1, 10000, FALSE);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::setMoveDestinationPairs,
            DAT_PathFindingState::ptr)(playerID - 1, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID,
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].someMinimumDistance + extraDistance);
    }

}
}
