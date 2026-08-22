#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB700
    BOOLEnum AICState::shouldWaitWithBuildingAPositiveFearFactor(int playerID, Commands::MappersEnum param_2)
    {
        switch (param_2) {
        case Commands::M_MAPPER_GARDEN1:
        case Commands::M_MAPPER_GARDEN2:
        case Commands::M_MAPPER_GARDEN3:
        case Commands::M_MAPPER_GARDEN4:
        case Commands::M_MAPPER_GARDEN5:
        case Commands::M_MAPPER_GARDEN6:
        case Commands::M_MAPPER_GARDEN7:
        case Commands::M_MAPPER_GARDEN8:
        case Commands::M_MAPPER_GARDEN9:
        case Commands::M_MAPPER_GARDEN10:
        case Commands::M_MAPPER_GARDEN11:
        case Commands::M_MAPPER_GARDEN12:
        case Commands::M_MAPPER_MAYPOLE:
        case Commands::M_MAPPER_STATUE1:
        case Commands::M_MAPPER_STATUE2:
        case Commands::M_MAPPER_STATUE3:
        case Commands::M_MAPPER_STATUE4:
        case Commands::M_MAPPER_STATUE5:
        case Commands::M_MAPPER_SHRINE1:
        case Commands::M_MAPPER_SHRINE2:
        case Commands::M_MAPPER_SHRINE3:
        case Commands::M_MAPPER_SHRINE4:
        case Commands::M_MAPPER_SHRINE5:
        case Commands::M_MAPPER_DANCING_BEAR:
        case Commands::M_MAPPER_POND1:
        case Commands::M_MAPPER_POND2_SMALL:
        case Commands::M_MAPPER_POND3_LARGE1:
        case Commands::M_MAPPER_POND4_LARGE2:
            DAT_GameState::instance.playerDataArray[playerID].aivPositiveFearFactorDelay += 1;
            if (DAT_GameState::instance.playerDataArray[playerID].aivPositiveFearFactorDelay < 200) {
                return TRUE;
            }
            DAT_GameState::instance.playerDataArray[playerID].aivPositiveFearFactorDelay = 0;
        }
        return FALSE;
    }
}
}
