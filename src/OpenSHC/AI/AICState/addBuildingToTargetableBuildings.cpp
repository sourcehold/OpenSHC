#include "../AICState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDA50
    void AICState::addBuildingToTargetableBuildings(int buildingID)
    {
        int _player = DAT_BuildingsState::instance.buildings[buildingID].owner;
        if (DAT_GameSynchronyState::instance.DAT_CurrentGameMode != Game::GM_SOLITARY) {
            int* piVar1 = &DAT_GameState::instance.playerDataArray[_player].top100TargetableBuildingsTracker;
            if ((*piVar1 < 100) && (DAT_BuildingsState::instance.buildings[buildingID].fireDuration == 0)) {
                DAT_GameState::instance.playerDataArray[_player].top100TargetableBuildings[*piVar1] = (short)buildingID;
                *piVar1 = *piVar1 + 1;
            }
        }
    }

}
}
