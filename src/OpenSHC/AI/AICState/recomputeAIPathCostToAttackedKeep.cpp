#include "../AICState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE040
    void AICState::recomputeAIPathCostToAttackedKeep(int playerID, int useBorderDistance)
    {
        int attackedPlayerID = DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID;
        int keepArea = (short)DAT_TileMapState::instance
                           .PathConnectionLayer[DAT_GameState::instance.playerDataArray[playerID].campground.tileEntry];

        int borderDistance;
        if (DAT_GameState::instance.playerDataArray[attackedPlayerID].unknownPathBorderDistanceRelated > 120) {
            borderDistance = 98;
        }
        else {
            borderDistance
                = DAT_GameState::instance.playerDataArray[attackedPlayerID].unknownPathBorderDistanceRelated > 90 ? 70
                                                                                                                   : 50;
        }
        if (useBorderDistance == 0) {
            borderDistance = 0;
        }

        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].currentPlayerID_OR_attackedPlayerID_OR_one
            = attackedPlayerID;

        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            80400, '\0', DAT_TileMapState::instance.AIZoneLayer);

        if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::canNavigateFromKeepToKeep, DAT_GameState::ptr)(
                playerID, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID)
            != FALSE) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::computeAIZoneLayer,
                DAT_PathFindingState::ptr)(DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID, 1, 1);
        }
        else {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::computeAIZoneLayer,
                DAT_PathFindingState::ptr)(DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID, 0, 1);
        }

        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkLayerAndAIPathCostLayer,
            DAT_PathFindingState::ptr)(110, borderDistance, keepArea, playerID);
    }

}
}
