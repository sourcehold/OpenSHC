#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005253F0
        BOOLEnum TribesState::allUnitsReachedTheirDestination(int tribeID)
        {
            int unitID;
            BOOLEnum BVar1;
            int unitSelectionIndex = 0;
            if (0 < this->tribes[tribeID].size) {
                do {
                    unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if ((DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL)
                        && (DAT_UnitsState::instance.units[unitID].dying == 0)) {
                        BVar1 = MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(unitID);
                        if (!BVar1) {
                            return FALSE;
                        }
                    }
                } while (unitSelectionIndex < this->tribes[tribeID].size);
            }
            return TRUE;
        }

    }
}
}
