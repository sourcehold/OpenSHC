#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/Selection/UnitSelectionEnumInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535810
        BOOLEnum UnitsState::selectionContainsOnlyArabAssassins()
        {
            BOOLEnum result = FALSE;
            if (this->selectionUnitType[Selection::USE_A_ASSASSINS] != 0) {
                for (int index = 0; index <= 26; index++) {
                    if ((index != Selection::USE_A_ASSASSINS) && (this->selectionUnitType[index] != 0)) {
                        return FALSE;
                    }
                }
                result = TRUE;
            }
            return result;
        }

    }
}
}
