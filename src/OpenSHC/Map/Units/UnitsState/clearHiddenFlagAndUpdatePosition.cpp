#include "../UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053E8D0
        void UnitsState::clearHiddenFlagAndUpdatePosition(int unitID)
        {
            if (this->units[unitID].unknownTestAgainst0_2 != 0) {
                this->units[unitID].unknownTestAgainst0_2 = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitPendingUnitPosition, this)(unitID);
            }
        }

    }
}
}
