#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005355E0
        undefined4 UnitsState::selectionHasMixedAssaultAndInfantry()
        {
            if (this->selectionKnights != 0 || this->selectionLaddermen != 0 || this->selectionBatteringRam != 0
                || this->selectionTrebuchets != 0 || this->selectionCatapults != 0
                || this->selectionArabHorseArchers != 0 || this->selectionFireBallista != 0
                || this->selectionSiegeTower != 0) {
                for (int i = 0; i <= 26; ++i) {
                    if (i != 6 && i != 8 && i != 13 && i != 12 && i != 11 && i != 23 && i != 26 && i != 14
                        && (&this->selectionEuropeanArchers)[i] != 0) {
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
