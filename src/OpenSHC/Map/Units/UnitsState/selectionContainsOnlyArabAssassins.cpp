#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */

        // FUNCTION: STRONGHOLDCRUSADER 0x00535810
        BOOLEnum UnitsState::selectionContainsOnlyArabAssassins()

        {
            if (this->selectionArabAssassin != 0) {
                int* piVar2 = (int*)&this->selectionEuropeanArchers;
                for (int iVar1 = 0; iVar1 < 0x1b; iVar1++) {
                    if ((iVar1 != 0x16) && (piVar2[iVar1] != 0)) {
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
