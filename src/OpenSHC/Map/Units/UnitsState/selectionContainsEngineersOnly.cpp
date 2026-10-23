#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitsState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535520
        int UnitsState::selectionContainsEngineersOnly()
        {
            int result = FALSE;
            // I tried simplifying this with an early-return but didn't work
            if (this->selectionEngineers != 0) {
                // This really is field pointer increment style. I tried a for loop over the fields as a int[]
                // but that didn't work
                int* pUnitSelection = (int*)&this->selectionEuropeanArchers;
                for (int index = 0; index <= 26; index++) {
                    if ((index != 7) && (*pUnitSelection != 0)) {
                        return FALSE;
                    }
                    pUnitSelection++;
                }
                result = TRUE;
            }
            return result;
        }

    }
}
}
