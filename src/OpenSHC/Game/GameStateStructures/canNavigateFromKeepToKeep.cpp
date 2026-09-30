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
    // FUNCTION: STRONGHOLDCRUSADER 0x004576E0
    BOOLEnum GameStateStructures::canNavigateFromKeepToKeep(int playerID1, int playerID2)
    {
        if (this->playerDataArray[playerID1].keep.id == 0) {
            return TRUE;
        }
        if (this->playerDataArray[playerID2].keep.id == 0) {
            return TRUE;
        }
        ushort area2
            = DAT_TileMapState::instance.PathConnectionLayer[this->playerDataArray[playerID2].campground.tileEntry];
        ushort area1
            = DAT_TileMapState::instance.PathConnectionLayer[this->playerDataArray[playerID1].campground.tileEntry];
        if (area2 == 0) {
            return FALSE;
        }
        if (area1 == 0) {
            return FALSE;
        }
        if (area1 == area2) {
            return TRUE;
        }
        return MACRO_CALL_MEMBER(
                   OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                   DAT_PathFindingState::ptr)(playerID1, (short)area2, (short)area1, 0)
            != 0;
    }
}
}
