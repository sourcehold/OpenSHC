#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/CommandBuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ECA60
    BOOLEnum AICState::shouldNotBeBuildingArmoury(PlayerID playerID, Commands::CommandBuildingType commandBuildingType)
    {
        if (commandBuildingType != Commands::CBT_ARMORY) {
            return FALSE;
        }
        return DAT_GameState::instance.playerDataArray[playerID].isArmouryAlmostFilledUp == 0;
    }
}
}
