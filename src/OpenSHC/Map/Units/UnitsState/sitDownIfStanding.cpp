#include "../UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0052FBF0
        BOOLEnum UnitsState::sitDownIfStanding(int unitID)
        {
            if (this->units[unitID].seated != 0) {
                return FALSE;
            }
            this->units[unitID].substate = 101;
            this->units[unitID].animationCycleNumber = 0;
            return TRUE;
        }

    }
}
}
