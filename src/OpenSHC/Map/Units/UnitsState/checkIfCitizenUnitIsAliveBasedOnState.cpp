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
            return 0x6f <= this->units[unitID].state.generic && this->units[unitID].state.generic <= 0x74;
        }

    }
}
}
