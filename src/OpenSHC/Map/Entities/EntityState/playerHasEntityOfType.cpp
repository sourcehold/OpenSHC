#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // Types 0x28/0x29 (popups, no EntityType name) return TRUE while the player's cooldown is nonzero
        // (0x401167, 0x401188). The scan covers only entity slots 1..24 (cmp edx,0x19 / jl at 0x4011C3); type and
        // owner are read with movsx (0x4011AC, 0x4011B3).
        // FUNCTION: STRONGHOLDCRUSADER 0x00401150
        BOOLEnum EntityState::playerHasEntityOfType(int playerID, EntityType entityType)
        {
            if (entityType == 0x28) {
                if (DAT_GameState::instance.playerDataArray[playerID].someCount32 != 0) {
                    return TRUE;
                }
            } else if (entityType == 0x29 && DAT_GameState::instance.playerDataArray[playerID].someCount33 != 0) {
                return TRUE;
            }
            for (int i = 1; i < 0x19; i++) {
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
