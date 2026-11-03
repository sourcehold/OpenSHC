#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/Selection/UnitSelectionEnumInt.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00535870
        BOOLEnum UnitsState::selectionHasShieldOrSiegeMobileUnits()
        {
            if (this->selectionUnitType[Selection::USE_E_SHIELDS] != 0
                || this->selectionUnitType[Selection::USE_E_SIEGETOWERS] != 0
                || this->selectionUnitType[Selection::USE_E_BATTERING_RAMS] != 0) {
                for (int i = 0; i <= 26; ++i) {
                    if (i != Selection::USE_E_SHIELDS && i != Selection::USE_E_BATTERING_RAMS
                        && i != Selection::USE_E_SIEGETOWERS && this->selectionUnitType[i] != 0) {
                        return FALSE;
                    }
                }
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
