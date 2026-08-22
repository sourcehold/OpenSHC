#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ECAB0
    BOOLEnum AICState::mapperIsWoodCuttersHutWhileNoWoodAvailable(
        undefined4 playerID, Commands::MappersEnum commandBuildingType)
    {
        return ((commandBuildingType == Commands::M_MAPPER_WOODSMAN)
            && (DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable <= 0));
    }
}
}
