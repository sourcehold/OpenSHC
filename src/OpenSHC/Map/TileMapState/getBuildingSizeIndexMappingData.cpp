#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingSizeIndexMapping.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F9880
    void TileMapState::getBuildingSizeIndexMappingData(int buildingSizeTileIndex, int buildingWidthOrHeight)
    {
        this->constructionTileCount = buildingWidthOrHeight * buildingWidthOrHeight;
        this->buildingX = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex].x;
        this->buildingY = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex].y;
        switch (this->mapOrientation) {
        case OpenSHC::Map::Enums::MO_NORTH:
            this->buildingOrientedPartIndex
                = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex]
                      .orientedPartIndex[0];
            return;
        case OpenSHC::Map::Enums::MO_EAST:
            this->buildingOrientedPartIndex
                = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex]
                      .orientedPartIndex[1];
            return;
        case OpenSHC::Map::Enums::MO_SOUTH:
            this->buildingOrientedPartIndex
                = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex]
                      .orientedPartIndex[2];
            return;
        case OpenSHC::Map::Enums::MO_WEST:
            this->buildingOrientedPartIndex
                = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex]
                      .orientedPartIndex[3];
        }
    }

}
}
