#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401150
        BOOLEnum EntityState::playerHasEntityOfType(int playerID, EntityType entityType)
        {
            if (entityType == ET_GOLD_POPUP) {
                if (DAT_GameState::instance.playerDataArray[playerID].someCount32 != 0) {
                    return TRUE;
                }
            } else if (entityType == ET_POPULARITY_POPUP) {
                if (DAT_GameState::instance.playerDataArray[playerID].someCount33 != 0) {
                    return static_cast<BOOLEnum>(entityType - ET_GOLD_POPUP);
                }
            }
            for (int i = 1; i < 25; ++i) {
                if (this->entityArray[i].logicalState != 0 && this->entityArray[i].entityType == entityType
                    && this->entityArray[i].owner == playerID) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
