#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Game {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00457770
    BOOLEnum GameStateStructures::canUnitsNavigateFromKeepToKeep(int playerID, int targetPlayerID)
    {
        if (this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_KEEP].id == 0) {
            return TRUE;
        }
        if (this->playerDataArray[targetPlayerID].buildingEntryInfos[Player::Enums::BEIE_KEEP].id == 0) {
            return TRUE;
        }
        int const targetKeepTile
            = this->playerDataArray[targetPlayerID].buildingEntryInfos[Player::Enums::BEIE_CAMPGROUND].tileEntry;
        int const keepTile
            = this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_CAMPGROUND].tileEntry;
        if (DAT_TileMapState::instance.PathConnectionLayer[targetKeepTile] == 0) {
            return FALSE;
        }
        if (DAT_TileMapState::instance.PathConnectionLayer[keepTile] == 0) {
            return FALSE;
        }
        if (DAT_TileMapState::instance.PathConnectionLayer[keepTile]
            == DAT_TileMapState::instance.PathConnectionLayer[targetKeepTile]) {
            return TRUE;
        }
        return MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                   DAT_PathFindingState::ptr)(playerID,
                   DAT_TileMapState::instance.PathConnectionLayer[targetKeepTile],
                   DAT_TileMapState::instance.PathConnectionLayer[keepTile], 2)
            != 0;
    }

}
}
