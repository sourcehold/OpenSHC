#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F8640
    undefined4 TileMapState::isTileEnclosedByWalls(int tile, int y)
    {
        if ((this->LogicLayer[this->directionTranslationMatrix[y][0] + tile] & L_WALL_OR_GATEHOUSE) != 0
            && (this->LogicLayer[this->directionTranslationMatrix[y][0] + tile] & L_STOCKPILEUnk) == 0) {
            return 1;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][4] + tile] & L_WALL_OR_GATEHOUSE) != 0
            && (this->LogicLayer[this->directionTranslationMatrix[y][4] + tile] & L_STOCKPILEUnk) == 0) {
            return 1;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][2] + tile] & L_WALL_OR_GATEHOUSE) != 0
            && (this->LogicLayer[this->directionTranslationMatrix[y][2] + tile] & L_STOCKPILEUnk) == 0) {
            return 1;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][6] + tile] & L_WALL_OR_GATEHOUSE) != 0
            && (this->LogicLayer[this->directionTranslationMatrix[y][6] + tile] & L_STOCKPILEUnk) == 0) {
            return 1;
        }
        return 0;
    }

}
}
