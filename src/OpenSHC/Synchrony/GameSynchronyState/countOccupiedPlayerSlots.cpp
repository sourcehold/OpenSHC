#include "../GameSynchronyState.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E890
    int GameSynchronyState::countOccupiedPlayerSlots()
    {
        int _sum = 0;
        for (int _player = 1; _player < 9; ++_player) {
            if (this->currentPlayerFullIDArray[_player] != -1) {
                ++_sum;
            } else if (this->currentAIArray[_player]) {
                ++_sum;
            }
        }
        return _sum;
    }

}
}
