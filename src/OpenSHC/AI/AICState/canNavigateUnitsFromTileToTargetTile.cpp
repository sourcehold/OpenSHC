#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD250
    BOOLEnum AICState::canNavigateUnitsFromTileToTargetTile(int tribeID, int tile)
    {
        int iVar1 = MACRO_CALL_MEMBER(
            Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
            DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[tribeID].owner,
            (int)(short)DAT_TileMapState::instance.PathConnectionLayer
                [DAT_UnitsState::instance.units[DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID].tile],
            (int)(short)DAT_TileMapState::instance.PathConnectionLayer[tile], 0);
        return (uint)(iVar1 != 0);
    }
}
}
