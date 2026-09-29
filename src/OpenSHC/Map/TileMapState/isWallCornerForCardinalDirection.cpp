#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL;

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F86D0
    BOOLEnum TileMapState::isWallCornerForCardinalDirection(int tile, int y, int direction)
    {
        int first = 0;
        int second = 0;
        int third = 0;
        int fourth = 0;
        if (direction == 0) {
            first = 0;
            second = 4;
            third = 2;
            fourth = 6;
        } else if (direction == 2) {
            first = 2;
            second = 6;
            third = 0;
            fourth = 4;
        } else if (direction == 4) {
            first = 0;
            second = 4;
            third = 2;
            fourth = 6;
        } else if (direction == 6) {
            first = 2;
            second = 6;
            third = 0;
            fourth = 4;
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
        return ~(this->LogicLayer[this->directionTranslationMatrix[y][fourth] + tile] >> 9) & TRUE;
    }

}
}
