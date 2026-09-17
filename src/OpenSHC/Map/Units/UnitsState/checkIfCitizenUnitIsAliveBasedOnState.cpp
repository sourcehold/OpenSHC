#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00530FD0
        BOOLEnum UnitsState::checkIfCitizenUnitIsAliveBasedOnState(int param_1)
        {
            short _state = (unsigned short)this->units[param_1].state.generic;
            if ((0x6f <= _state)) {
                if (_state <= 0x74) {
                    return TRUE;
                } else {
                    return FALSE;
                }

            } else {
                return FALSE;
            }
        }

    }
}
}
