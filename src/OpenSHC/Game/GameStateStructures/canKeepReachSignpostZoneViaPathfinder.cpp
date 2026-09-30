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
    // FUNCTION: STRONGHOLDCRUSADER 0x004578F0
    BOOLEnum GameStateStructures::canKeepReachSignpostZoneViaPathfinder(int playerID, int param_2, int signpostSlot)
    {
        ushort keepArea
            = DAT_TileMapState::instance.PathConnectionLayer[this->playerDataArray[playerID].campground.tileEntry];
        ushort signpostArea = DAT_TileMapState::instance.PathConnectionLayer[this->mapAndTime
                .signpostEntryData[(&DAT_TroopValueState::instance.attackInfo
                                         .unknownSignpostRelatedArray)[signpostSlot]]
                .tile];
        if (keepArea == 0) {
            return FALSE;
        }
        if (signpostArea == 0) {
            return FALSE;
        }
        return MACRO_CALL_MEMBER(
                   OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                   DAT_PathFindingState::ptr)(param_2, (short)keepArea, (short)signpostArea, 2)
            != 0;
    }
}
}
