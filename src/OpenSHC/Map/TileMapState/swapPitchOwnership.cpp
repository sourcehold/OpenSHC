#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00500940
    void TileMapState::swapPitchOwnership(int param_1, int param_2)
    {
        for (int pitchDitchID = 1; pitchDitchID < 4000; pitchDitchID++) {
            if (this->pitchDitches[pitchDitchID].owner == 0) {
                continue;
            }
            if (this->pitchDitches[pitchDitchID].owner == param_1) {
                this->pitchDitches[pitchDitchID].owner = (short)param_2;
            } else if (this->pitchDitches[pitchDitchID].owner == param_2) {
                this->pitchDitches[pitchDitchID].owner = (short)param_1;
            }
        }
    }

}
}
