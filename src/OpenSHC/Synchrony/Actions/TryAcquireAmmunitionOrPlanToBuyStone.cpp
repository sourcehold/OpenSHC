#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00465F20
    void Actions::TryAcquireAmmunitionOrPlanToBuyStone(int playerID, int unitID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_STONE] >= 10) {
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(
                playerID, Game::Resources::RT_STONE, 10, 0);
            DAT_UnitsState::instance.units[unitID].stoneAmmunition += 20;
        } else if (DAT_GameSynchronyState::instance.currentGameMode != 0
            && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
            && DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
            DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[Game::Resources::RT_STONE] = 10;
        }
    }

}
}
