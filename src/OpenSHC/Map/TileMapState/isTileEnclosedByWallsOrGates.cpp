#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F85B0
    BOOLEnum TileMapState::isTileEnclosedByWallsOrGates(int tile, int y)
    {
        if ((this->LogicLayer[this->directionTranslationMatrix[y][0] + tile] & L_WALL_OR_GATEHOUSE) != 0
            && (this->LogicLayer[this->directionTranslationMatrix[y][0] + tile] & (L_STOCKPILEUnk | L_CRENEL)) == 0) {
            return TRUE;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][4] + tile] & L_WALL_OR_GATEHOUSE) != 0
            && (this->LogicLayer[this->directionTranslationMatrix[y][4] + tile] & (L_STOCKPILEUnk | L_CRENEL)) == 0) {
            return TRUE;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][2] + tile] & L_WALL_OR_GATEHOUSE) != 0
            && (this->LogicLayer[this->directionTranslationMatrix[y][2] + tile] & (L_STOCKPILEUnk | L_CRENEL)) == 0) {
            return TRUE;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][6] + tile] & L_WALL_OR_GATEHOUSE) != 0
            && (this->LogicLayer[this->directionTranslationMatrix[y][6] + tile] & (L_STOCKPILEUnk | L_CRENEL)) == 0) {
            return TRUE;
        }
        return FALSE;
    }

}
}
