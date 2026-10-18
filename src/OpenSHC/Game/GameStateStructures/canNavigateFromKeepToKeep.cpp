#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Game {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004576E0
    BOOLEnum GameStateStructures::canNavigateFromKeepToKeep(int playerID1, int playerID2)
    {
        if (this->playerDataArray[playerID1].keep.id == 0) {
            return TRUE;
        }
        if (this->playerDataArray[playerID2].keep.id == 0) {
            return TRUE;
        }
        int keepTile2 = this->playerDataArray[playerID2].campground.tileEntry;
        int keepTile1 = this->playerDataArray[playerID1].campground.tileEntry;
        if (DAT_TileMapState::instance.PathConnectionLayer[keepTile2] == 0) {
            return FALSE;
        }
        if (DAT_TileMapState::instance.PathConnectionLayer[keepTile1] == 0) {
            return FALSE;
        }
        if (DAT_TileMapState::instance.PathConnectionLayer[keepTile1]
            == DAT_TileMapState::instance.PathConnectionLayer[keepTile2]) {
            return TRUE;
        }
        return MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                   DAT_PathFindingState::ptr)(playerID1,
                   (short)DAT_TileMapState::instance.PathConnectionLayer[keepTile2],
                   (short)DAT_TileMapState::instance.PathConnectionLayer[keepTile1], 0)
            != 0;
    }

}
}
