#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500800
    int TileMapState::countUnownedPitchDitches()
    {
        int unownedPitchDitches = 0;
        for (int pitchDitchID = 0; pitchDitchID < 4000; pitchDitchID++) {
            if (this->pitchDitches[pitchDitchID].owner == 0) {
                unownedPitchDitches++;
            }
        }
        return unownedPitchDitches;
    }

}
}
