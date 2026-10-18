#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00535870
        undefined4 UnitsState::selectionHasShieldOrSiegeMobileUnits()
        {
            if (this->selectionShield != 0 || this->selectionSiegeTower != 0 || this->selectionBatteringRam != 0) {
                for (int i = 0; i <= 26; ++i) {
                    if (i != 15 && i != 13 && i != 14 && (&this->selectionEuropeanArchers)[i] != 0) {
                        return 0;
                    }
                }
                return 1;
            }
            return 0;
        }

    }
}
}
