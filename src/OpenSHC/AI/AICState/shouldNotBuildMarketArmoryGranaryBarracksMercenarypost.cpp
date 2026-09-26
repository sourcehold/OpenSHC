#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB9F0
    BOOLEnum AICState::shouldNotBuildMarketArmoryGranaryBarracksMercenarypost(
        int playerID, Commands::MappersEnum param_2)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker > 0) {
            // nervous: reject market/mercenarypost/barracks/armory types
            if (param_2 != Commands::M_MAPPER_TRADEPOST && param_2 != Commands::M_MAPPER_BARRACKS_ARAB
                && param_2 != Commands::M_MAPPER_BARRACKS_EURO && param_2 != Commands::M_MAPPER_ARMOURY) {
                return param_2 != Commands::M_MAPPER_GRANARY;
            }
        } else {
            // not nervous: only reject if destroy tracker > 0 and not marketplace
            if (DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker > 0
                && param_2 != Commands::M_MAPPER_TRADEPOST) {
                return param_2 != Commands::M_MAPPER_GRANARY;
            }
        }
        return FALSE;
    }
}
}
