#include "../TileMapState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8A40
    BOOLEnum TileMapState::hasHigherNeighborWithStairs(int tile, int y, int direction)
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
            rotatedDirection = rotatedDirection - 8;
        }

        int neighbour = this->directionTranslationMatrix[y][rotatedDirection] + tile;
        if (this->HeightLayer[neighbour] > this->HeightLayer[tile]) {
            return this->LogicLayer[neighbour] >> 0xb & TRUE;
        }
        return FALSE;
    }

}
}
