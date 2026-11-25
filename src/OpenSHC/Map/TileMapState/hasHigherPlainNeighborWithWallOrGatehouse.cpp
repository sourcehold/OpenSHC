#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Enums/CardinalDirection.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8AC0
    BOOLEnum TileMapState::hasHigherPlainNeighborWithWallOrGatehouse(int tile, int y, int direction)
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
        if ((this->LogicLayer[neighbour] & L_WALL_OR_GATEHOUSE) != 0) {
            return TRUE;
        }
        return FALSE;
    }

}
}
