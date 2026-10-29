#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046CC80
        int DirectionAlgorithmState::setAxisBasedDistanceResult(
            int destinationXPosition, int destinationYPosition, int fromXPosition, int fromYPosition)
        {
            if (destinationXPosition > fromXPosition) {
                this->distanceX = destinationXPosition - fromXPosition;
            } else {
                this->distanceX = fromXPosition - destinationXPosition;
            }
            if (destinationYPosition > fromYPosition) {
                this->distanceY = destinationYPosition - fromYPosition;
            } else {
                this->distanceY = fromYPosition - destinationYPosition;
            }

            if (this->distanceX < this->distanceY) {
                this->distanceLow = this->distanceX;
                this->distanceHigh = this->distanceY;
            } else {
                this->distanceHigh = this->distanceX;
                this->distanceLow = this->distanceY;
            }
            return this->distanceX + this->distanceY;
        }

    }
}
}
