#include "../TileMapState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8840
    BOOLEnum TileMapState::isWallConnectionHeightValid(int tile, int y, int direction)
    {
        int tileHeight = this->HeightLayer[tile];
        int firstDirection = 0;
        int secondDirection = 0;
        if (direction == 0) {
            secondDirection = 4;
        } else if (direction == 2) {
            firstDirection = 2;
            secondDirection = 6;
        } else if (direction == 4) {
            firstDirection = 0;
            secondDirection = direction;
        } else if (direction == 6) {
            firstDirection = 2;
            secondDirection = 6;
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
