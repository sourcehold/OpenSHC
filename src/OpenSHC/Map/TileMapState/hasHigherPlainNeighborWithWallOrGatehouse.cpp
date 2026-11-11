#include "../TileMapState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8AC0
    BOOLEnum TileMapState::hasHigherPlainNeighborWithWallOrGatehouse(int tile, int y, int direction)
    {
        int rotatedDirection = 0;
        if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {
            rotatedDirection = direction;
        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
            rotatedDirection = direction + 4;
        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_EAST) {
            rotatedDirection = direction + 2;
        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_WEST) {
            rotatedDirection = direction + 6;
        }
        if (rotatedDirection >= 8) {
            rotatedDirection -= 8;
        }

        int neighbour = this->directionTranslationMatrix[y][rotatedDirection] + tile;
        if (this->HeightLayer[neighbour] <= this->HeightLayer[tile]) {
            return FALSE;
        }
        if ((this->LogicLayer[neighbour] & L_CRENEL) != 0) {
            return FALSE;
        }
        if ((this->LogicLayer[neighbour] & L_STOCKPILEUnk) != 0) {
            return FALSE;
        }
        return (uint)this->LogicLayer[neighbour] >> 8 & TRUE;
    }

}
}
