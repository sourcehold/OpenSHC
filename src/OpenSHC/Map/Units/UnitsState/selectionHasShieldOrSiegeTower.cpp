#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/Selection/UnitSelectionEnumInt.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005358C0
        BOOLEnum UnitsState::selectionHasShieldOrSiegeTower()
        {
            if (this->selectionShield != 0 || this->selectionSiegeTower != 0) {
                for (int i = 0; i <= 26; ++i) {
                    if (i != Selection::USE_E_SHIELDS && i != Selection::USE_E_SIEGETOWERS
                        && (&this->selectionEuropeanArchers)[i] != 0) {
                        return FALSE;
                    }
                }
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
