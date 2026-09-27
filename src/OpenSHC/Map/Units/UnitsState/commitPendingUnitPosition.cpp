#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053BB10
        void UnitsState::commitPendingUnitPosition(int unitID)
        {
            if (this->units[unitID].field105_0xe8 != 0) {
                this->units[unitID].tile = this->units[unitID].nextTileUnk;
                this->units[unitID].x = this->units[unitID].mimicCurrentXPosition;
                this->units[unitID].y = this->units[unitID].mimicCurrentYPosition;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setMoveDelayForUnitsOnSameTiles, this)(
                unitID, this->units[unitID].tile);
        }

    }
}
}
