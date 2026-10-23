#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F89C0
    uint TileMapState::getWallFlagForOrientedDirection(int tile, int y, int twoOrFour)
    {
        int direction = 0;
        if (twoOrFour == 2) {
            if (this->mapOrientation == 0) {
                direction = 2;
            } else if (this->mapOrientation == 2) {
                direction = 4;
            } else if (this->mapOrientation == 4) {
                direction = 6;
            }
        } else {
            if (twoOrFour != 4) {
                return 0;
            }
            if (this->mapOrientation == 0) {
                direction = 4;
            } else if (this->mapOrientation == 2) {
                direction = 6;
            } else if (this->mapOrientation == 6) {
                direction = 2;
            }
        }
        return this->LogicLayer[this->directionTranslationMatrix[y][direction] + tile] >> 8 & 1;
    }

}
}
