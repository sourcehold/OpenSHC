#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/CommandBuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ECA30
    BOOLEnum AICState::shouldNotBeBuildingGranary(int playerID, Commands::CommandBuildingType commandBuildingType)
    {
        if (commandBuildingType != Commands::CBT_GRANARY) {
            return FALSE;
        }
        return DAT_GameState::instance.playerDataArray[playerID].granaryIsAlmostFilledUp == FALSE;
    }
}
}
