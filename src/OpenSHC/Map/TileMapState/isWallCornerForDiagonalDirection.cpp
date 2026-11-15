#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Enums/CardinalDirection.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8780
    uint TileMapState::isWallCornerForDiagonalDirection(int tile, int y, int direction)
    {
        int first = OpenSHC::Map::Enums::CD_NORTH;
        int second = OpenSHC::Map::Enums::CD_NORTH;
        int third = OpenSHC::Map::Enums::CD_NORTH;
        int fourth = OpenSHC::Map::Enums::CD_NORTH;
        if (direction == OpenSHC::Map::Enums::CD_NORTHEAST) {
            first = OpenSHC::Map::Enums::CD_SOUTH;
            second = OpenSHC::Map::Enums::CD_WEST;
            third = OpenSHC::Map::Enums::CD_NORTH;
            fourth = OpenSHC::Map::Enums::CD_EAST;
        } else if (direction == OpenSHC::Map::Enums::CD_SOUTHEAST) {
            first = OpenSHC::Map::Enums::CD_NORTH;
            second = OpenSHC::Map::Enums::CD_WEST;
            third = OpenSHC::Map::Enums::CD_SOUTH;
            fourth = OpenSHC::Map::Enums::CD_EAST;
        } else if (direction == OpenSHC::Map::Enums::CD_SOUTHWEST) {
            first = OpenSHC::Map::Enums::CD_NORTH;
            second = OpenSHC::Map::Enums::CD_EAST;
            third = OpenSHC::Map::Enums::CD_SOUTH;
            fourth = OpenSHC::Map::Enums::CD_WEST;
        } else if (direction == OpenSHC::Map::Enums::CD_NORTHWEST) {
            first = OpenSHC::Map::Enums::CD_SOUTH;
            second = OpenSHC::Map::Enums::CD_EAST;
            third = OpenSHC::Map::Enums::CD_NORTH;
            fourth = OpenSHC::Map::Enums::CD_WEST;
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
