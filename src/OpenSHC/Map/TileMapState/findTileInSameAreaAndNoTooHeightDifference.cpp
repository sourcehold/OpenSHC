#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00500370
    BOOLEnum TileMapState::findTileInSameAreaAndNoTooHeightDifference(int area, int tile, int row)
    {
        int direction = 0;
        int* neighborOffset = this->directionTranslationMatrix[row];
        for (; direction < 8; ++direction, ++neighborOffset) {
            int neighborTile = tile + *neighborOffset;
            // This is an existence check, not a route search. Lower neighbors have
            // no height restriction; a neighbor may be at most 16 units higher.
            if (this->HeightLayer[neighborTile] <= this->HeightLayer[tile] + 16 &&
                static_cast<short>(this->PathConnectionLayer[neighborTile]) == area) {
                return TRUE;
            }
        }
        return FALSE;
    }

} // namespace Map
} // namespace OpenSHC
