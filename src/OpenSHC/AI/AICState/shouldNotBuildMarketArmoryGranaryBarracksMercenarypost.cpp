#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/CommandBuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB9F0
    BOOLEnum AICState::shouldNotBuildMarketArmoryGranaryBarracksMercenarypost(
        int playerID, Commands::CommandBuildingType param_2)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker < 1) {
            if ((0 < DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker)
                && (param_2 != Commands::CBT_MARKETPLACE)) {
                return param_2 != Commands::CBT_GRANARY;
            }
        } else if ((((param_2 != Commands::CBT_MARKETPLACE) && (param_2 != Commands::CBT_MERCENARYPOST))
                       && (param_2 != Commands::CBT_BARRACKS))
            && (param_2 != Commands::CBT_ARMORY)) {
            return param_2 != Commands::CBT_GRANARY;
        }
        return FALSE;
    }
}
}
