#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */

        // FUNCTION: STRONGHOLDCRUSADER 0x00535700
        int UnitsState::selectionContainsTunnelersOnly()

        {
            if (this->selectionTunnelers != 0) {
                int* piVar2 = (int*)&this->selectionEuropeanArchers;
                for (int iVar1 = 0; iVar1 < 0x1b; iVar1++) {
                    if ((iVar1 != 9) && (piVar2[iVar1] != 0)) {
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
