#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005358C0
        undefined4 UnitsState::selectionHasShieldOrSiegeTower()
        {
            if (this->selectionShield != 0 || this->selectionSiegeTower != 0) {
                for (int i = 0; i <= 26; ++i) {
                    if (i != 15 && i != 14 && (&this->selectionEuropeanArchers)[i] != 0) {
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
