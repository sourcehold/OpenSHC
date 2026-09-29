#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535730
        BOOLEnum UnitsState::selectionContainsRangedOnlyUnits()
        {
            if (this->selectionEuropeanArchers != 0 || this->selectionCrossbowmen != 0 || this->selectionArabArcher != 0
                || this->selectionArabSlinger != 0 || this->selectionArabHorseArchers != 0
                || this->selectionArabFireThrower != 0 || this->selectionFireBallista != 0
                || this->selectionCatapults != 0 || this->selectionTrebuchets != 0) {
                for (int i = 0; i <= 26; ++i) {
                    if (i != 0 && i != 3 && i != 19 && i != 21 && i != 23 && i != 25 && i != 26 && i != 11 && i != 12
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
