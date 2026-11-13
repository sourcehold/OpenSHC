#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00500850
    int TileMapState::getPitchDitchIDForTile(int tile)
    {
        for (int pitchDitchID = 1; pitchDitchID < this->maxPitchDitchCount; pitchDitchID++) {
            if (this->pitchDitches[pitchDitchID].owner != 0 && tile == this->pitchDitches[pitchDitchID].tile) {
                return pitchDitchID;
            }
        }
        return 0;
    }

}
}
