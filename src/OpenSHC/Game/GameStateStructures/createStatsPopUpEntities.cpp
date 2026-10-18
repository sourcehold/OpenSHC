#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00457FD0
    void GameStateStructures::createStatsPopUpEntities()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == GM_SOLITARY) {
            return;
        }
        for (int playerID = 1; playerID < 9; ++playerID) {
            if (this->playerDataArray[playerID].lordKilledByPlayerID != 0) {
                continue;
            }
            if (this->playerDataArray[playerID].playerDeathRelated != 0) {
                continue;
            }
            // the original walks one pointer over currentPlayerFullIDArray and reaches currentAIArray off it, 27 ints
            // further on; reading the second array by name costs the induction base
            int* currentPlayerFullID = &DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID];
            if (*currentPlayerFullID == -1 && currentPlayerFullID[0x1b] == 0) {
                continue;
            }
            if (this->playerDataArray[playerID].currentResources[0xf]
                == this->playerDataArray[playerID].currentGoldDelayed) {
                continue;
            }
            this->playerDataArray[playerID].field490_0x450 += 1;
            if (this->playerDataArray[playerID].field490_0x450 < 2) {
                continue;
            }
            this->playerDataArray[playerID].currentGoldDelayed = this->playerDataArray[playerID].currentResources[0xf];
            this->playerDataArray[playerID].field490_0x450 = 0;
            if (this->playerDataArray[playerID].keep.id != 0) {
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::displayPopularityAndGoldPopups,
                    DAT_BuildingsState::ptr)(this->playerDataArray[playerID].keep.id, 0, 0, 0);
            }
        }
    }

}
}
