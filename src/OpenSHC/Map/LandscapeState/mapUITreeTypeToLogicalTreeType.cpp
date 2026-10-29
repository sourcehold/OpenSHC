#include "OpenSHC/Map/LandscapeState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F1A60
    undefined4 LandscapeState::mapUITreeTypeToLogicalTreeType(undefined4 uiTreeType)
    {
        switch (uiTreeType) {
        case 0x28:
            return OpenSHC::Map::Trees::TT_CHESTNUT;
        case 0x29:
            return OpenSHC::Map::Trees::TT_OAK;
        case 0x2A:
            return OpenSHC::Map::Trees::TT_PINE;
        case 0x2B:
            return OpenSHC::Map::Trees::TT_BIRCH;
        case 0x82:
            return OpenSHC::Map::Trees::TT_SHRUB1A;
        case 0x83:
            return OpenSHC::Map::Trees::TT_SHRUB1B;
        case 0x84:
            return OpenSHC::Map::Trees::TT_SHRUB1C;
        case 0x85:
            return OpenSHC::Map::Trees::TT_SHRUB1D;
        case 0x86:
            return OpenSHC::Map::Trees::TT_SHRUB1E;
        case 0x87:
            return OpenSHC::Map::Trees::TT_SHRUB2A;
        case 0x88:
            return OpenSHC::Map::Trees::TT_SHRUB2B;
        case 0x89:
            return OpenSHC::Map::Trees::TT_SHRUB2C;
        case 0x8A:
            return OpenSHC::Map::Trees::TT_SHRUB2D;
        case 0x8B:
            return OpenSHC::Map::Trees::TT_SHRUB2E;
        case 0x99:
            return OpenSHC::Map::Trees::TT_SHRUB3A;
        case 0x9A:
            return OpenSHC::Map::Trees::TT_SHRUB3B;
        case 0x9B:
            return OpenSHC::Map::Trees::TT_SHRUB3C;
        case 0x9C:
            return OpenSHC::Map::Trees::TT_SHRUB3D;
        default:
            return OpenSHC::Map::Trees::TT_DEFAULT;
        }
    }

}
}
