#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00518BB0
        BOOLEnum TroopValueState::isLessThanPercentageOfTribesInAttackDying(int attackID, int leDyingPerc)
        {
            int _status;
            int _dying = 0;
            int _living = 0;
            for (int _tribeID = 1; _tribeID < 1250; _tribeID = _tribeID + 1) {
                if (DAT_TribesState::instance.tribes[_tribeID].tribeState && DAT_TribesState::instance.tribes[_tribeID].tribeState != 3
                    && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_TribesState::instance.tribes[_tribeID].owner] == -1
                    && DAT_TribesState::instance.tribes[_tribeID].attackWave == attackID) {
                    _status = MACRO_CALL_MEMBER(
                        Map::Units::TribesState_Func::getTribeAliveStatus, DAT_TribesState::ptr)(_tribeID);
                    if (_status < 50) {
                        _living = _living + 1;
                    } else {
                        _dying = _dying + 1;
                    }
                }
            }
            int _dyingPercentage;
            if (_dying + _living == 0) {
                _dyingPercentage = 100;
            } else {
                _dyingPercentage = (_dying * 100) / (_dying + _living);
            }
            return (uint)(_dyingPercentage >= leDyingPerc);
        }

    }
}
}
