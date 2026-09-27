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
    // FUNCTION: STRONGHOLDCRUSADER 0x00458070
    void GameStateStructures::displayPlayerTradeVisualEffect(
        int playerID, int param_2, int amount, undefined4 resourceType)
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            return;
        }
        if (this->playerDataArray[playerID].lordKilledByPlayerID != 0) {
            return;
        }
        if (this->playerDataArray[playerID].playerDeathRelated != 0) {
            return;
        }
        if (this->playerDataArray[playerID].marketplace.id == 0) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::displayPopularityAndGoldPopups,
            DAT_BuildingsState::ptr)(this->playerDataArray[playerID].marketplace.id, param_2, amount, resourceType);
    }
}
}
