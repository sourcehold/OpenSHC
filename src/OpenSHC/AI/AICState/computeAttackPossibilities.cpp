#include "../AICState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2EC0
    void AICState::computeAttackPossibilities(int playerID)
    {
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            80400, '\0', DAT_TileMapState::instance.AIInfoLayer);
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAttackPrimeInfo, this)(
            playerID, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::recomputeTargetedBuildingTilesArray,
            DAT_TroopValueState::ptr)(playerID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::recomputeAttackInfo, DAT_TroopValueState::ptr)(
            playerID, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::computeSiegeSpotScores, DAT_TroopValueState::ptr)(
            DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID, playerID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::setScale3, DAT_TroopValueState::ptr)(1, playerID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::setTown2, DAT_TroopValueState::ptr)(1, playerID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::setGate2, DAT_TroopValueState::ptr)(1, playerID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::setWide3, DAT_TroopValueState::ptr)(1, playerID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::setMoat3, DAT_TroopValueState::ptr)(1, playerID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::calculateAttackVectorsToCampFireOfPlayer,
            DAT_GameState::ptr)(DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID);
    }

}
}
