#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051BF20
        BOOLEnum TroopValueState::shouldLightPitchBasedOnTroopValue(int tile, int playerID, int param_3)
        {
            int iVar1;
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::computeTotalUnitsWithinDistance,
                DAT_PathFindingState::ptr)(playerID, 1, 1, tile, 10);
            iVar1 = DAT_PathFindingState::instance.ALGO_TotalTroopValue;
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::computeTotalUnitsWithinDistance,
                DAT_PathFindingState::ptr)(playerID, 0, 1, tile, 6);
            return (uint)(iVar1 * 2 < DAT_PathFindingState::instance.ALGO_TotalTroopValue);
        }

    }
}
}
