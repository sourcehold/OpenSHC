#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0190
    BOOLEnum AICState::teamIsWeakRelativeToEnemy(int playerID, BOOLEnum param_2)
    {
        // strength of the own team in percent of the enemy strength
        int _relativeStrength;
        if (DAT_GameState::instance.playerDataArray[playerID].totalEnemyTroopValue == 0) {
            _relativeStrength = 100;
        } else {
            _relativeStrength = DAT_GameState::instance.playerDataArray[playerID].totalTeamTroopValue * 100
                / DAT_GameState::instance.playerDataArray[playerID].totalEnemyTroopValue;
        }
        DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy = _relativeStrength;

        // the team counts as weak below a threshold that is lower with an enclosed keep
        // and much higher during the first 12000 ticks
        if (param_2) {
            if (MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkKeepEnclosed, DAT_GameState::ptr)(playerID)) {
                if (DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy >= 70)
                    return FALSE;
            } else if ((int)DAT_GameCore::instance.mapTimeInTicks < 12000) {
                if (DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy >= 300)
                    return FALSE;
            } else if (DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy >= 100) {
                return FALSE;
            }
        } else {
            // without enemy ranged troops there is no reason to become nervous
            if (DAT_GameState::instance.playerDataArray[playerID].totalEnemyRangedTroopValue < 100)
                return FALSE;
            if (MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkKeepEnclosed, DAT_GameState::ptr)(playerID)) {
                if (DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy >= 50)
                    return FALSE;
            } else if ((int)DAT_GameCore::instance.mapTimeInTicks < 12000) {
                if (DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy >= 250)
                    return FALSE;
            } else if (DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy >= 75) {
                return FALSE;
            }
        }
        return TRUE;
    }
}
}
