#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D510
        void TroopValueState::moveTowardsParticularUnits(int param_1)
        {
            int const selectedUnitID = DAT_TribesState::instance.tribes[param_1].selectionTargetUnitID;
            int targetUnitID = MACRO_CALL_MEMBER(
                Map::Navigation::PathFindingState_Func::findDistanceOrThreatLevelToUnitUnk, DAT_PathFindingState::ptr)(
                DAT_TribesState::instance.tribes[param_1].owner, DAT_UnitsState::instance.units[selectedUnitID].x,
                DAT_UnitsState::instance.units[selectedUnitID].y, 80);
            if (!targetUnitID) {
                targetUnitID
                    = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findDistanceOrThreatLevelToUnitUnk,
                        DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[param_1].owner,
                        DAT_UnitsState::instance.units[selectedUnitID].x,
                        DAT_UnitsState::instance.units[selectedUnitID].y, 200);
                if (!targetUnitID) {
                    return;
                }
            }
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                param_1, Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk, 0, 0, 0);
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(param_1,
                DAT_UnitsState::instance.units[targetUnitID].x, DAT_UnitsState::instance.units[targetUnitID].y, 0, 0,
                Map::Units::Instructions::UMSE_0);
        }

    }
}
}
