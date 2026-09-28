#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F8780
    uint TileMapState::isWallCornerForDiagonalDirection(int tile, int y, int direction)
    {
        int first = 0;
        int second = 0;
        int third = 0;
        int fourth = 0;
        if (direction == 1) {
            first = 4;
            second = 6;
            third = 0;
            fourth = 2;
        } else if (direction == 3) {
            first = 0;
            second = 6;
            third = 4;
            fourth = 2;
        } else if (direction == 5) {
            first = 0;
            second = 2;
            third = 4;
            fourth = 6;
        } else if (direction == 7) {
            first = 4;
            second = 2;
            third = 0;
            fourth = 6;
        }

        if ((this->LogicLayer[this->directionTranslationMatrix[y][first] + tile] & L_CRENEL) == 0) {
            return 0;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][second] + tile] & L_CRENEL) == 0) {
            return 0;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][third] + tile] & L_CRENEL) != 0) {
            return 0;
        }
        return ~((uint)this->LogicLayer[this->directionTranslationMatrix[y][fourth] + tile] >> 9) & 1;
    }

}
}
