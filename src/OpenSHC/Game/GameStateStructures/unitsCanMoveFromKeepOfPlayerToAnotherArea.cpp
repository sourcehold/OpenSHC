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
    // FUNCTION: STRONGHOLDCRUSADER 0x00457800
    BOOLEnum GameStateStructures::unitsCanMoveFromKeepOfPlayerToAnotherArea(int playerID)
    {
        ushort keepArea
            = DAT_TileMapState::instance.PathConnectionLayer[this->playerDataArray[playerID].campground.tileEntry];
        ushort signpostArea
            = DAT_TileMapState::instance.PathConnectionLayer[this->mapAndTime.signpostEntryData[0].tile];
        if (keepArea == 0) {
            return FALSE;
        }
        if (signpostArea == 0) {
            return FALSE;
        }
        if (signpostArea == keepArea) {
            return TRUE;
        }
        return MACRO_CALL_MEMBER(
                   OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                   DAT_PathFindingState::ptr)(playerID, (short)keepArea, (short)signpostArea, 0)
            != 0;
    }
}
}
