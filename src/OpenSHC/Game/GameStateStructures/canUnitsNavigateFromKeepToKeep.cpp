#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00457770
    BOOLEnum GameStateStructures::canUnitsNavigateFromKeepToKeep(int playerID, int targetPlayerID)
    {
        if (this->playerDataArray[playerID].keep.id == 0) {
            return TRUE;
        }
        if (this->playerDataArray[targetPlayerID].keep.id == 0) {
            return TRUE;
        }
        ushort targetArea = DAT_TileMapState::instance
                                .PathConnectionLayer[this->playerDataArray[targetPlayerID].campground.tileEntry];
        ushort area
            = DAT_TileMapState::instance.PathConnectionLayer[this->playerDataArray[playerID].campground.tileEntry];
        if (targetArea == 0) {
            return FALSE;
        }
        if (area == 0) {
            return FALSE;
        }
        if (area == targetArea) {
            return TRUE;
        }
        return MACRO_CALL_MEMBER(
                   OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                   DAT_PathFindingState::ptr)(playerID, (short)targetArea, (short)area, 2)
            != 0;
    }
}
}
