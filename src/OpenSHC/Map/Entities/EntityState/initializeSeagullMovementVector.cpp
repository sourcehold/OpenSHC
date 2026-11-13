#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00403790
        void EntityState::initializeSeagullMovementVector(int seagullID, int x, int y, int targetX, int targetY)
        {
            int distanceY;
            if (y > targetY) {
                distanceY = y - targetY;
            } else {
                distanceY = targetY - y;
            }
            int distanceX;
            if (x > targetX) {
                distanceX = x - targetX;
            } else {
                distanceX = targetX - x;
            }
            if (x > targetX) {
                this->seagullArray[seagullID].pathStepX = -1;
            } else {
                this->seagullArray[seagullID].pathStepX = 1;
            }
            if (y > targetY) {
                this->seagullArray[seagullID].pathStepY = -1;
            } else {
                this->seagullArray[seagullID].pathStepY = 1;
            }
            if (distanceX == 0) {
                if (distanceY == 0) {
                    this->seagullArray[seagullID].pathAxisCase = 0;
                } else {
                    this->seagullArray[seagullID].pathAxisCase = 1;
                }
            } else if (distanceY == 0) {
                this->seagullArray[seagullID].pathAxisCase = 2;
            } else if (distanceY > distanceX) {
                this->seagullArray[seagullID].pathAxisCase = 3;
            } else {
                this->seagullArray[seagullID].pathAxisCase = 4;
            }
            int majorLength;
            if (distanceX > distanceY) {
                majorLength = distanceX;
            } else {
                majorLength = distanceY;
            }
            this->seagullArray[seagullID].pathMajorLength = majorLength;
            if (this->seagullArray[seagullID].pathAxisCase == 3) {
                int const errorStep = distanceX * 2;
                this->seagullArray[seagullID].pathErrorStepStraight = errorStep;
                this->seagullArray[seagullID].pathErrorStepDiagonal = errorStep - distanceY * 2;
                this->seagullArray[seagullID].pathError = errorStep - distanceY;
            } else if (this->seagullArray[seagullID].pathAxisCase == 4) {
                int const errorStep = distanceY * 2;
                this->seagullArray[seagullID].pathErrorStepStraight = errorStep;
                this->seagullArray[seagullID].pathErrorStepDiagonal = errorStep - distanceX * 2;
                this->seagullArray[seagullID].pathError = errorStep - distanceX;
            }
        }

    }
}
}
