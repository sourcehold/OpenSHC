#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046C9E0
        void DirectionAlgorithmState::calculatePreferredRelativeOrientation(int fromX, int fromY, int toX, int toY)
        {
            if (fromX > toX) {
                this->distanceX = fromX - toX;
            } else {
                this->distanceX = toX - fromX;
            }
            if (fromY > toY) {
                this->distanceY = fromY - toY;
            } else {
                this->distanceY = toY - fromY;
            }

            if (this->distanceX > this->distanceY * 2) {
                if (fromX > toX) {
                    this->orientation = 6;
                } else {
                    this->orientation = 2;
                }
            } else if (this->distanceY > this->distanceX * 2) {
                if (fromY > toY) {
                    this->orientation = 0;
                } else {
                    this->orientation = 4;
                }
            } else if (fromY > toY) {
                if (fromX > toX) {
                    this->orientation = 7;
                } else {
                    this->orientation = 1;
                }
            } else if (fromY < toY) {
                if (fromX > toX) {
                    this->orientation = 5;
                } else {
                    this->orientation = 3;
                }
            } else {
                this->orientation = 15;
            }
        }

    }
}
}
