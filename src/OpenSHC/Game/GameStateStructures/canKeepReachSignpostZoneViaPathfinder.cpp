#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Game {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004578F0
    BOOLEnum GameStateStructures::canKeepReachSignpostZoneViaPathfinder(int playerID, int param_2, int signpostSlot)
    {
        int const keepTile = this->playerDataArray[playerID].campground.tileEntry;
        int signpostTile
            = this->mapAndTime
                  .signpostEntryData[DAT_TroopValueState::instance.attackInfo.unknownSignpostRelatedArray[signpostSlot]]
                  .tile;
        if (DAT_TileMapState::instance.PathConnectionLayer[keepTile] == 0) {
            return FALSE;
        }
        if (DAT_TileMapState::instance.PathConnectionLayer[signpostTile] == 0) {
            return FALSE;
        }
        return MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                   DAT_PathFindingState::ptr)(param_2, (short)DAT_TileMapState::instance.PathConnectionLayer[keepTile],
                   (short)DAT_TileMapState::instance.PathConnectionLayer[signpostTile], 2)
            != 0;
    }

}
}
