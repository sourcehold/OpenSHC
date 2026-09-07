#include "../UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00533C70
        void UnitsState::changeDestinationByLeftover(int unitID)
        {
            short _leftover = this->units[unitID].leftover;
            if (0 < _leftover) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByAmount, this)(
                    unitID, _leftover);
            }
        }

    }
}
}
