#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/Selection/UnitSelectionEnumInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535560
        BOOLEnum UnitsState::selectionHasArchers()
        {
            if (this->selectionUnitType[Selection::USE_E_ARCHERS] != 0) {
                return TRUE;
            }
            return this->selectionUnitType[Selection::USE_A_ARAB_ARCHERS] != 0;
        }

    }
}
}
