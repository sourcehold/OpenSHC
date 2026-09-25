#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00530760
    void Units::DetachLadderman(int unitID)
    {
        int tile = DAT_UnitsState::instance.units[unitID].tile;
        DAT_TileMapState::instance.LogicLayer[tile] &= ~OpenSHC::Map::LogicHelpers::L_CLIMBABLE;
        DAT_UnitsState::instance.units[unitID].wallDataID = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
            DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[unitID].y, tile);
        DAT_UnitsState::instance.units[unitID].laddermanIsInPosition = 0;
    }

}
}
