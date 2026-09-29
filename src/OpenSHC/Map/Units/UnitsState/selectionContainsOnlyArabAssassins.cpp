#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535810
        BOOLEnum UnitsState::selectionContainsOnlyArabAssassins()
        {
            if (this->selectionArabAssassin == 0) {
                return FALSE;
            }
            for (int i = 0; i <= 26; ++i) {
                if (i != 22 && (&this->selectionEuropeanArchers)[i] != 0) {
                    return FALSE;
                }
            }
            return TRUE;
        }

    }
}
}
