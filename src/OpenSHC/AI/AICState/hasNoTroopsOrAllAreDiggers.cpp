#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CFFD0
    BOOLEnum AICState::hasNoTroopsOrAllAreDiggers(int playerID)
    {
        int _totalBackup;
        int _totalBackup2;
        int _total1;
        int _totalTroops;
        int _halfOfDiggingTroops;
        int _totalBackupLate;
        int _totalBackupLate2;

        _total1 = DAT_GameState::instance.playerDataArray[playerID].totalUnitPatrolTroops
            + DAT_GameState::instance.playerDataArray[playerID].totalUnit2Troops
            + DAT_GameState::instance.playerDataArray[playerID].totalAssassinTroops;
        _halfOfDiggingTroops = 0;
        if (DAT_GameState::instance.playerDataArray[playerID].aiPlayerState == 6) {
            if (DAT_GameState::instance.playerDataArray[playerID].attackTicker < 17) {
                _totalBackup = DAT_GameState::instance.playerDataArray[playerID].totalUnitBackupTroops;
            } else {
                _totalBackupLate = DAT_GameState::instance.playerDataArray[playerID].totalUnitBackupTroops;
                _totalBackup = (int)(_totalBackupLate + (_totalBackupLate >> 0x1f & 7U)) >> 3;
            }
            _totalTroops = _total1 + DAT_GameState::instance.playerDataArray[playerID].totalDiggingUnitTroops
                + _totalBackup + DAT_GameState::instance.playerDataArray[playerID].totalMaxDefaultTroops
                + DAT_GameState::instance.playerDataArray[playerID].totalUnitSiegeDefTroops
                + DAT_GameState::instance.playerDataArray[playerID].totalUnitEngageTroops;
        } else {
            _halfOfDiggingTroops = DAT_GameState::instance.playerDataArray[playerID].totalDiggingUnitTroops / 2;
            if (DAT_GameState::instance.playerDataArray[playerID].attackTicker < 13) {
                _totalBackup2 = DAT_GameState::instance.playerDataArray[playerID].totalUnitBackupTroops;
            } else {
                _totalBackupLate2 = DAT_GameState::instance.playerDataArray[playerID].totalUnitBackupTroops;
                _totalBackup2 = (int)(_totalBackupLate2 + (_totalBackupLate2 >> 0x1f & 7U)) >> 3;
            }
            _totalTroops = _total1 + _totalBackup2
                + DAT_GameState::instance.playerDataArray[playerID].totalMaxDefaultTroops
                + DAT_GameState::instance.playerDataArray[playerID].totalUnitSiegeDefTroops
                + DAT_GameState::instance.playerDataArray[playerID].totalUnitEngageTroops;
        }
        if ((1 < _totalTroops) && ((4 < _totalTroops || (_halfOfDiggingTroops <= _totalTroops * 2)))) {
            return FALSE;
        }
        return TRUE;
    }
}
}
