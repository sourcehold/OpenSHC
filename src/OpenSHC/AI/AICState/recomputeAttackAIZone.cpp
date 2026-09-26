#include "../AICState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/AttackInfoSubElement.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::AttackInfoSubElement;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE110
    void AICState::recomputeAttackAIZone()
    {
        for (int playerID = 1; playerID < 9; playerID++) {
            int fullID = DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID];
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].currentPlayerID_OR_attackedPlayerID_OR_one
                = playerID;
            if (fullID == -1
                && DAT_GameSynchronyState::instance.currentAIArray[playerID] == 0
                // fixme: this comparison looks dumb since fullID is already known to be the value, so a cmp eax eax
                // is generated, but we need it for the 100% match.
                && fullID == DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID]) {
                continue;
            }

            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                80400, '\0', DAT_TileMapState::instance.AIZoneLayer);
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::computeAIZoneLayer,
                DAT_PathFindingState::ptr)(playerID, 2, 1);
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkLayerAndAIPathCostLayer,
                DAT_PathFindingState::ptr)(252, 0, 1, playerID);
            DAT_GameState::instance.playerDataArray[playerID].unknownPathBorderDistanceRelated
                = DAT_PathFindingState::instance.distance;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].currentPlayerID_OR_attackedPlayerID_OR_one
                = 1;
        }
    }

}
}
