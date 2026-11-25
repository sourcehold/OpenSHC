#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Enums/CardinalDirection.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8840
    BOOLEnum TileMapState::isWallConnectionHeightValid(int tile, int y, int direction)
    {
        int tileHeight = this->HeightLayer[tile];
        int firstDirection = OpenSHC::Map::Enums::CD_NORTH;
        int secondDirection = OpenSHC::Map::Enums::CD_NORTH;
        if (direction == OpenSHC::Map::Enums::CD_NORTH) {
            secondDirection = OpenSHC::Map::Enums::CD_SOUTH;
        } else if (direction == OpenSHC::Map::Enums::CD_EAST) {
            firstDirection = OpenSHC::Map::Enums::CD_EAST;
            secondDirection = OpenSHC::Map::Enums::CD_WEST;
        } else if (direction == OpenSHC::Map::Enums::CD_SOUTH) {
            firstDirection = OpenSHC::Map::Enums::CD_NORTH;
            secondDirection = OpenSHC::Map::Enums::CD_SOUTH;
        } else if (direction == OpenSHC::Map::Enums::CD_WEST) {
            firstDirection = OpenSHC::Map::Enums::CD_EAST;
            secondDirection = OpenSHC::Map::Enums::CD_WEST;
        }

        int first = this->directionTranslationMatrix[y][firstDirection] + tile;
        if ((this->LogicLayer[first] & L_WALL_OR_GATEHOUSE) == 0) {
            return FALSE;
        }
        if ((this->LogicLayer[first] & L_STOCKPILEUnk) != 0) {
            return FALSE;
        }
        int minHeight = tileHeight - 16;
        if (this->HeightLayer[first] < minHeight && this->DamageLayer[first] == 0) {
            return FALSE;
        }

        int second = this->directionTranslationMatrix[y][secondDirection] + tile;
        if ((this->LogicLayer[second] & L_WALL_OR_GATEHOUSE) == 0) {
            return FALSE;
        }
        if ((this->LogicLayer[second] & L_STOCKPILEUnk) != 0) {
            return FALSE;
        }
        if (this->HeightLayer[second] < minHeight && this->DamageLayer[second] == 0) {
            return FALSE;
        }
        return TRUE;
    }

}
}
