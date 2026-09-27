#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052FE90
        BOOLEnum UnitsState::setUnitFacingDirectionForTargetXandY(int unitID, int targetX, int targetY)
        {
            short _previousFacingDirection = this->units[unitID].facingDirection;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                DAT_DirectionAlgorithmState::ptr)(this->units[unitID].x, this->units[unitID].y, targetX, targetY);
            if (DAT_DirectionAlgorithmState::instance.orientation == 15) {
                return FALSE;
            }
            if (this->units[unitID].facingDirection == DAT_DirectionAlgorithmState::instance.orientation) {
                return FALSE;
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
            return (BOOLEnum)(_previousFacingDirection != this->units[unitID].facingDirection);
        }

    }
}
}
