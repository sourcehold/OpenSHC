#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitInstructionType;
        using Map::Units::Instructions::UnitMatchSpeedEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D450
        undefined4 TroopValueState::moveTribeToNearbyGatehouse(int param_1)
        {
            short sVar1;
            int iVar2;
            sVar1 = DAT_TribesState::instance.tribes[param_1].selectionTargetUnitID;
            iVar2 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::getGatehouseNearSomethingUnk,
                DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[param_1].owner,
                (int)((int)(DAT_UnitsState::instance.units[sVar1].x)),
                (int)((int)(DAT_UnitsState::instance.units[sVar1].y)), (int)((int)(80)));
            if (!iVar2) {
                iVar2 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::getGatehouseNearSomethingUnk,
                    DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[param_1].owner,
                    (int)((int)(DAT_UnitsState::instance.units[sVar1].x)),
                    (int)((int)(DAT_UnitsState::instance.units[sVar1].y)), 200);
                if (!iVar2) {
                    return (undefined4)(0);
                }
            }
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                param_1, Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk, 0, 0, 0);
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                param_1, (uint)((int)((int)DAT_BuildingsState::instance.buildings[iVar2].someX)),
                (uint)((int)((int)DAT_BuildingsState::instance.buildings[iVar2].someY)), 0, 0,
                Map::Units::Instructions::UMSE_0);
            return (undefined4)(1);
        }

    }
}
}
