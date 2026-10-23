#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingSizeIndexMapping.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F9880
    void TileMapState::getBuildingSizeIndexMappingData(int buildingSizeTileIndex, int buildingWidthOrHeight)
    {
        this->constructionTileCount = buildingWidthOrHeight * buildingWidthOrHeight;
        this->buildingX = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex][0];
        this->buildingY = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex][1];
        switch (this->mapOrientation) {
        case 0:
            this->buildingRotationRelatedValue
                = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex][2];
            return;
        case 2:
            this->buildingRotationRelatedValue
                = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex][3];
            return;
        case 4:
            this->buildingRotationRelatedValue
                = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex][4];
            return;
        case 6:
            this->buildingRotationRelatedValue
                = DAT_BuildingSizeIndexMapping::instance[buildingWidthOrHeight][buildingSizeTileIndex][5];
        }
        return;
    }

}
}
