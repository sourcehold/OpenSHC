#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00535980
        undefined4 UnitsState::selectionHasFootSoldiers()
        {
            if (this->selectionEngineers == 0 && this->selectionArabSlave == 0 && this->selectionSpearmen == 0
                && this->selectionEuropeanArchers == 0 && this->selectionMacemen == 0 && this->selectionPikemen == 0) {
                return 0;
            }
            return 1;
        }

    }
}
}
