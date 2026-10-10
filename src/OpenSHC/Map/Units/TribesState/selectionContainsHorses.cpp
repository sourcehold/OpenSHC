#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00524230
        BOOLEnum TribesState::selectionContainsHorses(int param_1)
        {
            UnitTypeShort UVar1;
            int iVar2;
            int iVar3;
            int unitSelectionIndex;
            iVar3 = (int)this->tribes[param_1].size;
            unitSelectionIndex = 0;
            if (0 < iVar3) {
                do {
                    iVar2 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        param_1, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if (DAT_UnitsState::instance.units[iVar2].logicalState == Map::Units::ULS_NORMAL
                        && DAT_UnitsState::instance.units[iVar2].dying == 0
                        && (UVar1 = DAT_UnitsState::instance.units[iVar2].unitType,
                            UVar1 == Map::Units::UT_A_HARCHER || (UVar1 == Map::Units::UT_E_KNIGHT))) {
                        return TRUE;
                    }
                } while (unitSelectionIndex < iVar3);
            }
            return FALSE;
        }

    }
}
}
