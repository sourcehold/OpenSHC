#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005224E0
        int TribesState::setWhetherTribeContainsAnyUnits(int tribeID)
        {
            for (int i = 0; i < 200; ++i) {
                if (this->tribes[tribeID].unitSelectionBitMasked[i] != 0) {
                    this->tribes[tribeID].highestID = i;
                    return i;
                }
            }
            return 200;
        }

    }
}
}
