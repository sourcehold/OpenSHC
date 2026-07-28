#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/CommandBuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB5B0
    BOOLEnum AICState::shouldNotBeBuildingHovel(PlayerID playerID, Commands::CommandBuildingType param_2)
    {
        if (param_2 != Commands::CBT_HOVEL) {
            return FALSE;
        }

        int const populationCap = DAT_GameState::instance.playerDataArray[playerID].populationCap;
        if (populationCap <= 12) {
            return FALSE;
        }

        if (populationCap <= DAT_GameState::instance.playerDataArray[playerID].currentPopulation) {
            return TRUE;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].previousAvailablePeasants >= 5) {
            return TRUE;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].averagePopulationGrowthUnk >= 5) {
            return TRUE;
        }

        return DAT_GameState::instance.playerDataArray[playerID].popularity < 5000;
    }
}
}
