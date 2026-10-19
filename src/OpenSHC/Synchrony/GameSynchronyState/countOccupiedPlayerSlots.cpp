#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E890
    int GameSynchronyState::countOccupiedPlayerSlots()
    {
        int _sum = 0;
        // The original is a slot loop the compiler unrolled four at a time, which is why it walks
        // one pointer over currentAIArray and reads currentPlayerFullIDArray through a negative
        // offset from it. Writing the unroll out keeps every access inside its own field and
        // matches exactly. A plain 1..8 loop measures 27.0% and stays there under /GL and under
        // every per-file pragma lever (optimize "t" on, "s" off, "y" off, "g" on, inline_depth(1)),
        // so this compiler does not rebuild the unroll from the rolled source.
        for (int _player = 1; _player < 9; _player = _player + 4) {
            if ((this->currentPlayerFullIDArray[_player] != -1) || (this->currentAIArray[_player] != 0)) {
                _sum = _sum + 1;
            }
            if ((this->currentPlayerFullIDArray[_player + 1] != -1) || (this->currentAIArray[_player + 1] != 0)) {
                _sum = _sum + 1;
            }
            if ((this->currentPlayerFullIDArray[_player + 2] != -1) || (this->currentAIArray[_player + 2] != 0)) {
                _sum = _sum + 1;
            }
            if ((this->currentPlayerFullIDArray[_player + 3] != -1) || (this->currentAIArray[_player + 3] != 0)) {
                _sum = _sum + 1;
            }
        }
        return _sum;
    }

}
}
