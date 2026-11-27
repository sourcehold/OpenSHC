#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/Selection/UnitSelectionEnumInt.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00535580
        BOOLEnum UnitsState::selectionHasMobileAssaultUnits()
        {
            if (this->selectionUnitType[Selection::USE_E_KNIGHTS] == 0
                && this->selectionUnitType[Selection::USE_E_LADDERMEN] == 0
                && this->selectionUnitType[Selection::USE_E_BATTERING_RAMS] == 0
                && this->selectionUnitType[Selection::USE_E_TREBUCHETS] == 0
                && this->selectionUnitType[Selection::USE_E_CATAPULTS] == 0
                && this->selectionUnitType[Selection::USE_A_HORSE_ARCHERS] == 0
                && this->selectionUnitType[Selection::USE_A_FIRE_BALLISTAS] == 0
                && this->selectionUnitType[Selection::USE_E_SIEGETOWERS] == 0) {
                return FALSE;
            }
            return TRUE;
        }

    }
}
}
