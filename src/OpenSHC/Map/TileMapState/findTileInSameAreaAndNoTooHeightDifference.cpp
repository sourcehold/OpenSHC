#include "../TileMapState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00500370
    BOOLEnum TileMapState::findTileInSameAreaAndNoTooHeightDifference(int area, int tile, int yUnk)
    {
        for (int attempts = 0; attempts < countof(this->directionTranslationMatrix[yUnk]); attempts++) {
            int neighbour = this->directionTranslationMatrix[yUnk][attempts] + tile;
            if (this->HeightLayer[neighbour] > this->HeightLayer[tile] + 16) {
                continue;
            }
            if (this->PathConnectionLayer[neighbour] != area) {
                continue;
            }
            return TRUE;
        }
        return FALSE;
    }

}
}
