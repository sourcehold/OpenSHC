#include "../UnitsState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535560
        BOOLEnum UnitsState::selectionHasArchers()
        {
            if (this->selectionEuropeanArchers != 0) {
                return TRUE;
            }
            return this->selectionArabArcher != 0;
        }

    }
}
}
