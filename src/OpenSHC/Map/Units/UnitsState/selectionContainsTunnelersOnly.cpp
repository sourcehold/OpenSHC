#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00535700
        int UnitsState::selectionContainsTunnelersOnly()
        {
            if (this->selectionTunnelers == 0) {
                return 0;
            }
            for (int i = 0; i <= 26; ++i) {
                if (i != 9 && (&this->selectionEuropeanArchers)[i] != 0) {
                    return 0;
                }
            }
            return 1;
        }

    }
}
}
