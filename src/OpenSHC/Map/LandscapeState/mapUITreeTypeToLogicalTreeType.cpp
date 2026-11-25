#include "../LandscapeState.func.hpp"

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Trees/TreeType.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Map::Trees::TreeType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F1A60
    TreeType LandscapeState::mapUITreeTypeToLogicalTreeType(MappersEnum mapperType)
    {
        switch (mapperType) {
        case Commands::M_MAPPER_TREE_OLIVE:
            return Trees::TT_TREE_OLIVE;
        case Commands::M_MAPPER_TREE_DATE:
            return Trees::TT_TREE_DATE;
        case Commands::M_MAPPER_TREE_COCONUT:
            return Trees::TT_TREE_COCONUT;
        case Commands::M_MAPPER_TREE_CHERRY:
            return Trees::TT_TREE_CHERRY;
        case Commands::M_MAPPER_SHRUB_NEEDLE_PALM_A:
            return Trees::TT_SHRUB_NEEDLE_PALM_A;
        case Commands::M_MAPPER_SHRUB_NEEDLE_PALM_B:
            return Trees::TT_SHRUB_NEEDLE_PALM_B;
        case Commands::M_MAPPER_SHRUB_NEEDLE_PALM_C:
            return Trees::TT_SHRUB_NEEDLE_PALM_C;
        case Commands::M_MAPPER_SHRUB_NEEDLE_PALM_D:
            return Trees::TT_SHRUB_NEEDLE_PALM_D;
        case Commands::M_MAPPER_SHRUB_NEEDLE_PALM_E:
            return Trees::TT_SHRUB_NEEDLE_PALM_E;
        case Commands::M_MAPPER_SHRUB_PYGMY_A:
            return Trees::TT_SHRUB_PYGMY_A;
        case Commands::M_MAPPER_SHRUB_PYGMY_B:
            return Trees::TT_SHRUB_PYGMY_B;
        case Commands::M_MAPPER_SHRUB_PYGMY_C:
            return Trees::TT_SHRUB_PYGMY_C;
        case Commands::M_MAPPER_SHRUB_PYGMY_D:
            return Trees::TT_SHRUB_PYGMY_D;
        case Commands::M_MAPPER_SHRUB_PYGMY_E:
            return Trees::TT_SHRUB_PYGMY_E;
        case Commands::M_MAPPER_SHRUB_PIPE_CACTUS:
            return Trees::TT_SHRUB_PIPE_CACTUS;
        case Commands::M_MAPPER_SHRUB_SUCCULENT:
            return Trees::TT_SHRUB_SUCCULENT;
        case Commands::M_MAPPER_SHRUB_CYCAD:
            return Trees::TT_SHRUB_CYCAD;
        case Commands::M_MAPPER_SHRUB_PRICKLYPEAR:
            return Trees::TT_SHRUB_PRICKLYPEAR;
        default:
            return Trees::TT_DEFAULT;
        }
    }

}
}
