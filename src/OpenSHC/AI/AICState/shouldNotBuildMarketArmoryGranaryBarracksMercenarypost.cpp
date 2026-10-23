#include "../AICState.func.hpp"

#include "OpenSHC/Commands/MappersEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB9F0
    BOOLEnum AICState::shouldNotBuildMarketArmoryGranaryBarracksMercenarypost(
        int playerID, Commands::MappersEnum mapper)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker > 0) {
            // nervous: reject market/mercenarypost/barracks/armory types
            if (mapper != Commands::M_MAPPER_TRADEPOST && mapper != Commands::M_MAPPER_BARRACKS_EURO
                && mapper != Commands::M_MAPPER_BARRACKS_ARAB && mapper != Commands::M_MAPPER_ARMOURY) {
                return mapper != Commands::M_MAPPER_GRANARY;
            }
        } else {
            // not nervous: only reject if destroy tracker > 0 and not marketplace
            if (DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker > 0
                && mapper != Commands::M_MAPPER_TRADEPOST) {
                return mapper != Commands::M_MAPPER_GRANARY;
            }
        }
        return FALSE;
    }
}
}
