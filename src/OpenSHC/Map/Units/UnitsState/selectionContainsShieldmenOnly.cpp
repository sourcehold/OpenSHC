#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00535840
        int UnitsState::selectionContainsShieldmenOnly()
        {
            if (this->selectionShield == 0) {
                return 0;
            }
            for (int i = 0; i <= 26; ++i) {
                if (i != 15 && (&this->selectionEuropeanArchers)[i] != 0) {
                    return 0;
                }
            }
            return 1;
        }

    }
}
}
