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

        using Map::Units::UnitInstructionType;
        using Map::Units::Instructions::UnitMatchSpeedEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D510
        void TroopValueState::moveTowardsParticularUnits(int param_1)
        {
            int const _unitID = DAT_TribesState::instance.tribes[param_1].selectionTargetUnitID;
            int _targetUnitID = MACRO_CALL_MEMBER(
                Map::Navigation::PathFindingState_Func::findDistanceOrThreatLevelToUnitUnk, DAT_PathFindingState::ptr)(
                DAT_TribesState::instance.tribes[param_1].owner, (int)(DAT_UnitsState::instance.units[_unitID].x),
                (int)(DAT_UnitsState::instance.units[_unitID].y), 0x50);
            if ((!_targetUnitID)
                && (_targetUnitID
                    = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findDistanceOrThreatLevelToUnitUnk,
                        DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[param_1].owner,
                        (int)(DAT_UnitsState::instance.units[_unitID].x),
                        (int)(DAT_UnitsState::instance.units[_unitID].y), 200),
                    _targetUnitID == 0)) {
                return;
            }
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                param_1, Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk, 0, 0, 0);
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(param_1,
                (uint)(DAT_UnitsState::instance.units[_targetUnitID].x),
                (uint)(DAT_UnitsState::instance.units[_targetUnitID].y), 0, 0, Map::Units::Instructions::UMSE_0);
        }

    }
}
}
