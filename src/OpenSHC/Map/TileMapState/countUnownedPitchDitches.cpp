#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00500800
    int TileMapState::countUnownedPitchDitches()
    {
        int unownedPitchDitches = 0;
        for (int pitchDitchID = 0; pitchDitchID < countof(this->pitchDitches); pitchDitchID++) {
            if (this->pitchDitches[pitchDitchID].owner == 0) {
                unownedPitchDitches++;
            }
        }
        return unownedPitchDitches;
    }

}
}
