#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004565A0
    void GameStateStructures::setLastEncounteredTroopUnit(int playerID, int unitID)
    {
        int const enemyUnitID = DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyUnitIDUnk;
        if (playerID < 1 || playerID > 8) {
            return;
        }
        if (enemyUnitID <= 0) {
            return;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode == GM_SOLITARY) {
            return;
        }
        DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01
            = DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01 + 1;
        DAT_GameState::instance.playerDataArray[playerID].someXPosition = DAT_UnitsState::instance.units[unitID].x;
        DAT_GameState::instance.playerDataArray[playerID].someYPosition = DAT_UnitsState::instance.units[unitID].y;
        if (DAT_UnitsState::instance.units[enemyUnitID].isSelectable_OR_matchTime == 0
            || DAT_GameState::instance.mapAndTime.playerTeams[DAT_UnitsState::instance.units[enemyUnitID].owner]
                == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
            DAT_GameState::instance.playerDataArray[playerID].lastEncounteredTroopUnitID = 0;
        } else {
            DAT_GameState::instance.playerDataArray[playerID].lastEncounteredTroopUnitID = enemyUnitID;
            DAT_GameState::instance.playerDataArray[playerID].lastEncounteredTroopUnitUID
                = DAT_UnitsState::instance.units[enemyUnitID].uid;
        }
        DAT_GameState::instance.playerDataArray[playerID]
            .attackedByPlayerArrayUnk[DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID][3]
            = DAT_GameState::instance.playerDataArray[playerID]
                  .attackedByPlayerArrayUnk[DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID][3]
            + 1;
    }

}
}
