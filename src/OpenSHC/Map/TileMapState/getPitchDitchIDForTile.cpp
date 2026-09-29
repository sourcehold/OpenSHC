#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
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
