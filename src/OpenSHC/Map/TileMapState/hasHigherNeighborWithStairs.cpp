#include "../TileMapState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8A40
    BOOLEnum TileMapState::hasHigherNeighborWithStairs(int tileUnk, int y, int direction)
    {
        int rotatedDirection = 0;
        if (this->mapOrientation == 0) {
            rotatedDirection = direction;
        } else if (this->mapOrientation == 4) {
            rotatedDirection = direction + 4;
        } else if (this->mapOrientation == 2) {
            rotatedDirection = direction + 2;
        } else if (this->mapOrientation == 6) {
            rotatedDirection = direction + 6;
        }
        if (rotatedDirection >= 8) {
            rotatedDirection -= 8;
        }

        int neighbour = this->directionTranslationMatrix[y][rotatedDirection] + tileUnk;
        if (this->HeightLayer[neighbour] <= this->HeightLayer[tileUnk]) {
            return FALSE;
        }
        return (uint)this->LogicLayer[neighbour] >> 11 & TRUE;
    }

}
}
