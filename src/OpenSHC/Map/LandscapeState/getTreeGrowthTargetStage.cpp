#include "OpenSHC/Map/LandscapeState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2C20
    undefined4 LandscapeState::getTreeGrowthTargetStage(int treeID)
    {
        switch (this->trees[treeID].treeType) {
        case OpenSHC::Map::Trees::TT_CHESTNUT:
            switch (this->trees[treeID].stage) {
            case 0:
                return 1;
            case 1:
                return 2;
            case 2:
                return 3;
            }
            return 4;
        case OpenSHC::Map::Trees::TT_OAK:
        case OpenSHC::Map::Trees::TT_PINE:
        case OpenSHC::Map::Trees::TT_BIRCH:
            switch (this->trees[treeID].stage) {
            case 0:
                return 1;
            case 1:
                return 1;
            case 2:
                return 2;
            }
            return 3;
        case OpenSHC::Map::Trees::TT_SHRUB1A:
        case OpenSHC::Map::Trees::TT_SHRUB1B:
        case OpenSHC::Map::Trees::TT_SHRUB1C:
        case OpenSHC::Map::Trees::TT_SHRUB1D:
        case OpenSHC::Map::Trees::TT_SHRUB1E:
        case OpenSHC::Map::Trees::TT_SHRUB2A:
        case OpenSHC::Map::Trees::TT_SHRUB2B:
        case OpenSHC::Map::Trees::TT_SHRUB2C:
        case OpenSHC::Map::Trees::TT_SHRUB2D:
        case OpenSHC::Map::Trees::TT_SHRUB2E:
        case OpenSHC::Map::Trees::TT_SHRUB3A:
        case OpenSHC::Map::Trees::TT_SHRUB3B:
        case OpenSHC::Map::Trees::TT_SHRUB3C:
        case OpenSHC::Map::Trees::TT_SHRUB3D:
            return 1;
        }
        return 0;
    }

}
}
