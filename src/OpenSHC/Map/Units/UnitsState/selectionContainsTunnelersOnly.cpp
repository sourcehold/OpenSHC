#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/Selection/UnitSelectionEnumInt.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00535700
        int UnitsState::selectionContainsTunnelersOnly()
        {
            int result = FALSE;
            if (this->selectionUnitType[Selection::USE_E_TUNNELERS] != 0) {
                for (int index = 0; index <= 26; index++) {
                    if ((index != Selection::USE_E_TUNNELERS) && (this->selectionUnitType[index] != 0)) {
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
