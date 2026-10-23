#include "../UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00533C70
        void UnitsState::changeDestinationByLeftover(int unitID)
        {
            if (this->units[unitID].leftover > 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByAmount, this)(
                    unitID, this->units[unitID].leftover);
            }
        }

    }
}
}
