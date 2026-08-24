#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitsState;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */

        // FUNCTION: STRONGHOLDCRUSADER 0x00535520
        int UnitsState::selectionContainsEngineersOnly()
        {

            if (this->selectionEngineers != 0) {
                int* piVar2 = (int*)&this->selectionEuropeanArchers;
                for (int iVar1 = 0; iVar1 < 0x1b; iVar1++) {
                    if ((iVar1 != 7) && (piVar2[iVar1] != 0)) {
                        return FALSE;
                    }
                }
                // piVar2 = &this->selectionEuropeanArchers;
                // do {
                //     if ((iVar1 != 7) && (piVar2->selectionEuropeanArchers != 0)) {
                //         return 0;
                //     }
                //     iVar1 = iVar1 + 1;
                //     piVar2 = &piVar2->selectionSpearmen;
                // } while (iVar1 < 0x1b);
                // iVar1 = 1;
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
