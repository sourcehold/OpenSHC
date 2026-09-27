#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052FE00
        void UnitsState::setFacingDirectionTowardUnitMicro(int unitID, int targetUnitID)
        {
            if (targetUnitID < 1) {
                return;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                DAT_DirectionAlgorithmState::ptr)(this->units[unitID].microXPosition,
                this->units[unitID].microYPosition, this->units[targetUnitID].microXPosition,
                this->units[targetUnitID].microYPosition);
            if (DAT_DirectionAlgorithmState::instance.orientation == 15) {
                return;
            }
            UnitTypeShort _unitType = this->units[unitID].unitType;
            this->units[unitID].orientation = (short)DAT_DirectionAlgorithmState::instance.orientation;
            if (_unitType != OpenSHC::Map::Units::UT_E_KNIGHT) {
                return;
            }
            this->units[unitID].orientation = this->units[unitID].orientation - 1;
            if (this->units[unitID].orientation < 0) {
                this->units[unitID].orientation = this->units[unitID].orientation + 8;
            }
        }

    }
}
}
