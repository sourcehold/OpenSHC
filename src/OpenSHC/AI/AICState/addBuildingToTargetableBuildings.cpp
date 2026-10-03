#include "../AICState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDA50
    void AICState::addBuildingToTargetableBuildings(int buildingID)
    {
        int owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)
            return;
        if (DAT_GameState::instance.playerDataArray[owner].top100TargetableBuildingsTracker >= 100)
            return;
        if (DAT_BuildingsState::instance.buildings[buildingID].fireDuration != 0)
            return;

        DAT_GameState::instance.playerDataArray[owner]
            .top100TargetableBuildings[DAT_GameState::instance.playerDataArray[owner].top100TargetableBuildingsTracker]
            = buildingID;
        DAT_GameState::instance.playerDataArray[owner].top100TargetableBuildingsTracker++;
    }

}
}
