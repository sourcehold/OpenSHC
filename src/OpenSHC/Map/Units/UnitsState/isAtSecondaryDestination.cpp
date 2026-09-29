#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00533960
        BOOLEnum UnitsState::isAtSecondaryDestination(int unitID)
        {
            if (this->units[unitID].destinationX_2Unk != this->units[unitID].x) {
                return FALSE;
            }
            return (BOOLEnum)(this->units[unitID].destinationY_2Unk == this->units[unitID].y);
        }

    }
}
}
