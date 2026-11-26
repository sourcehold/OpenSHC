#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AFF0
        int TroopValueState::claimArcherAttackPoint(int param_1)
        {
            int const unitID = DAT_TribesState::instance.tribes[param_1].selectionTargetUnitID;
            int pointIndex = MACRO_CALL_MEMBER(
                Map::Units::TribesState_Func::tribeHasActiveLaddermanUnit, DAT_TribesState::ptr)(param_1);
            if (!pointIndex) {
                pointIndex = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findArcherRelatedAttackInfoIndex,
                    DAT_PathFindingState::ptr)(
                    200, DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, param_1);
                if (!pointIndex) {
                    return 0;
                }
                short const oldPointIndex = DAT_TribesState::instance.tribes[param_1].archerRelated;
                int const tribeUID = DAT_TribesState::instance.tribes[param_1].uid;
                DAT_TribesState::instance.tribes[param_1].archerRelated2 = oldPointIndex;
                DAT_TroopValueState::instance.attackInfo.archerPointArray[oldPointIndex].tribeID = 0;
                DAT_TroopValueState::instance.attackInfo.archerPointArray[oldPointIndex].tribeUID = 0;
                int const pointY = DAT_TroopValueState::instance.attackInfo.archerPointArray[pointIndex].y;
                DAT_TroopValueState::instance.attackInfo.archerPointArray[pointIndex].tribeUID = tribeUID;
                int const pointX = DAT_TroopValueState::instance.attackInfo.archerPointArray[pointIndex].x;
                DAT_TribesState::instance.tribes[param_1].archerRelated = pointIndex;
                DAT_TroopValueState::instance.attackInfo.archerPointArray[pointIndex].tribeID = param_1;
                DAT_TroopValueState::instance.attackInfo.archerPointArray[pointIndex].claimCooldown = 3;
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                    param_1, pointX, pointY, 0, 0, Map::Units::Instructions::UMSE_0);
                return pointIndex;
            }
            return 0;
        }

    }
}
}
