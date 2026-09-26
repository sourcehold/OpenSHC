#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB610
    BOOLEnum AICState::shouldWaitWithBuildingNegativeFearFactor(int playerID, Commands::MappersEnum mapper)
    {
        switch (mapper) {
        case Commands::M_MAPPER_GALLOWS:
        case Commands::M_MAPPER_STOCKS:
        case Commands::M_MAPPER_CESS_PIT1:
        case Commands::M_MAPPER_CESS_PIT2:
        case Commands::M_MAPPER_CESS_PIT3:
        case Commands::M_MAPPER_CESS_PIT4:
        case Commands::M_MAPPER_BURNING_STAKE:
        case Commands::M_MAPPER_GIBBET:
        case Commands::M_MAPPER_DUNGEON:
        case Commands::M_MAPPER_RACK_STRETCHING:
        case Commands::M_MAPPER_RACK_FLOGGING:
        case Commands::M_MAPPER_CHOPPING_BLOCK:
        case Commands::M_MAPPER_DUNKING_STOOL:
            if (DAT_GameState::instance.playerDataArray[playerID].popularity < 5000) {
                return TRUE;
            }
            DAT_GameState::instance.playerDataArray[playerID].aivNegativeFearFactorDelay++;
            if (DAT_GameState::instance.playerDataArray[playerID].aivNegativeFearFactorDelay < 100) {
                return TRUE;
            }
            DAT_GameState::instance.playerDataArray[playerID].aivNegativeFearFactorDelay = 0;
            return FALSE;
        }
        return FALSE;
    }
}
}
