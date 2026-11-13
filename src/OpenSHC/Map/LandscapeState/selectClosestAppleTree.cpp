#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3610
    int LandscapeState::selectClosestAppleTree(int xPosition, int yPosition, int param_3)
    {
        int closestDistance = 1000;
        int closestTreeID = 0;
        for (int treeID = 1; treeID < this->maxTreeCount; ++treeID) {
            if (this->trees[treeID].state == 2 && this->trees[treeID].treeType == Trees::TT_APPLEUnk
                && this->trees[treeID].stage == 3) {
                MACRO_CALL_MEMBER(Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(
                    xPosition, yPosition, this->trees[treeID].xPosition, this->trees[treeID].yPosition);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < closestDistance) {
                    closestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    closestTreeID = treeID;
                }
            }
        }
        if (closestDistance >= 30) {
            return 0;
        }
        if (closestTreeID <= 0) {
            return 0;
        }
        this->x = this->trees[closestTreeID].xPosition;
        this->y = this->trees[closestTreeID].yPosition;
        if (param_3 == 0) {
            this->x -= 2;
        } else if (param_3 == 1) {
            this->y += 2;
        } else if (param_3 == 2) {
            this->x += 2;
        } else {
            this->y -= 2;
        }
        return closestTreeID;
    }

}
}
