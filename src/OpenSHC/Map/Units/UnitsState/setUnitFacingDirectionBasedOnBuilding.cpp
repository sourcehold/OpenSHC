#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0052FF80
        uint UnitsState::setUnitFacingDirectionBasedOnBuilding(int unitID, int buildingID)
        {
            int previousFacingDirection = this->units[unitID].facingDirection;
            if (buildingID == 0) {
                return 0;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                DAT_DirectionAlgorithmState::ptr)(this->units[unitID].x, this->units[unitID].y,
                (short)DAT_BuildingsState::instance.buildings[buildingID].x,
                (short)DAT_BuildingsState::instance.buildings[buildingID].y);
            if (DAT_DirectionAlgorithmState::instance.orientation == 15) {
                return 0;
            }
            if (this->units[unitID].facingDirection == DAT_DirectionAlgorithmState::instance.orientation) {
                return 0;
            }
            int clockwiseSteps
                = DAT_DirectionAlgorithmState::instance.orientation - this->units[unitID].facingDirection;
            if (clockwiseSteps < 0) {
                clockwiseSteps = clockwiseSteps + 8;
            }
            int counterClockwiseSteps
                = this->units[unitID].facingDirection - DAT_DirectionAlgorithmState::instance.orientation;
            if (counterClockwiseSteps < 0) {
                counterClockwiseSteps = counterClockwiseSteps + 8;
            }
            if (clockwiseSteps <= counterClockwiseSteps) {
                this->units[unitID].facingDirection = this->units[unitID].facingDirection + 1;
            } else {
                this->units[unitID].facingDirection = this->units[unitID].facingDirection - 1;
            }
            if (this->units[unitID].facingDirection < 0) {
                this->units[unitID].facingDirection = this->units[unitID].facingDirection + 8;
            }
            if (this->units[unitID].facingDirection >= 8) {
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
            return (uint)(previousFacingDirection != this->units[unitID].facingDirection);
        }

    }
}
}
