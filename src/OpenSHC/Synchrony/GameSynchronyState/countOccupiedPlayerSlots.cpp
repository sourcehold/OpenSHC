#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E890
    int GameSynchronyState::countOccupiedPlayerSlots()
    {
        int _sum = 0;
        // The original unrolls this four slots at a time, walking one pointer over currentAIArray
        // and reaching back into currentPlayerFullIDArray with a negative index. Indexing both
        // arrays by player costs part of the match but keeps every access inside its own field.
        for (int _player = 1; _player < 9; _player = _player + 1) {
            if ((this->currentPlayerFullIDArray[_player] != -1) || (this->currentAIArray[_player] != 0)) {
                _sum = _sum + 1;
            }
        }
        return _sum;
    }

}
}
