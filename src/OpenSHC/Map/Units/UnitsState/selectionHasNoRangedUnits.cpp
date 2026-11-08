#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/Selection/UnitSelectionEnumInt.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00535910
        BOOLEnum UnitsState::selectionHasNoRangedUnits()
        {
            if (this->selectionUnitType[Selection::USE_E_ARCHERS] == 0
                && this->selectionUnitType[Selection::USE_E_CROSSBOWMEN] == 0
                && this->selectionUnitType[Selection::USE_A_ARAB_ARCHERS] == 0
                && this->selectionUnitType[Selection::USE_A_SLINGERS] == 0
                && this->selectionUnitType[Selection::USE_E_CATAPULTS] == 0
                && this->selectionUnitType[Selection::USE_E_ARCHERS] == 0
                && this->selectionUnitType[Selection::USE_E_TREBUCHETS] == 0
                && this->selectionUnitType[Selection::USE_A_HORSE_ARCHERS] == 0
                && this->selectionUnitType[Selection::USE_A_FIRETHROWERS] == 0
                && this->selectionUnitType[Selection::USE_A_FIRE_BALLISTAS] == 0
                && this->selectionUnitType[Selection::USE_E_MANGONELS] == 0
                && this->selectionUnitType[Selection::USE_E_BALLISTAS] == 0) {
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
