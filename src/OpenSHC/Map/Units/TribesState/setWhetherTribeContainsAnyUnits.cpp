#include "OpenSHC/Map/Units/TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005224E0
        void TribesState::setWhetherTribeContainsAnyUnits(int tribeID)
        {
            for (int iVar1 = 0; iVar1 < 200; iVar1++) {
                if (this->tribes[tribeID].unitSelectionBitMasked[iVar1] != 0) {
                    this->tribes[tribeID].highestID = iVar1;
                    return;
                }
            }
        }

    }
}
}
