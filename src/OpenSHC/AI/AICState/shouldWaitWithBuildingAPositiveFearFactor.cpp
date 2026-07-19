#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/CommandBuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB700
    BOOLEnum AICState::shouldWaitWithBuildingAPositiveFearFactor(int playerID, Commands::CommandBuildingType param_2)
    {
        int* piVar1;
        switch (param_2) {
        case Commands::CBT_COMMUNAL_GARDEN1:
        case Commands::CBT_COMMUNAL_GARDEN2:
        case Commands::CBT_COMMUNAL_GARDEN3:
        case Commands::CBT_COMMUNAL_GARDEN4:
        case Commands::CBT_COMMUNAL_GARDEN5:
        case Commands::CBT_SHRUB_GARDEN6:
        case Commands::CBT_COMMUNAL_GARDEN7:
        case Commands::CBT_COMMUNAL_GARDEN8:
        case Commands::CBT_COMMUNAL_GARDEN9:
        case Commands::CBT_TOWN_GARDEN10:
        case Commands::CBT_TOWN_GARDEN11:
        case Commands::CBT_TOWN_GARDEN12:
        case Commands::CBT_MAYPOLE:
        case Commands::CBT_STATUE1:
        case Commands::CBT_STATUE2:
        case Commands::CBT_STATUE3:
        case Commands::CBT_STATUE4:
        case Commands::CBT_STATUE5:
        case Commands::CBT_SHRINE1:
        case Commands::CBT_SHRINE2:
        case Commands::CBT_SHRINE3:
        case Commands::CBT_SHRINE4:
        case Commands::CBT_SHRINE5:
        case Commands::CBT_DANCINGBEAR:
        case Commands::CBT_POND_1:
        case Commands::CBT_SMALL_POND_3:
        case Commands::CBT_LARGE_POND_3:
        case Commands::CBT_LARGE_POND_4:
            piVar1 = &DAT_GameState::instance.playerDataArray[playerID].aivPositiveFearFactorDelay;
            *piVar1 = *piVar1 + 1;
            if (DAT_GameState::instance.playerDataArray[playerID].aivPositiveFearFactorDelay < 200) {
                return TRUE;
            }
            DAT_GameState::instance.playerDataArray[playerID].aivPositiveFearFactorDelay = 0;
        }
        return FALSE;
    }
}
}
