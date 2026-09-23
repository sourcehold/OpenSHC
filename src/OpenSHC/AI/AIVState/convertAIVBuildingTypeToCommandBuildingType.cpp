#include "../AIVState.func.hpp"

#include "OpenSHC/Globals/DAT_AIVDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ECFE0
    MappersEnum AIVState::convertAIVBuildingTypeToCommandBuildingType(AIVBuildingType2 aivBuildingType)
    {
        switch (aivBuildingType) {
        case AIV::AIVBT_HIGH_WALL:
            return Commands::M_MAPPER_WALL;
        case AIV::AIVBT_LOW_WALL:
            return Commands::M_MAPPER_WOODWALL;
        case AIV::AIVBT_CRENEL:
            return Commands::M_MAPPER_CRENAL;
        case AIV::AIVBT_LOW_CRENEL:
            return Commands::M_MAPPER_CRENAL2;
        case AIV::AIVBT_STAIRS_1:
            return Commands::M_MAPPER_STAIR1;
        case AIV::AIVBT_STAIRS_2:
            return Commands::M_MAPPER_STAIR2;
        case AIV::AIVBT_STAIRS_3:
            return Commands::M_MAPPER_STAIR3;
        case AIV::AIVBT_STAIRS_4:
            return Commands::M_MAPPER_STAIR4;
        case AIV::AIVBT_STAIRS_5:
            return Commands::M_MAPPER_STAIR5;
        case AIV::AIVBT_STAIRS_6Unk:
            return Commands::M_MAPPER_STAIR6;
        case AIV::AIVBT_MOAT_A:
        case AIV::AIVBT_MOAT_B:
        case AIV::AIVBT_MOAT_C:
        case AIV::AIVBT_MOAT_D:
            return Commands::M_MAPPER_MOAT;
        case AIV::AIVBT_PITCHDITCH_2:
            return Commands::M_MAPPER_PITCH_DITCH;
        }
        // all other buildings are looked up in a table starting at the first tower
        if (aivBuildingType < AIV::AIVBT_TOWER1 || aivBuildingType > AIV::AIVBT_TOWER1 + 79) {
            return Commands::M_MAPPER_GENERIC;
        }
        return DAT_AIVDefinedData::instance.field21_0xf4[aivBuildingType - AIV::AIVBT_TOWER1];
    }

}
}
