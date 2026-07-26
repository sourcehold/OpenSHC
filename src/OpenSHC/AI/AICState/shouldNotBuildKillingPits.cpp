#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/CommandBuildingType.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ECA90
    BOOLEnum AICState::shouldNotBuildKillingPits(int playerID, Commands::CommandBuildingType commandBuildingType)
    {
        if (commandBuildingType == Commands::CBT_KILLINGPIT) {
            return (BOOLEnum)(DAT_AIVState::instance.mapExtraInfo.playerTotalKillingPits[playerID] >= 100);
        }
        return FALSE;
    }
}
}
