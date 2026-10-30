#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

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
            int* currentPlayerFullID = &DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID];
            if (*currentPlayerFullID == -1 && currentPlayerFullID[0x1b] == 0) {
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
            if (this->playerDataArray[playerID].campground.id != 0) {
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::displayPopularityAndGoldPopups,
                    DAT_BuildingsState::ptr)(this->playerDataArray[playerID].campground.id, 0, 0, 0);
            }
        }
    }

}
}
