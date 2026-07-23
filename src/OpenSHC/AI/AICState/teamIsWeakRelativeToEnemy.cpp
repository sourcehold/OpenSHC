#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0190
    BOOLEnum AICState::teamIsWeakRelativeToEnemy(int playerID, BOOLEnum param_2)
    {
        short _relativeStrength;
        int _totalEnemyTroopValue = DAT_GameState::instance.playerDataArray[playerID].totalEnemyTroopValue;
        if (_totalEnemyTroopValue == 0) {
            _relativeStrength = 100;
        } else {
            _relativeStrength = (short)((DAT_GameState::instance.playerDataArray[playerID].totalTeamTroopValue * 100)
                / _totalEnemyTroopValue);
        }
        DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy = _relativeStrength;
        if (param_2 == FALSE) {
            if (DAT_GameState::instance.playerDataArray[playerID].totalEnemyRangedTroopValue < 100) {
                return FALSE;
            }
            BOOLEnum BVar2
                = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkKeepEnclosed, DAT_GameState::ptr)(playerID);
            if (BVar2 != FALSE) {
                if (DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy < 50) {
                    return TRUE;
                }
                return FALSE;
            }
            if ((int)DAT_GameCore::instance.mapTimeInTicks < 12000) {
                if (DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy < 250) {
                    return TRUE;
                }
                return FALSE;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy < 75) {
                return TRUE;
            }
        } else {
            BOOLEnum BVar2
                = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkKeepEnclosed, DAT_GameState::ptr)(playerID);
            if (BVar2 != FALSE) {
                if (DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy < 0x46) {
                    return TRUE;
                }
                return FALSE;
            }
            if ((int)DAT_GameCore::instance.mapTimeInTicks < 12000) {
                if (DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy < 300) {
                    return TRUE;
                }
                return FALSE;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy < 100) {
                return TRUE;
            }
        }
        return FALSE;
    }
}
}
