#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00530FD0
        BOOLEnum UnitsState::checkIfCitizenUnitIsAliveBasedOnState(int unitID)
        {
            short const state = (ushort)this->units[unitID].state.generic;
            if (state >= 111) {
                if (state <= 116) {
                    return TRUE;
                }
                return FALSE;
            }
            return FALSE;
        }

    }
}
}
