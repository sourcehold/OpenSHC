#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/CommandBuildingType.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ECA90
    BOOLEnum AICState::shouldNotBuildKillingPits(int playerID, Commands::CommandBuildingType commandBuildingType)
    {
        BOOLEnum _totalAbove99 = FALSE;
        if (commandBuildingType == Commands::CBT_KILLINGPIT) {
            _totalAbove99 = (BOOLEnum)(DAT_AIVState::instance.mapExtraInfo.playerTotalKillingPits[playerID] >= 100);
        }
        return _totalAbove99;
    }
}
}
