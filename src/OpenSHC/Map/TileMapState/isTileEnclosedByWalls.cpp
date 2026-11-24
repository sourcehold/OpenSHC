#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Enums/CardinalDirection.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8640
    BOOLEnum TileMapState::isTileEnclosedByWalls(int tile, int y)
    {
        int offset = this->directionTranslationMatrix[y][OpenSHC::Map::Enums::CD_NORTH] + tile;
        if ((this->LogicLayer[offset] & L_WALL_OR_GATEHOUSE) != 0 && (this->LogicLayer[offset] & L_STOCKPILEUnk) == 0) {
            return TRUE;
        }
        offset = this->directionTranslationMatrix[y][OpenSHC::Map::Enums::CD_SOUTH] + tile;
        if ((this->LogicLayer[offset] & L_WALL_OR_GATEHOUSE) != 0 && (this->LogicLayer[offset] & L_STOCKPILEUnk) == 0) {
            return TRUE;
        }
        offset = this->directionTranslationMatrix[y][OpenSHC::Map::Enums::CD_EAST] + tile;
        if ((this->LogicLayer[offset] & L_WALL_OR_GATEHOUSE) != 0 && (this->LogicLayer[offset] & L_STOCKPILEUnk) == 0) {
            return TRUE;
        }
        offset = this->directionTranslationMatrix[y][OpenSHC::Map::Enums::CD_WEST] + tile;
        if ((this->LogicLayer[offset] & L_WALL_OR_GATEHOUSE) != 0 && (this->LogicLayer[offset] & L_STOCKPILEUnk) == 0) {
            return TRUE;
        }
        return FALSE;
    }

}
}
