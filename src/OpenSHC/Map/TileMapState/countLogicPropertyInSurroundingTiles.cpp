#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F8530
    void TileMapState::countLogicPropertyInSurroundingTiles(int tile, int y, uint logic1)
    {
        this->DAT_CardinalTilesAroundTile = 0;
        if ((this->LogicLayer[this->directionTranslationMatrix[y][0] + tile] & logic1) != 0) {
            this->DAT_CardinalTilesAroundTile++;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][2] + tile] & logic1) != 0) {
            this->DAT_CardinalTilesAroundTile++;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][4] + tile] & logic1) != 0) {
            this->DAT_CardinalTilesAroundTile++;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][6] + tile] & logic1) != 0) {
            this->DAT_CardinalTilesAroundTile++;
        }
    }

}
}
