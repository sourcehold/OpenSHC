#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00457F20
    void GameStateStructures::showPopAndGoldPopup()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            return;
        }
        for (int playerID = 1; playerID < 9; playerID++) {
            if (this->playerDataArray[playerID].lordKilledByPlayerID != 0) {
                continue;
            }
            if (this->playerDataArray[playerID].playerDeathRelated != 0) {
                continue;
            }
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1)
                && (DAT_GameSynchronyState::instance.currentAIArray[playerID] == 0)) {
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
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::displayPopularityAndGoldPopups,
                    DAT_BuildingsState::ptr)(this->playerDataArray[playerID].campground.id, 0, 0, 0);
            }
        }
    }
}
}
