#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/CommandBuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB610
    BOOLEnum AICState::shouldWaitWithBuildingNegativeFearFactor(int param_1, Commands::CommandBuildingType param_2)
    {
        int* piVar1;
        switch (param_2) {
        case Commands::CBT_GALLOWS:
        case Commands::CBT_STOCKS:
        case Commands::CBT_CESSPIT1:
        case Commands::CBT_CESSPIT2:
        case Commands::CBT_CESSPIT3:
        case Commands::CBT_CESSPIT4:
        case Commands::CBT_BURNINGSTAKE:
        case Commands::CBT_GIBBET:
        case Commands::CBT_DUNGEON:
        case Commands::CBT_STRETCHINGRACK:
        case Commands::CBT_RACKFLOGGING:
        case Commands::CBT_CHOPPINGBLOCK:
        case Commands::CBT_DUNKINGSTOOL:
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
