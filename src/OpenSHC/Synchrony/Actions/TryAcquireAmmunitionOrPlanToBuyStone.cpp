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

    using Game::GameMode;
    using Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00465F20
    void Actions::TryAcquireAmmunitionOrPlanToBuyStone(int param_1, int param_2)
    {
        short* psVar1;
        if (9 < DAT_GameState::instance.playerDataArray[param_1].currentResources[4]) {
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(
                param_1, Game::Resources::RT_STONE, 10, 0);
            psVar1 = &DAT_UnitsState::instance.units[param_2].stoneAmmunition;
            *psVar1 = *psVar1 + 0x14;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
            && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[param_1] == -1
            && DAT_GameSynchronyState::instance.currentAIArray[param_1] != 0) {
            DAT_GameState::instance.playerDataArray[param_1].resourcesToAcquireArray[4] = 10;
        }
    }

}
}
