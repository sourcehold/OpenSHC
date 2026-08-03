#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ECA90
    BOOLEnum AICState::shouldNotBuildKillingPits(int playerID, Commands::MappersEnum commandBuildingType)
    {
        if (commandBuildingType == Commands::M_MAPPER_KILLING_PIT) {
            return (BOOLEnum)(DAT_AIVState::instance.mapExtraInfo.playerTotalKillingPits[playerID] >= 100);
        }
        return FALSE;
    }
}
}
