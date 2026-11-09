#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Game {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004576E0
    BOOLEnum GameStateStructures::canNavigateFromKeepToKeep(int playerID1, int playerID2)
    {
        if (this->playerDataArray[playerID1].buildingEntryInfos[Player::Enums::BEIE_KEEP].id == 0) {
            return TRUE;
        }
        if (this->playerDataArray[playerID2].buildingEntryInfos[Player::Enums::BEIE_KEEP].id == 0) {
            return TRUE;
        }
        int const keepTile2
            = this->playerDataArray[playerID2].buildingEntryInfos[Player::Enums::BEIE_CAMPGROUND].tileEntry;
        int const keepTile1
            = this->playerDataArray[playerID1].buildingEntryInfos[Player::Enums::BEIE_CAMPGROUND].tileEntry;
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
                   DAT_TileMapState::instance.PathConnectionLayer[keepTile2],
                   DAT_TileMapState::instance.PathConnectionLayer[keepTile1], 0)
            != 0;
    }

}
}
