#include "../Navigation.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00530720
    void Navigation::UpdateLadderman_SetClimbData(int unitID)
    {
        DAT_TileMapState::instance.LogicLayer[DAT_UnitsState::instance.units[unitID].tile] |= LogicHelpers::L_CLIMBABLE;
        MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::createClimbData, DAT_PathFindingState::ptr)(
            1, 0, unitID, 0, 0);
        DAT_UnitsState::instance.units[unitID].laddermanIsInPosition = 1;
    }

}
}
