#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace AI {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE1A0
    void AICState ::recomputeAIZonerLayer()

    {

        DAT_TroopValueState::instance.attackInfo.playerInfo[0].currentPlayerID_OR_attackedPlayerID_OR_one = 1;

        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            80400, '\0', (void*)((int)(DAT_TileMapState::instance.AIZoneLayer)));

        MACRO_CALL_MEMBER(
            OpenSHC::Map::Navigation::PathFindingState_Func::computeAIZoneLayer, DAT_PathFindingState::ptr)(1, 2);

        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkLayerAndAIPathCostLayer,
            DAT_PathFindingState::ptr)(252, 0, 1, 1);

        DAT_GameState::instance.playerDataArray[1].unknownPathBorderDistanceRelated
            = DAT_PathFindingState::instance.distance;

        DAT_TroopValueState::instance.attackInfo.playerInfo[0].currentPlayerID_OR_attackedPlayerID_OR_one = 1;

        return;
    }

}
}
