#include "OpenSHC/Map/LandscapeState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2C20
    undefined4 LandscapeState::getTreeGrowthTargetStage(int treeID)
    {
        switch (this->trees[treeID].treeType) {
        case OpenSHC::Map::Trees::TT_TREE_OLIVE:
            switch (this->trees[treeID].stage) {
            case 0:
                return 1;
            case 1:
                return 2;
            case 2:
                return 3;
            }
            return 4;
        case OpenSHC::Map::Trees::TT_TREE_DATE:
        case OpenSHC::Map::Trees::TT_TREE_COCONUT:
        case OpenSHC::Map::Trees::TT_TREE_CHERRY:
            switch (this->trees[treeID].stage) {
            case 0:
                return 1;
            case 1:
                return 1;
            case 2:
                return 2;
            }
            return 3;
        case OpenSHC::Map::Trees::TT_SHRUB_NEEDLE_PALM_A:
        case OpenSHC::Map::Trees::TT_SHRUB_NEEDLE_PALM_B:
        case OpenSHC::Map::Trees::TT_SHRUB_NEEDLE_PALM_C:
        case OpenSHC::Map::Trees::TT_SHRUB_NEEDLE_PALM_D:
        case OpenSHC::Map::Trees::TT_SHRUB_NEEDLE_PALM_E:
        case OpenSHC::Map::Trees::TT_SHRUB_PYGMY_A:
        case OpenSHC::Map::Trees::TT_SHRUB_PYGMY_B:
        case OpenSHC::Map::Trees::TT_SHRUB_PYGMY_C:
        case OpenSHC::Map::Trees::TT_SHRUB_PYGMY_D:
        case OpenSHC::Map::Trees::TT_SHRUB_PYGMY_E:
        case OpenSHC::Map::Trees::TT_SHRUB_PIPE_CACTUS:
        case OpenSHC::Map::Trees::TT_SHRUB_SUCCULENT:
        case OpenSHC::Map::Trees::TT_SHRUB_CYCAD:
        case OpenSHC::Map::Trees::TT_SHRUB_PRICKLYPEAR:
            return 1;
        }
        return 0;
    }

}
}
