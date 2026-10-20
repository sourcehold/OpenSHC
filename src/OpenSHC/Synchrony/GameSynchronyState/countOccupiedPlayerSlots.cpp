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
        // matches exactly: this compiler will not rebuild the unroll from rolled source, under /GL
        // or under any per-file pragma lever (optimize "t" on, "s" off, "y" off, "g" on,
        // inline_depth(1)). Measured as quick_diff ratios against this form's 0.967: a plain 1..8
        // loop 0.384, 0..7 with a +1 on every index 0.384, the same body as a while loop with the
        // counter outside 0.384, a `_sum +=` on the condition 0.351, a do-while 0.333, and even a
        // two-at-a-time unroll only 0.520.
        for (int _player = 1; _player < 9; _player += 4) {
            if ((this->currentPlayerFullIDArray[_player] != -1) || (this->currentAIArray[_player] != 0)) {
                ++_sum;
            }
            if ((this->currentPlayerFullIDArray[_player + 1] != -1) || (this->currentAIArray[_player + 1] != 0)) {
                ++_sum;
            }
            if ((this->currentPlayerFullIDArray[_player + 2] != -1) || (this->currentAIArray[_player + 2] != 0)) {
                ++_sum;
            }
            if ((this->currentPlayerFullIDArray[_player + 3] != -1) || (this->currentAIArray[_player + 3] != 0)) {
                ++_sum;
            }
        }
        return _sum;
    }

}
}
