#include "../GreatestLord.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/UI/GreatestLord.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0044B800
    int GreatestLord::GetLowestRankedAlivePlayer()
    {
        int _aliveLordCount = 0;
        for (int _playerID = 1; _playerID < 9; ++_playerID) {
            int const _aliveLord = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(_playerID);
            if (_aliveLord != 0) {
                ++_aliveLordCount;
            }
        }
        return MACRO_CALL(OpenSHC::UI::GreatestLord_Func::GetPlayerAtRank)(_aliveLordCount - 1);
    }

}
}
