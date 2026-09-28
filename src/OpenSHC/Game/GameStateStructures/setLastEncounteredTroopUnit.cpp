#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

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
    // FUNCTION: STRONGHOLDCRUSADER 0x004565A0
    uint GameStateStructures::setLastEncounteredTroopUnit(int playerID, int unitID)
    {
        uint result = playerID - 1;
        int enemyUnitID = DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyUnitIDUnk;
        if ((result <= 7) && (enemyUnitID > 0)
            && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)) {
            DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01
                = DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01 + 1;
            DAT_GameState::instance.playerDataArray[playerID].someXPosition
                = DAT_UnitsState::instance.units[unitID].x;
            DAT_GameState::instance.playerDataArray[playerID].someYPosition
                = DAT_UnitsState::instance.units[unitID].y;
            if ((DAT_UnitsState::instance.units[enemyUnitID].isSelectable_OR_matchTime == 0)
                || (DAT_GameState::instance.mapAndTime
                        .playerTeams[DAT_UnitsState::instance.units[enemyUnitID].owner]
                    == DAT_GameState::instance.mapAndTime.playerTeams[playerID])) {
                DAT_GameState::instance.playerDataArray[playerID].lastEncounteredTroopUnitID = 0;
            } else {
                DAT_GameState::instance.playerDataArray[playerID].lastEncounteredTroopUnitID = enemyUnitID;
                DAT_GameState::instance.playerDataArray[playerID].lastEncounteredTroopUnitUID
                    = DAT_UnitsState::instance.units[enemyUnitID].uid;
            }
            DAT_GameState::instance.playerDataArray[playerID].unusedEnemyAttackTracker
                [DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID][0]
                = DAT_GameState::instance.playerDataArray[playerID].unusedEnemyAttackTracker
                      [DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID][0]
                + 1;
            result = (uint)&DAT_GameState::instance.playerDataArray[playerID].unusedEnemyAttackTracker
                          [DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID][0];
        }
        return result;
    }
}
}
