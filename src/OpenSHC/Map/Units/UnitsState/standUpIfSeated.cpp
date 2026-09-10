#include "../UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0052FBB0
        BOOLEnum UnitsState::standUpIfSeated(int param_1)
        {
            if (this->units[param_1].seated == 0) {
                return FALSE;
            }
            this->units[param_1].substate = 100;
            this->units[param_1].animationCycleNumber = 0;
            return TRUE;
        }

    }
}
}
