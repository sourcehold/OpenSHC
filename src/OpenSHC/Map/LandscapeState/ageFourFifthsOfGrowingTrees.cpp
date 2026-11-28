#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2DA0
    void LandscapeState::ageFourFifthsOfGrowingTrees()
    {
        for (int treeID = 1; treeID < this->maxTreeCount; treeID++) {
            if (this->trees[treeID].state == 0) {
                continue;
            }
            int const treeType = this->trees[treeID].treeType;
            if (treeType >= OpenSHC::Map::Trees::TT_TREE_OLIVE && treeType <= OpenSHC::Map::Trees::TT_TREE_CHERRY
                && this->trees[treeID].stage >= 2 && this->trees[treeID].stage <= 4
                && (SEC_RNG::instance.currentNumber2 ^ this->trees[treeID].rng1) % 5 != 0) {
                this->trees[treeID].stage = 5;
            }
        }
    }

}
}
