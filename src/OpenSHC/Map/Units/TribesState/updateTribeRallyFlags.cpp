#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00523F70
        undefined4 TribesState::updateTribeRallyFlags(int param_1)
        {
            short* psVar1;
            int iVar2;
            undefined4 uVar3;
            int unitSelectionIndex;
            undefined4 local_4;
            short _isRallying;
            psVar1 = &this->tribes[param_1].size;
            unitSelectionIndex = 0;
            local_4 = 0;
            uVar3 = 0;
            if (0 < *psVar1) {
                do {
                    iVar2 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        param_1, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if (DAT_UnitsState::instance.units[iVar2].logicalState == Map::Units::ULS_NORMAL
                        && DAT_UnitsState::instance.units[iVar2].dying == 0
                        && (_isRallying = DAT_UnitsState::instance.units[iVar2].goToRallyPoint,
                            DAT_UnitsState::instance.units[iVar2].rallyRelatedFlag = 0,
                            _isRallying != 0
                                || (DAT_UnitsState::instance.units[iVar2].isSelectable_OR_matchTime == 0))) {
                        local_4 = 1;
                        DAT_UnitsState::instance.units[iVar2].rallyRelatedFlag = 1;
                    }
                    uVar3 = local_4;
                } while (unitSelectionIndex < *psVar1);
            }
            return (undefined4)(uVar3);
        }

    }
}
}
