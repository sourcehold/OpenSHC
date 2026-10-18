#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519850
        void TroopValueState::initializeAttackZoneSearch(int param_1)
        {
            DAT_TroopValueState::instance.attackInfo.biggestZone = 0;
            int _tile
                = DAT_GameState::instance.mapAndTime
                      .signpostEntryData[DAT_TroopValueState::instance.attackInfo.unknownSignpostRelatedArray[param_1]]
                      .tile;
            DAT_TroopValueState::instance.attackInfo.startCon
                = (int)(short)DAT_TileMapState::instance.PathConnectionLayer[_tile];
            DAT_TroopValueState::instance.attackInfo.startZone
                = (int)(char)DAT_TileMapState::instance.AIZoneLayer[_tile];
            DAT_TroopValueState::instance.attackInfo.zoneSize
                = DAT_PathFindingState::instance
                      .zoneSizesArray[(short)DAT_TileMapState::instance.PathConnectionLayer[_tile]];
            DAT_TroopValueState::instance.attackInfo.unknownOne_0x20f90 = 1;
            DAT_TroopValueState::instance.attackInfo.keepCon
                = (int)(short)DAT_TileMapState::instance.PathConnectionLayer[DAT_GameState::instance
                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .campground.tileEntry];
        }

    }
}
}
