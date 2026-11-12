#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Enums/CardinalDirection.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8530
    void TileMapState::countLogicPropertyInSurroundingTiles(int tile, int y, uint logic1)
    {
        this->DAT_CardinalTilesAroundTile = 0;
        if ((this->LogicLayer[this->directionTranslationMatrix[y][OpenSHC::Map::Enums::CD_NORTH] + tile] & logic1)
            != 0) {
            this->DAT_CardinalTilesAroundTile++;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][OpenSHC::Map::Enums::CD_EAST] + tile] & logic1)
            != 0) {
            this->DAT_CardinalTilesAroundTile++;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][OpenSHC::Map::Enums::CD_SOUTH] + tile] & logic1)
            != 0) {
            this->DAT_CardinalTilesAroundTile++;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][OpenSHC::Map::Enums::CD_WEST] + tile] & logic1)
            != 0) {
            this->DAT_CardinalTilesAroundTile++;
        }
    }

}
}
