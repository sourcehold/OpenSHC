#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/CommandBuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB5B0
    BOOLEnum AICState::shouldNotBeBuildingHovel(PlayerID playerID, Commands::CommandBuildingType param_2)
    {
        if (param_2 == Commands::CBT_HOVEL) {
            int const populationCap = DAT_GameState::instance.playerDataArray[playerID].populationCap;
            if (12 < populationCap) {
                if (((populationCap <= DAT_GameState::instance.playerDataArray[playerID].currentPopulation)
                        && (DAT_GameState::instance.playerDataArray[playerID].previousAvailablePeasants < 5))
                    && (DAT_GameState::instance.playerDataArray[playerID].averagePopulationGrowthUnk < 5)) {
                    return DAT_GameState::instance.playerDataArray[playerID].popularity < 5000;
                }
                return TRUE;
            }
        }
        return FALSE;
    }
}
}
