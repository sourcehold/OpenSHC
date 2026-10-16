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
            int _dying;
            int _living;
            Tribe* _pTribe;
            int _tribeID;
            _dying = 0;
            _living = 0;
            _tribeID = 1;
            _pTribe = &DAT_TribesState::instance.tribes[1];
            do {
                if ((((_pTribe->tribeState) && (_pTribe->tribeState != 3))
                        && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_pTribe->owner] == -1))
                    && (_pTribe->attackWave == attackID)) {
                    _status = MACRO_CALL_MEMBER(
                        Map::Units::TribesState_Func::getTribeAliveStatus, DAT_TribesState::ptr)(_tribeID);
                    if (_status < 50) {
                        _living = _living + 1;
                    } else {
                        _dying = _dying + 1;
                    }
                }
                _pTribe = _pTribe + 0x19a;
                _tribeID = _tribeID + 1;
            } while ((int)_pTribe < 0x17623a0);
            if (_dying + _living == 0) {
                return (uint)(leDyingPerc < 100);
            }
            return (uint)(leDyingPerc <= (_dying * 100) / (_dying + _living));
        }

    }
}
}
