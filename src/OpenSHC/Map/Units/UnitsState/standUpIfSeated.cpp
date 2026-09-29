#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052FBB0
        BOOLEnum UnitsState::standUpIfSeated(int unitID)
        {
            if (this->units[unitID].seated == 0) {
                return FALSE;
            }
            this->units[unitID].substate = 100;
            this->units[unitID].animationCycleNumber = 0;
            return TRUE;
        }

    }
}
}
