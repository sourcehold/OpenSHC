#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005339A0
        BOOLEnum UnitsState::hasUnitReachedDestination(int unitID)
        {
            if (this->units[unitID].tunnelerFinishedDigging != 0) {
                return FALSE;
            }
            if (this->units[unitID].climbDataID != 0) {
                if (this->units[unitID].destinationX_2Unk != this->units[unitID].x) {
                    return FALSE;
                }
                if (this->units[unitID].destinationY_2Unk != this->units[unitID].y) {
                    return FALSE;
                }
            }
            return TRUE;
        }

    }
}
}
