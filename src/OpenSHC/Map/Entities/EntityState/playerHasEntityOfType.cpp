#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401150
        BOOLEnum EntityState::playerHasEntityOfType(int playerID, EntityType entityType)
        {
            if (entityType == 40) {
                if (DAT_GameState::instance.playerDataArray[playerID].someCount32 != 0) {
                    return TRUE;
                }
            } else if (entityType == 41 && DAT_GameState::instance.playerDataArray[playerID].someCount33 != 0) {
                return TRUE;
            }
            for (int i = 1; i < 25; i++) {
                if (this->entityArray[i].logicalState != 0 && this->entityArray[i].entityType == entityType
                    && this->entityArray[i].owner == playerID) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
