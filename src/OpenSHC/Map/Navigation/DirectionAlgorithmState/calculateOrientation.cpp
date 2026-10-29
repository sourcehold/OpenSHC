#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046C920
        void DirectionAlgorithmState::calculateOrientation(
            int currentXPosition, int currentYPosition, int destinationXPosition, int destinationYPosition)
        {
            if (currentYPosition > destinationYPosition) {
                if (currentXPosition > destinationXPosition) {
                    this->orientation = 7;
                } else if (currentXPosition < destinationXPosition) {
                    this->orientation = 1;
                } else {
                    this->orientation = 0;
                }
            } else if (currentYPosition < destinationYPosition) {
                if (currentXPosition > destinationXPosition) {
                    this->orientation = 5;
                } else if (currentXPosition < destinationXPosition) {
                    this->orientation = 3;
                } else {
                    this->orientation = 4;
                }
            } else {
                if (currentXPosition > destinationXPosition) {
                    this->orientation = 6;
                } else if (currentXPosition < destinationXPosition) {
                    this->orientation = 2;
                } else {
                    this->orientation = 15;
                }
            }
        }

    }
}
}
