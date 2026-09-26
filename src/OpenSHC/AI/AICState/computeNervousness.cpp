#include "../AICState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D3780
    void AICState::computeNervousness(int playerID)
    {
        int troopValueNearKeep
            = DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep[playerID];
        int enemyTroopValue = DAT_GameState::instance.playerDataArray[playerID].totalEnemyTroopValue;

        int margin;
        if (enemyTroopValue < 50)
            margin = -20;
        else if (enemyTroopValue < 100)
            margin = 0;
        else if (enemyTroopValue < 200)
            margin = 20;
        else if (enemyTroopValue < 400)
            margin = 100;
        else if (enemyTroopValue < 600)
            margin = 200;
        else if (enemyTroopValue < 800)
            margin = 300;
        else
            margin = 500;

        if (troopValueNearKeep > enemyTroopValue + margin) {
            DAT_GameState::instance.playerDataArray[playerID].isNotNervousByEnemyTroopValue = 0;
            return;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].isNotNervousByEnemyTroopValue == 0) {
            if (DAT_GameState::instance.playerDataArray[playerID]
                    .totalEnemyTroopValueByPlayerID[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                > troopValueNearKeep)
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playNervous1BikFromPlayer, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playRequestHelpBikFromPlayer, this)(playerID);
        }
        DAT_GameState::instance.playerDataArray[playerID].isNotNervousByEnemyTroopValue = 1;
    }

}
}
