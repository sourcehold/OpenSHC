#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00535910
        undefined4 UnitsState::selectionHasNoRangedUnits()
        {
            if (this->selectionEuropeanArchers == 0 && this->selectionCrossbowmen == 0 && this->selectionArabArcher == 0
                && this->selectionArabSlinger == 0 && this->selectionCatapults == 0 && this->selectionTrebuchets == 0
                && this->selectionArabHorseArchers == 0 && this->selectionArabFireThrower == 0
                && this->selectionFireBallista == 0 && this->selectionMangonel == 0 && this->selectionBallista == 0) {
                return 1;
            }
            return 0;
        }

    }
}
}
