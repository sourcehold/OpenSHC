#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/Selection/UnitSelectionEnumInt.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005355E0
        BOOLEnum UnitsState::selectionHasMixedAssaultAndInfantry()
        {
            if (this->selectionUnitType[Selection::USE_E_KNIGHTS] != 0
                || this->selectionUnitType[Selection::USE_E_LADDERMEN] != 0
                || this->selectionUnitType[Selection::USE_E_BATTERING_RAMS] != 0
                || this->selectionUnitType[Selection::USE_E_TREBUCHETS] != 0
                || this->selectionUnitType[Selection::USE_E_CATAPULTS] != 0
                || this->selectionUnitType[Selection::USE_A_HORSE_ARCHERS] != 0
                || this->selectionUnitType[Selection::USE_A_FIRE_BALLISTAS] != 0
                || this->selectionUnitType[Selection::USE_E_SIEGETOWERS] != 0) {
                for (int i = 0; i <= 26; ++i) {
                    if (i != Selection::USE_E_KNIGHTS && i != Selection::USE_E_LADDERMEN
                        && i != Selection::USE_E_BATTERING_RAMS && i != Selection::USE_E_TREBUCHETS
                        && i != Selection::USE_E_CATAPULTS && i != Selection::USE_A_HORSE_ARCHERS
                        && i != Selection::USE_A_FIRE_BALLISTAS && i != Selection::USE_E_SIEGETOWERS
                        && this->selectionUnitType[i] != 0) {
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
