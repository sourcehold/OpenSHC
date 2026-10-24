#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00525210
        BOOLEnum TribesState::isTribeFreeOfTunnelingUnits(int param_1, int param_2)
        {
            int iVar2;
            int iVar1 = (int)this->tribes[param_1].size;
            int unitSelectionIndex = 0;
            if (0 < iVar1) {
                do {
                    iVar2 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        param_1, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if (DAT_UnitsState::instance.units[iVar2].logicalState == Map::Units::ULS_NORMAL
                        && DAT_UnitsState::instance.units[iVar2].dying == 0
                        && DAT_UnitsState::instance.units[iVar2].tunnelerFinishedDigging == 2) {
                        return FALSE;
                    }
                } while (unitSelectionIndex < iVar1);
            }
            return TRUE;
        }

    }
}
}
