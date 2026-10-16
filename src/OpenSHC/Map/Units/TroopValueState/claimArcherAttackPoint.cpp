#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

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

        using Map::Units::Instructions::UnitMatchSpeedEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AFF0
        int TroopValueState::claimArcherAttackPoint(int param_1)
        {
            int iVar3;
            short sVar1 = DAT_TribesState::instance.tribes[param_1].selectionTargetUnitID;
            iVar3 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::tribeHasActiveLaddermanUnit, DAT_TribesState::ptr)(
                param_1);
            if (!iVar3) {
                iVar3 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findArcherRelatedAttackInfoIndex,
                    DAT_PathFindingState::ptr)(200, (uint)(DAT_UnitsState::instance.units[sVar1].x),
                    (uint)(DAT_UnitsState::instance.units[sVar1].y), param_1);
                if (iVar3) {
                    sVar1 = DAT_TribesState::instance.tribes[param_1].archerRelated;
                    int iVar2 = DAT_TribesState::instance.tribes[param_1].uid;
                    DAT_TribesState::instance.tribes[param_1].archerRelated2 = sVar1;
                    DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[sVar1 * 2 + 0x3ea].buildingID = 0;
                    DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[sVar1 * 2 + 0x3ea].unitID = 0;
                    uint y1 = DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[iVar3 * 2 + 0x3e9].unitID;
                    DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[iVar3 * 2 + 0x3ea].unitID = iVar2;
                    uint x1 = DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[iVar3 * 2 + 0x3e9].buildingID;
                    DAT_TribesState::instance.tribes[param_1].archerRelated = (short)iVar3;
                    DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[iVar3 * 2 + 0x3ea].buildingID = param_1;
                    DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[iVar3 * 2 + 0x3eb].tile = 3;
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                        param_1, x1, y1, 0, 0, Map::Units::Instructions::UMSE_0);
                    return iVar3;
                }
            }
            return 0;
        }

    }
}
}
