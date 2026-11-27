#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/Selection/UnitSelectionEnumInt.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00535980
        BOOLEnum UnitsState::selectionHasFootSoldiers()
        {
            if (this->selectionUnitType[Selection::USE_E_ENGINEERS] == 0
                && this->selectionUnitType[Selection::USE_A_SLAVES] == 0
                && this->selectionUnitType[Selection::USE_E_SPEARMEN] == 0
                && this->selectionUnitType[Selection::USE_E_ARCHERS] == 0
                && this->selectionUnitType[Selection::USE_E_MACEMEN] == 0
                && this->selectionUnitType[Selection::USE_E_PIKEMEN] == 0) {
                return FALSE;
            }
            return TRUE;
        }

    }
}
}
