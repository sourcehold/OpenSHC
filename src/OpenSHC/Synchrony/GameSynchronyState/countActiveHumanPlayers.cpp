#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E830
    int GameSynchronyState::countActiveHumanPlayers()
    {
        uint _count = 0;
        for (int _player = 1; _player < 9; _player = _player + 1) {
            if (this->currentPlayerFullIDArray[_player] != -1) {
                _count = _count + 1;
            }
        }
        return _count;
    }

}
}
