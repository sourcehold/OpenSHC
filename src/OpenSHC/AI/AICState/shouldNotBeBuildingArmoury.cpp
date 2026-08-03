#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ECA60
    BOOLEnum AICState::shouldNotBeBuildingArmoury(PlayerID playerID, Commands::MappersEnum commandBuildingType)
    {
        if (commandBuildingType != Commands::M_MAPPER_ARMOURY) {
            return FALSE;
        }
        return DAT_GameState::instance.playerDataArray[playerID].isArmouryAlmostFilledUp == 0;
    }
}
}
