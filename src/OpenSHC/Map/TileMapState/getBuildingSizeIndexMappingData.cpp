#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingSizeIndexMapping.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F9880
    void TileMapState::getBuildingSizeIndexMappingData(int buildingSizeTileIndex, int buildingWidthOrHeight)
    {
        this->constructionTileCount = buildingWidthOrHeight * buildingWidthOrHeight;
        this->buildingX = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex][0];
        this->buildingY = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex][1];
        switch (this->mapOrientation) {
        case OpenSHC::Map::Enums::MO_NORTH:
            this->buildingRotationRelatedValue
                = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex][2];
            return;
        case OpenSHC::Map::Enums::MO_EAST:
            this->buildingRotationRelatedValue
                = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex][3];
            return;
        case OpenSHC::Map::Enums::MO_SOUTH:
            this->buildingRotationRelatedValue
                = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex][4];
            return;
        case OpenSHC::Map::Enums::MO_WEST:
            this->buildingRotationRelatedValue
                = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex][5];
        }
    }

}
}
