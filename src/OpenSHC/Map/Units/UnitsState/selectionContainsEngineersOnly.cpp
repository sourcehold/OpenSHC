#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535520
        BOOLEnum UnitsState::selectionContainsEngineersOnly()
        {
            if (this->selectionEngineers == 0) {
                return FALSE;
            }
            for (int i = 0; i <= 26; ++i) {
                if (i != 7 && (&this->selectionEuropeanArchers)[i] != 0) {
                    return FALSE;
                }
            }
            return TRUE;
        }

    }
}
}
