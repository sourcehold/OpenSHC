#include "OpenSHC/AI/AICState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D3780
    void AICState ::computeNervousness(int playerID)

    {
        int _one = 1;

        int iVar1 = DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep[playerID];

        int _totalTroopValueOfEnemy = DAT_GameState::instance.playerDataArray[playerID].totalEnemyTroopValue;

        int _someCutoff;

        if (_totalTroopValueOfEnemy < 50) {
            _someCutoff = _one - 0x15;
        } else if (_totalTroopValueOfEnemy < 100) {
            _someCutoff = 0;
        } else if (_totalTroopValueOfEnemy < 200) {
            _someCutoff = 20;
        } else if (_totalTroopValueOfEnemy < 400) {
            _someCutoff = 100;
        } else if (_totalTroopValueOfEnemy < 600) {
            _someCutoff = 200;
        } else {
            _someCutoff = ((_totalTroopValueOfEnemy >= 800) - _one & 0xffffff38) + 500;
        }

        if (iVar1 > _someCutoff + _totalTroopValueOfEnemy) {
            DAT_GameState::instance.playerDataArray[playerID].isNotNervousByEnemyTroopValue = 0;
            return;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].isNotNervousByEnemyTroopValue == 0) {
            if (DAT_GameState::instance.playerDataArray[playerID]
                    .totalEnemyTroopValueByPlayerID[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                > iVar1) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playNervous1BikFromPlayer, this)(playerID);
            }
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playRequestHelpBikFromPlayer, this)(playerID);
        }

        DAT_GameState::instance.playerDataArray[playerID].isNotNervousByEnemyTroopValue = _one;
    }

}
}
