#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F8AC0
    BOOLEnum TileMapState::hasHigherPlainNeighborWithWallOrGatehouse(int tile, int y, int direction)
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
        if (this->HeightLayer[tile] >= this->HeightLayer[neighbour]) {
            return FALSE;
        }
        if ((this->LogicLayer[neighbour] & L_CRENEL) != 0) {
            return FALSE;
        }
        if ((this->LogicLayer[neighbour] & L_STOCKPILEUnk) != 0) {
            return FALSE;
        }
        return this->LogicLayer[neighbour] >> 8 & TRUE;
    }

}
}
