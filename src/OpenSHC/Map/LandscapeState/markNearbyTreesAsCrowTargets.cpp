#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Map {

    // stage < 4 and distanceHigh < 4 are signed (jge 0x4F30FA / 0x4F312D); isTreeAdult is called on this.
    // FUNCTION: STRONGHOLDCRUSADER 0x004F30D0
    void LandscapeState::markNearbyTreesAsCrowTargets(int x, int y)
    {
        for (int treeID = 1; treeID < this->maxTreeCount; treeID++) {
            if (this->trees[treeID].state != 2) {
                continue;
            }
            if (this->trees[treeID].stage >= 4) {
                continue;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::isTreeAdult, this)(
                    treeID, this->trees[treeID].uid)
                == FALSE) {
                continue;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                DAT_DirectionAlgorithmState::ptr)(
                x, y, (short)this->trees[treeID].xPosition, (short)this->trees[treeID].yPosition);
            if (DAT_DirectionAlgorithmState::instance.distanceHigh < 4) {
                this->trees[treeID].unknownDistanceRelatedToCrow = 1;
            }
        }
    }

}
}
