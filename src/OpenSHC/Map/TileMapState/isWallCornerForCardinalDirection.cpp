#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Enums/CardinalDirection.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F86D0
    BOOLEnum TileMapState::isWallCornerForCardinalDirection(int tile, int y, int direction)
    {
        int first = OpenSHC::Map::Enums::CD_NORTH;
        int second = OpenSHC::Map::Enums::CD_NORTH;
        int third = OpenSHC::Map::Enums::CD_NORTH;
        int fourth = OpenSHC::Map::Enums::CD_NORTH;
        if (direction == OpenSHC::Map::Enums::CD_NORTH) {
            first = OpenSHC::Map::Enums::CD_NORTH;
            second = OpenSHC::Map::Enums::CD_SOUTH;
            third = OpenSHC::Map::Enums::CD_EAST;
            fourth = OpenSHC::Map::Enums::CD_WEST;
        } else if (direction == OpenSHC::Map::Enums::CD_EAST) {
            first = OpenSHC::Map::Enums::CD_EAST;
            second = OpenSHC::Map::Enums::CD_WEST;
            third = OpenSHC::Map::Enums::CD_NORTH;
            fourth = OpenSHC::Map::Enums::CD_SOUTH;
        } else if (direction == OpenSHC::Map::Enums::CD_SOUTH) {
            first = OpenSHC::Map::Enums::CD_NORTH;
            second = OpenSHC::Map::Enums::CD_SOUTH;
            third = OpenSHC::Map::Enums::CD_EAST;
            fourth = OpenSHC::Map::Enums::CD_WEST;
        } else if (direction == OpenSHC::Map::Enums::CD_WEST) {
            first = OpenSHC::Map::Enums::CD_EAST;
            second = OpenSHC::Map::Enums::CD_WEST;
            third = OpenSHC::Map::Enums::CD_NORTH;
            fourth = OpenSHC::Map::Enums::CD_SOUTH;
        }

        if ((this->LogicLayer[this->directionTranslationMatrix[y][first] + tile] & L_CRENEL) == 0) {
            return FALSE;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][second] + tile] & L_CRENEL) == 0) {
            return FALSE;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][third] + tile] & L_CRENEL) != 0) {
            return FALSE;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][fourth] + tile] & L_CRENEL) != 0) {
            return FALSE;
        }
        return TRUE;
    }

}
}
