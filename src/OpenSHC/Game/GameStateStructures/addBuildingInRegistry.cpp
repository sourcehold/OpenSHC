#include "../GameStateStructures.func.hpp"

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
    // FUNCTION: STRONGHOLDCRUSADER 0x0045AE10
    void GameStateStructures::addBuildingInRegistry(int buildingID)
    {
        int owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            return;
        }
        if (this->first500BuildingsCurrentIndexCounter[owner] >= 500) {
            return;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].fireDuration != 0) {
            return;
        }
        this->first500BuildingsPerPlayer[owner][this->first500BuildingsCurrentIndexCounter[owner]] = (short)buildingID;
        this->first500BuildingsCurrentIndexCounter[owner] = this->first500BuildingsCurrentIndexCounter[owner] + 1;
    }
}
}
