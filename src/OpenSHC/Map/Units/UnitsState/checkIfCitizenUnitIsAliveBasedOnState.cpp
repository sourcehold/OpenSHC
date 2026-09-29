#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00530FD0
        BOOLEnum UnitsState::checkIfCitizenUnitIsAliveBasedOnState(int unitID)
        {
            if ((short)this->units[unitID].state.generic >= States::US_DEATH_01
                && (short)this->units[unitID].state.generic <= States::US_STONE_DEATH_03) {
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
