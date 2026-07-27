#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CFFD0
    BOOLEnum AICState::hasNoTroopsOrAllAreDiggers(int playerID)
    {
        int _totalTroops;
        int _halfOfDiggingTroops;

        // reversed order to match orig
        int _totalMisc = DAT_GameState::instance.playerDataArray[playerID].totalAssassinTroops
            + DAT_GameState::instance.playerDataArray[playerID].totalUnit2Troops
            + DAT_GameState::instance.playerDataArray[playerID].totalUnitPatrolTroops;
        _halfOfDiggingTroops = 0;
        if (DAT_GameState::instance.playerDataArray[playerID].aiPlayerState == 6) {
            _totalMisc += DAT_GameState::instance.playerDataArray[playerID].totalDiggingUnitTroops;
            int _attackTicker = DAT_GameState::instance.playerDataArray[playerID].attackTicker;
            int _backup;
            if (_attackTicker > 0x10) {
                int _bp = DAT_GameState::instance.playerDataArray[playerID].totalUnitBackupTroops;
                _backup = (_bp + (_bp >> 0x1f & 7)) >> 3;
            } else {
                _backup = DAT_GameState::instance.playerDataArray[playerID].totalUnitBackupTroops;
            }
            _totalMisc += _backup;
            _totalTroops = _totalMisc
                + DAT_GameState::instance.playerDataArray[playerID].totalUnitEngageTroops
                + DAT_GameState::instance.playerDataArray[playerID].totalUnitSiegeDefTroops
                + DAT_GameState::instance.playerDataArray[playerID].totalMaxDefaultTroops;
        } else {
            int _digging = DAT_GameState::instance.playerDataArray[playerID].totalDiggingUnitTroops;
            _halfOfDiggingTroops = _digging / 2;
            int _attackTicker = DAT_GameState::instance.playerDataArray[playerID].attackTicker;
            int _backup;
            if (_attackTicker > 0xc) {
                int _bp2 = DAT_GameState::instance.playerDataArray[playerID].totalUnitBackupTroops;
                _backup = (_bp2 + (_bp2 >> 0x1f & 7)) >> 3;
            } else {
                _backup = DAT_GameState::instance.playerDataArray[playerID].totalUnitBackupTroops;
            }
            _totalMisc += _backup;
            _totalTroops = _totalMisc
                + DAT_GameState::instance.playerDataArray[playerID].totalUnitEngageTroops
                + DAT_GameState::instance.playerDataArray[playerID].totalUnitSiegeDefTroops
                + DAT_GameState::instance.playerDataArray[playerID].totalMaxDefaultTroops;
        }
        if ((1 < _totalTroops) && ((4 < _totalTroops) || (_halfOfDiggingTroops <= _totalTroops + _totalTroops))) {
            return FALSE;
        }
        return TRUE;
    }
}
}
