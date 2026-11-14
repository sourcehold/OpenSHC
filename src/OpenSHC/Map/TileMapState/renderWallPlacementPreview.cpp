#include "../TileMapState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FB9E0
    void TileMapState::renderWallPlacementPreview(uint x, uint y, short kind)
    {
        int base = 0;
        int size = 0;
        int index = 0;
        if (x > 399 || y > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
            return;
        }
        this->buildingPlacementFail = FALSE;
        // every wall kind has its own footprint size and first graphic
        if (kind == 0) {
            size = 1;
            base = 529;
        } else if (kind == 1) {
            size = 1;
            base = 533;
        } else if (kind == 2) {
            size = 1;
            base = 537;
        } else if (kind == 3) {
            size = 1;
            base = 541;
        } else if (kind == 4) {
            size = 2;
            base = 465;
        } else if (kind == 5) {
            size = 2;
            base = 481;
        } else if (kind == 6) {
            size = 2;
            base = 497;
        } else if (kind == 7) {
            size = 2;
            base = 513;
        } else if (kind == 8) {
            size = 3;
            base = 321;
        } else if (kind == 9) {
            size = 3;
            base = 357;
        } else if (kind == 10) {
            size = 3;
            base = 393;
        } else if (kind == 11) {
            size = 3;
            base = 429;
        } else if (kind == 12) {
            base = 65;
            size = 4;
        } else if (kind == 13) {
            base = 129;
            size = 4;
        } else if (kind == 14) {
            base = 193;
            size = 4;
        } else if (kind == 15) {
            base = 257;
            size = 4;
        }

        int rotation = this->rockOrientation + this->mapOrientation;
        if (this->editorRockType == 5) {
            rotation = this->mapOrientation;
        }
        if (rotation >= 8) {
            rotation -= 8;
        }
        // the rotation part of the graphic index does not change over the footprint
        int variationStep = rotation / 2 * size * size;

        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, size);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            uint const logic = this->LogicLayer[tile];
            if ((logic & (L_BORDER | L_BORDER_EDGE)) != 0) {
                return;
            }
            if ((logic & L_BUILDING) != 0) {
                return;
            }
            if (this->OrganismLayer[tile] != 0) {
                return;
            }
            index++;
        } while (index < this->constructionTileCount);

        index = 0;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, size);
            this->ConstructionGFXLayer[DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y]
                                           .addXgetTile
                + this->buildingX + x]
                = this->buildingRotationRelatedValue + GMFirstPictureIndex::instance[56] + variationStep + base - 1;
            index++;
            if (index >= this->constructionTileCount) {
                break;
            }
        }
    }

}
}
