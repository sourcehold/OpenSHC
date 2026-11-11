#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00500940
    void TileMapState::swapPitchOwnership(int playerID, int otherPlayerID)
    {
        for (int pitchDitchID = 1; pitchDitchID < countof(this->pitchDitches); pitchDitchID++) {
            if (this->pitchDitches[pitchDitchID].owner == 0) {
                continue;
            }
            if (this->pitchDitches[pitchDitchID].owner == playerID) {
                this->pitchDitches[pitchDitchID].owner = otherPlayerID;
            } else if (this->pitchDitches[pitchDitchID].owner == otherPlayerID) {
                this->pitchDitches[pitchDitchID].owner = playerID;
            }
        }
    }

}
}
