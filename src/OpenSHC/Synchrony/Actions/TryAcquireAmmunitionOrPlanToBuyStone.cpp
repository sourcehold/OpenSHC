#include "../../Synchrony.func.hpp"
#include "../Actions.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::Resources::ResourceType;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00465F20
    void Actions::TryAcquireAmmunitionOrPlanToBuyStone(int param_1, int param_2)
    {
        if (DAT_GameState::instance.playerDataArray[param_1].currentResources[4] >= 10) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                DAT_BuildingsState::ptr)(param_1, OpenSHC::Game::Resources::RT_STONE, 10, 0);
            DAT_UnitsState::instance.units[param_2].stoneAmmunition
                = DAT_UnitsState::instance.units[param_2].stoneAmmunition + 0x14;
            return;
        }
        if (((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[param_1] == -1))
            && (DAT_GameSynchronyState::instance.currentAIArray[param_1] != 0)) {
            DAT_GameState::instance.playerDataArray[param_1].resourcesToAcquireArray[4] = 10;
        }
    }

}
}
