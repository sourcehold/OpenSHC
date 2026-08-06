#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB610
    BOOLEnum AICState::shouldWaitWithBuildingNegativeFearFactor(int param_1, Commands::MappersEnum param_2)
    {
        int* piVar1;
        switch (param_2) {
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
            if ((DAT_GameState::instance.playerDataArray[param_1].popularity < 5000)
                || (piVar1 = &DAT_GameState::instance.playerDataArray[param_1].aivNegativeFearFactorDelay,
                    *piVar1 = *piVar1 + 1,
                    DAT_GameState::instance.playerDataArray[param_1].aivNegativeFearFactorDelay < 100)) {
                return TRUE;
            }
            DAT_GameState::instance.playerDataArray[param_1].aivNegativeFearFactorDelay = 0;
        }
        return FALSE;
    }
}
}
