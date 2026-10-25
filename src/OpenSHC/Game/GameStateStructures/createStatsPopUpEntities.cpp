#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

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
            // playerSlot[0x1b] is currentAIArray[playerID]: the two arrays sit 0x1b ints apart
            // (GameSynchronyState.hpp, 0x714 - 0x6a8 = 0x6c) and the original reaches the second
            // off the induction base it walks over the first. Naming currentAIArray instead moves
            // the anchor onto it and costs the match (measured: quick_diff 0.9737 -> 0.9211), so
            // this pointer is load-bearing rather than a decompiler artefact.
            int const* const playerSlot = &DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID];
            if (playerSlot[0] == -1 && playerSlot[0x1b] == 0) {
                continue;
            }
            if (this->playerDataArray[playerID].currentResources[Resources::RT_GOLD]
                == this->playerDataArray[playerID].currentGoldDelayed) {
                continue;
            }
            this->playerDataArray[playerID].field490_0x450 += 1;
            if (this->playerDataArray[playerID].field490_0x450 < 2) {
                continue;
            }
            this->playerDataArray[playerID].currentGoldDelayed = this->playerDataArray[playerID].currentResources[Resources::RT_GOLD];
            this->playerDataArray[playerID].field490_0x450 = 0;
            if (this->playerDataArray[playerID].keep.id != 0) {
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::displayPopularityAndGoldPopups,
                    DAT_BuildingsState::ptr)(this->playerDataArray[playerID].keep.id, 0, 0, 0);
            }
        }
    }

}
}
