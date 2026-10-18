#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0052FCA0
        void UnitsState::setFacingDirectionTowardCoords(int unitID, int x, int y)
        {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculateOrientation,
                DAT_DirectionAlgorithmState::ptr)(this->units[unitID].x, this->units[unitID].y, x, y);
            if (DAT_DirectionAlgorithmState::instance.orientation == 15) {
                return;
            }
            if (this->units[unitID].facingDirection == DAT_DirectionAlgorithmState::instance.orientation) {
                return;
            }
            this->units[unitID].facingDirection = (short)DAT_DirectionAlgorithmState::instance.orientation;
        }

    }
}
}
