#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0052FD00
        undefined4 UnitsState::setUnitFacingDirectionTowardsTarget(int unitID, int targetUnitID)
        {
            if (targetUnitID <= 0) {
                return 0;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                DAT_DirectionAlgorithmState::ptr)(
                this->units[unitID].x, this->units[unitID].y, this->units[targetUnitID].x, this->units[targetUnitID].y);
            if (DAT_DirectionAlgorithmState::instance.orientation == 15) {
                return 0;
            }
            if (this->units[unitID].facingDirection == DAT_DirectionAlgorithmState::instance.orientation) {
                return 0;
            }
            int _clockwiseSteps
                = DAT_DirectionAlgorithmState::instance.orientation - this->units[unitID].facingDirection;
            if (_clockwiseSteps < 0) {
                _clockwiseSteps = _clockwiseSteps + 8;
            }
            int _counterClockwiseSteps
                = this->units[unitID].facingDirection - DAT_DirectionAlgorithmState::instance.orientation;
            if (_counterClockwiseSteps < 0) {
                _counterClockwiseSteps = _counterClockwiseSteps + 8;
            }
            if (_counterClockwiseSteps < _clockwiseSteps) {
                this->units[unitID].facingDirection = this->units[unitID].facingDirection - 1;
            } else {
                this->units[unitID].facingDirection = this->units[unitID].facingDirection + 1;
            }
            if (this->units[unitID].facingDirection < 0) {
                this->units[unitID].facingDirection = this->units[unitID].facingDirection + 8;
            }
            if (this->units[unitID].facingDirection > 7) {
                this->units[unitID].facingDirection = this->units[unitID].facingDirection - 8;
            }
            this->units[unitID].facingDirectionMapOrientationCorrected = this->units[unitID].facingDirection;
            this->units[unitID].facingDirectionMapOrientationCorrected
                = this->units[unitID].facingDirectionMapOrientationCorrected
                - (short)DAT_TileMapState::instance.mapOrientation;
            if (this->units[unitID].facingDirectionMapOrientationCorrected < 0) {
                this->units[unitID].facingDirectionMapOrientationCorrected
                    = this->units[unitID].facingDirectionMapOrientationCorrected + 8;
            }
            return 1;
        }

    }
}
}
