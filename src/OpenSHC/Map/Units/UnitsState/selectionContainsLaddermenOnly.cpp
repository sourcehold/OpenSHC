#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/Selection/UnitSelectionEnumInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005357E0
        BOOLEnum UnitsState::selectionContainsLaddermenOnly()
        {
            if (this->selectionUnitType[Selection::USE_E_LADDERMEN] == 0) {
                return FALSE;
            }
            for (int i = 0; i <= 26; ++i) {
                if (i != Selection::USE_E_LADDERMEN && this->selectionUnitType[i] != 0) {
                    return FALSE;
                }
            }
            return TRUE;
        }

    }
}
}
