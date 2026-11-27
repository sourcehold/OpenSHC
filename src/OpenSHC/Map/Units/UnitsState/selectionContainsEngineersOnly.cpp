#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/Selection/UnitSelectionEnumInt.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitsState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535520
        int UnitsState::selectionContainsEngineersOnly()
        {
            int result = FALSE;
            if (this->selectionUnitType[Selection::USE_E_ENGINEERS] != 0) {
                for (int index = 0; index <= 26; index++) {
                    if ((index != Selection::USE_E_ENGINEERS) && (this->selectionUnitType[index] != 0)) {
                        return FALSE;
                    }
                }
                result = TRUE;
            }
            return result;
        }

    }
}
}
