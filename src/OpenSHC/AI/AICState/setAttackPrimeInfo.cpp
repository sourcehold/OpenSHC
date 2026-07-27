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
        int _zone = (int)(char)DAT_TileMapState::instance.AIZoneLayer[_tile];
        int _pathCon = (int)(short)DAT_TileMapState::instance.PathConnectionLayer[_tile];
        int _zoneSize = DAT_PathFindingState::instance.zoneSizesArray[_pathCon];
        DAT_TroopValueState::instance.attackInfo.startCon = _pathCon;
        int _attackedTile = DAT_GameState::instance.playerDataArray[attackedPlayerID].campground.tileEntry;
        DAT_TroopValueState::instance.attackInfo.startZone = _zone;
        DAT_TroopValueState::instance.attackInfo.zoneSize = _zoneSize;
        DAT_TroopValueState::instance.attackInfo.unknownOne_0x20f90 = 1;
        DAT_TroopValueState::instance.attackInfo.keepCon
            = (int)(short)DAT_TileMapState::instance.PathConnectionLayer[_attackedTile];
    }
}
}
