#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Enums/CardinalDirection.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_STAIRS;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8A40
    BOOLEnum TileMapState::hasHigherNeighborWithStairs(int tileUnk, int y, int direction)
    {
        int rotatedDirection = OpenSHC::Map::Enums::CD_NORTH;
        if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {
            rotatedDirection = direction;
        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
            rotatedDirection = direction + OpenSHC::Map::Enums::MO_SOUTH;
        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_EAST) {
            rotatedDirection = direction + OpenSHC::Map::Enums::MO_EAST;
        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_WEST) {
            rotatedDirection = direction + OpenSHC::Map::Enums::MO_WEST;
        }
        if (rotatedDirection >= OpenSHC::Map::Enums::CD_UPPER_LIMIT) {
            rotatedDirection -= OpenSHC::Map::Enums::CD_UPPER_LIMIT;
        }

        int neighbour = this->directionTranslationMatrix[y][rotatedDirection] + tileUnk;
        if (this->HeightLayer[neighbour] <= this->HeightLayer[tileUnk]) {
            return FALSE;
        }
        if ((this->LogicLayer[neighbour] & L_STAIRS) != 0) {
            return TRUE;
        }
        return FALSE;
    }

}
}
