#include "../GameStateStructures.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004574C0
    BOOLEnum GameStateStructures::checkKeepEnclosed(int playerID)
    {
        if (this->playerDataArray[playerID].campground.id == 0) {
            return FALSE;
        }
        int keepArea
            = (short)
                  DAT_TileMapState::instance.PathConnectionLayer[this->playerDataArray[playerID].campground.tileEntry];
        int zoneSize = DAT_PathFindingState::instance.zoneSizesArray[keepArea];
        if (zoneSize < 300) {
            return FALSE;
        }
        if (zoneSize > (DAT_PathFindingState::instance.sum * 3) / 4) {
            return FALSE;
        }
        switch (DAT_TileMapState::instance.mapSize) {
        case 160:
            if (zoneSize > 8000) {
                return FALSE;
            }
            break;
        case 200:
            if (zoneSize > 10000) {
                return FALSE;
            }
            break;
        case 300:
            if (zoneSize > 20000) {
                return FALSE;
            }
            break;
        case 400:
            if (zoneSize > 25000) {
                return FALSE;
            }
        }
        for (int otherPlayerID = 1; otherPlayerID < 9; otherPlayerID++) {
            if (DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                == DAT_GameState::instance.mapAndTime.playerTeams[otherPlayerID]) {
                continue;
            }
            int otherTile = this->playerDataArray[otherPlayerID].campground.tileEntry;
            if ((this->playerDataArray[otherPlayerID].campground.id != 0)
                && (DAT_GameState::instance.playerDataArray[otherPlayerID].lordKilledByPlayerID == 0)
                && ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[otherPlayerID] != -1)
                    || (DAT_GameSynchronyState::instance.currentAIArray[otherPlayerID] != 0))
                && (keepArea == (short)DAT_TileMapState::instance.PathConnectionLayer[otherTile])) {
                return FALSE;
            }
        }
        return TRUE;
    }
}
}
