#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
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
            // currentPlayerFullIDArray and currentAIArray are two of four parallel int[9] arrays laid out
            // back to back, so the AI flag for this player sits a constant number of ints past its slot. The
            // original walks one pointer over currentPlayerFullIDArray and reaches the AI flag off it: MSVC
            // anchors the loop pointer on whichever array is compared last, so naming currentAIArray in the
            // comparison moves the anchor onto it and costs the match (measured: quick_diff 0.9737 -> 0.9211).
            // The distance between the two arrays is constant-folded, so spelling it out this way is free and
            // cannot go stale if the layout changes.
            int const* const playerSlot = &DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID];
            int const* const playerIsAISlot = playerSlot
                + (DAT_GameSynchronyState::instance.currentAIArray
                    - DAT_GameSynchronyState::instance.currentPlayerFullIDArray);
            if (*playerSlot == -1 && *playerIsAISlot == 0) {
                continue;
            }
            if (this->playerDataArray[playerID].currentResources[Resources::RT_GOLD]
                == this->playerDataArray[playerID].currentGoldDelayed) {
                continue;
            }
            this->playerDataArray[playerID].field198_0x450 += 1;
            if (this->playerDataArray[playerID].field198_0x450 < 2) {
                continue;
            }
            this->playerDataArray[playerID].currentGoldDelayed
                = this->playerDataArray[playerID].currentResources[Resources::RT_GOLD];
            this->playerDataArray[playerID].field198_0x450 = 0;
            if (this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_KEEP].id != 0) {
                MACRO_CALL_MEMBER(
                    Map::Buildings::BuildingsState_Func::displayPopularityAndGoldPopups, DAT_BuildingsState::ptr)(
                    this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_KEEP].id, 0, 0, 0);
            }
        }
    }

}
}
