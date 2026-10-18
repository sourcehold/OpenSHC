#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00535580
        undefined4 UnitsState::selectionHasMobileAssaultUnits()
        {
            if (this->selectionKnights == 0 && this->selectionLaddermen == 0 && this->selectionBatteringRam == 0
                && this->selectionTrebuchets == 0 && this->selectionCatapults == 0
                && this->selectionArabHorseArchers == 0 && this->selectionFireBallista == 0
                && this->selectionSiegeTower == 0) {
                return 0;
            }
            return 1;
        }

    }
}
}
