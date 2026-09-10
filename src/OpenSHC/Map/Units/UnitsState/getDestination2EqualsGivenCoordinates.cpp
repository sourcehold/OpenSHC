#include "../UnitsState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00533920
        BOOLEnum UnitsState::getDestination2EqualsGivenCoordinates(int unitID, int x, int y)
        {
            if (this->units[unitID].destinationX_2Unk != x) {
                return TRUE;
            }
            return this->units[unitID].destinationY_2Unk != y;
        }

    }
}
}
