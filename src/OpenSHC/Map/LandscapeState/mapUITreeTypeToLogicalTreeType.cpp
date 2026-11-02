#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F1A60
    undefined4 LandscapeState::mapUITreeTypeToLogicalTreeType(undefined4 uiTreeType)
    {
        switch (uiTreeType) {
        case OpenSHC::Commands::M_MAPPER_CHESTNUT:
            return OpenSHC::Map::Trees::TT_CHESTNUT;
        case OpenSHC::Commands::M_MAPPER_OAK:
            return OpenSHC::Map::Trees::TT_OAK;
        case OpenSHC::Commands::M_MAPPER_PINE:
            return OpenSHC::Map::Trees::TT_PINE;
        case OpenSHC::Commands::M_MAPPER_BIRCH:
            return OpenSHC::Map::Trees::TT_BIRCH;
        case OpenSHC::Commands::M_MAPPER_SHRUB1A:
            return OpenSHC::Map::Trees::TT_SHRUB1A;
        case OpenSHC::Commands::M_MAPPER_SHRUB1B:
            return OpenSHC::Map::Trees::TT_SHRUB1B;
        case OpenSHC::Commands::M_MAPPER_SHRUB1C:
            return OpenSHC::Map::Trees::TT_SHRUB1C;
        case OpenSHC::Commands::M_MAPPER_SHRUB1D:
            return OpenSHC::Map::Trees::TT_SHRUB1D;
        case OpenSHC::Commands::M_MAPPER_SHRUB1E:
            return OpenSHC::Map::Trees::TT_SHRUB1E;
        case OpenSHC::Commands::M_MAPPER_SHRUB2A:
            return OpenSHC::Map::Trees::TT_SHRUB2A;
        case OpenSHC::Commands::M_MAPPER_SHRUB2B:
            return OpenSHC::Map::Trees::TT_SHRUB2B;
        case OpenSHC::Commands::M_MAPPER_SHRUB2C:
            return OpenSHC::Map::Trees::TT_SHRUB2C;
        case OpenSHC::Commands::M_MAPPER_SHRUB2D:
            return OpenSHC::Map::Trees::TT_SHRUB2D;
        case OpenSHC::Commands::M_MAPPER_SHRUB2E:
            return OpenSHC::Map::Trees::TT_SHRUB2E;
        case OpenSHC::Commands::M_MAPPER_SHRUB3A:
            return OpenSHC::Map::Trees::TT_SHRUB3A;
        case OpenSHC::Commands::M_MAPPER_SHRUB3B:
            return OpenSHC::Map::Trees::TT_SHRUB3B;
        case OpenSHC::Commands::M_MAPPER_SHRUB3C:
            return OpenSHC::Map::Trees::TT_SHRUB3C;
        case OpenSHC::Commands::M_MAPPER_SHRUB3D:
            return OpenSHC::Map::Trees::TT_SHRUB3D;
        default:
            return OpenSHC::Map::Trees::TT_DEFAULT;
        }
    }

}
}
