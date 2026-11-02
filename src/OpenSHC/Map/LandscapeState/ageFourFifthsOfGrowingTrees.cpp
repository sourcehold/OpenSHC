#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // Used slots of type 1..4 (unsigned range check at 0x4F2DC1) with stage 2..4 go to stage 5 unless
    // (currentNumber2 (signed short) ^ rng1) % 5 == 0 (signed idiv, je 0x4F2DE6).
    // FUNCTION: STRONGHOLDCRUSADER 0x004F2DA0
    void LandscapeState::ageFourFifthsOfGrowingTrees()
    {
        for (int treeID = 1; treeID < this->maxTreeCount; treeID++) {
            if (this->trees[treeID].state == 0) {
                continue;
            }
            int const treeType = this->trees[treeID].treeType;
            if (treeType >= OpenSHC::Map::Trees::TT_CHESTNUT && treeType <= OpenSHC::Map::Trees::TT_BIRCH
                && this->trees[treeID].stage >= 2 && this->trees[treeID].stage <= 4
                && (SEC_RNG::instance.currentNumber2 ^ this->trees[treeID].rng1) % 5 != 0) {
                this->trees[treeID].stage = 5;
            }
        }
    }

}
}
