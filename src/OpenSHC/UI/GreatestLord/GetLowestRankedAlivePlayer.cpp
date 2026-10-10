#include "../GreatestLord.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/UI/GreatestLord.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0044B800
    int GreatestLord::GetLowestRankedAlivePlayer()
    {
        int _alive;
        int _total = 0;
        int _playerID = 1;
        do {
            _alive
                = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(_playerID);
            if (_alive) {
                _total = _total + 1;
            }
            _playerID = _playerID + 1;
        } while (_playerID < 9);
        _playerID = MACRO_CALL(UI::GreatestLord_Func::GetPlayerAtRank)(_total + -1);
        return _playerID;
    }

}
}
