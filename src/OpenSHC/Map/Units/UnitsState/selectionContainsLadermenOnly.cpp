#include "../UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005357E0
        int UnitsState::selectionContainsLadermenOnly()
        {
            int result = FALSE;
            // I tried simplifying this with an early-return but didn't work
            if (this->selectionLaddermen != 0) {
                // This really is field pointer increment style. I tried a for loop over the fields as a int[]
                // but that didn't work
                int* pUnitSelection = (int*)&this->selectionEuropeanArchers;
                for (int index = 0; index <= 26; index++) {
                    if ((index != 8) && (*pUnitSelection != 0)) {
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
