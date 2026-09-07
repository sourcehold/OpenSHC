#include "../UnitsState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535810
        BOOLEnum UnitsState::selectionContainsOnlyArabAssassins()
        {
            BOOLEnum result = FALSE;
            // I tried simplifying this with an early-return but didn't work
            if (this->selectionArabAssassin != 0) {
                // This really is field pointer increment style. I tried a for loop over the fields as a int[]
                // but that didn't work
                int* pUnitSelection = (int*)&this->selectionEuropeanArchers;
                for (int index = 0; index <= 26; index++) {
                    if ((index != 22) && (*pUnitSelection != 0)) {
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
