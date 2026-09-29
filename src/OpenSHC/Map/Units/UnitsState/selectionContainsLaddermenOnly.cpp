#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005357E0
        int UnitsState::selectionContainsLaddermenOnly()
        {
            if (this->selectionLaddermen == 0) {
                return 0;
            }
            for (int i = 0; i <= 26; ++i) {
                if (i != 8 && (&this->selectionEuropeanArchers)[i] != 0) {
                    return 0;
                }
            }
            return 1;
        }

    }
}
}
