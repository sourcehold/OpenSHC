#include "OpenSHC/AI/AICState.func.hpp"
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

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE430
    void AICState ::removeOrganismsAndSetMoveDestinationPairs(int playerID)

    {

        AITypeInt _aiType;

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

        _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;

        /*
            bug: special hardcoded exception for AI type 8 */

        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
            DAT_PathFindingState::ptr)(DAT_GameState::instance.playerDataArray[playerID].shortestDistanceX,
            (uint)((int)(DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY)), -1, -1, 10000, FALSE);

        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::setMoveDestinationPairs,
            DAT_PathFindingState::ptr)(playerID + -1,
            DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID,
            (int)((int)(*(int*)(DAT_TroopValueState::instance.attackInfo.scaleValuesArray + playerID * 0x177bc + -0x1c)
                + (-(uint)(_aiType != OpenSHC::AI::AIT_SULTAN) & 0xc) + 8)));

        return;
    }

}
}
