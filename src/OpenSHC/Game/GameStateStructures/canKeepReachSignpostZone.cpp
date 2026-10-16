#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00457870
    BOOLEnum GameStateStructures::canKeepReachSignpostZone(int playerID, int param_2, int signpostSlot)
    {
        int keepTile = this->playerDataArray[playerID].campground.tileEntry;
        int signpostTile = this->mapAndTime
                               .signpostEntryData[(
                                   &DAT_TroopValueState::instance.attackInfo.unknownSignpostRelatedArray)[signpostSlot]]
                               .tile;
        if (DAT_TileMapState::instance.PathConnectionLayer[keepTile] == 0) {
            return FALSE;
        }
        if (DAT_TileMapState::instance.PathConnectionLayer[signpostTile] == 0) {
            return FALSE;
        }
        if (DAT_TileMapState::instance.PathConnectionLayer[signpostTile]
            == DAT_TileMapState::instance.PathConnectionLayer[keepTile]) {
            return TRUE;
        }
        return MACRO_CALL_MEMBER(
                   OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                   DAT_PathFindingState::ptr)(param_2, (short)DAT_TileMapState::instance.PathConnectionLayer[keepTile],
                   (short)DAT_TileMapState::instance.PathConnectionLayer[signpostTile], 0)
            != 0;
    }
}
}
