#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00457F20
    void GameStateStructures::showPopAndGoldPopup()
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
            // This function is at 100%, and this is what keeps it there. currentPlayerFullIDArray and
            // currentAIArray are two of four parallel int[9] arrays laid out back to back, so the AI flag for
            // this player sits a constant number of ints past its slot, and the original reaches it off the one
            // pointer it walks over currentPlayerFullIDArray. MSVC anchors the loop pointer on whichever array
            // is compared last, so naming currentAIArray in the comparison moves the anchor onto it: the plain
            // `currentAIArray[playerID] == 0` form was re-measured and costs 11 points (reccmp 100.0 -> 88.9,
            // normalized 100.0 -> 87.2). The distance between the two arrays is constant-folded, so spelling it
            // out this way is free and cannot go stale if the layout changes.
            int const* const playerSlot = &DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID];
            int const* const playerIsAISlot = playerSlot
                + (DAT_GameSynchronyState::instance.currentAIArray
                    - DAT_GameSynchronyState::instance.currentPlayerFullIDArray);
            if (*playerSlot == -1 && *playerIsAISlot == 0) {
                continue;
            }
            if (this->playerDataArray[playerID].popularity / 100
                == this->playerDataArray[playerID].popularityAtWeekTick100) {
                continue;
            }
            this->playerDataArray[playerID].counterTrackingPopGoldPopup += 1;
            if (this->playerDataArray[playerID].counterTrackingPopGoldPopup < 2) {
                continue;
            }
            this->playerDataArray[playerID].popularityAtWeekTick100 = this->playerDataArray[playerID].popularity / 100;
            this->playerDataArray[playerID].counterTrackingPopGoldPopup = 0;
            if (this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_CAMPGROUND].id != 0) {
                MACRO_CALL_MEMBER(
                    Map::Buildings::BuildingsState_Func::displayPopularityAndGoldPopups, DAT_BuildingsState::ptr)(
                    this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_CAMPGROUND].id, 0, 0, 0);
            }
        }
    }

}
}
