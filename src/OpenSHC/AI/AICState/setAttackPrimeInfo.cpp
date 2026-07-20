#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDFD0
    void AICState::setAttackPrimeInfo(int playerID, int attackedPlayerID)
    {
        int _tile = DAT_GameState::instance.playerDataArray[playerID].shortestDistanceTile;
        DAT_TroopValueState::instance.attackInfo.startCon
            = (int)(short)DAT_TileMapState::instance.PathConnectionLayer[_tile];
        DAT_TroopValueState::instance.attackInfo.startZone = (int)(char)DAT_TileMapState::instance.AIZoneLayer[_tile];
        DAT_TroopValueState::instance.attackInfo.zoneSize
            = DAT_PathFindingState::instance
                  .zoneSizesArray[(short)DAT_TileMapState::instance.PathConnectionLayer[_tile]];
        DAT_TroopValueState::instance.attackInfo.unknownOne_0x20f90 = 1;
        DAT_TroopValueState::instance.attackInfo.keepCon
            = (int)(short)DAT_TileMapState::instance
                  .PathConnectionLayer[DAT_GameState::instance.playerDataArray[attackedPlayerID].campground.tileEntry];
    }
}
}
