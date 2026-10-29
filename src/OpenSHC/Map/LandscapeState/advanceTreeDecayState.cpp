#include "OpenSHC/Map/LandscapeState.func.hpp"

namespace OpenSHC {
namespace Map {

    // Wood chunks are tested signed (jle 0x4F309F, jg 0x4F30B3); the second test re-reads the stored value.
    // FUNCTION: STRONGHOLDCRUSADER 0x004F3080
    void LandscapeState::advanceTreeDecayState(int treeID, int treeUID)
    {
        if (this->trees[treeID].uid == treeUID) {
            if ((short)this->trees[treeID].treeAdultHoodStageRelatedVisual3 > 0) {
                this->trees[treeID].treeAdultHoodStageRelatedVisual3 = this->trees[treeID].treeAdultHoodStageRelatedVisual3 - 1;
            }
            if ((short)this->trees[treeID].treeAdultHoodStageRelatedVisual3 <= 0) {
                this->trees[treeID].state = 3;
            }
            this->trees[treeID].zeroUpTo2 = 2;
        }
    }

}
}