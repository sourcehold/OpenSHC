#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/Selection/UnitSelectionEnumInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535730
        BOOLEnum UnitsState::selectionContainsRangedOnlyUnits()
        {
            if (this->selectionUnitType[Selection::USE_E_ARCHERS] != 0
                || this->selectionUnitType[Selection::USE_E_CROSSBOWMEN] != 0
                || this->selectionUnitType[Selection::USE_A_ARAB_ARCHERS] != 0
                || this->selectionUnitType[Selection::USE_A_SLINGERS] != 0
                || this->selectionUnitType[Selection::USE_A_HORSE_ARCHERS] != 0
                || this->selectionUnitType[Selection::USE_A_FIRETHROWERS] != 0
                || this->selectionUnitType[Selection::USE_A_FIRE_BALLISTAS] != 0
                || this->selectionUnitType[Selection::USE_E_CATAPULTS] != 0
                || this->selectionUnitType[Selection::USE_E_TREBUCHETS] != 0) {
                for (int i = 0; i <= 26; ++i) {
                    if (i != Selection::USE_E_ARCHERS && i != Selection::USE_E_CROSSBOWMEN
                        && i != Selection::USE_A_ARAB_ARCHERS && i != Selection::USE_A_SLINGERS
                        && i != Selection::USE_A_HORSE_ARCHERS && i != Selection::USE_A_FIRETHROWERS
                        && i != Selection::USE_A_FIRE_BALLISTAS && i != Selection::USE_E_CATAPULTS
                        && i != Selection::USE_E_TREBUCHETS && this->selectionUnitType[i] != 0) {
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
