
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FB9E0
    void TileMapState::renderWallPlacementPreview(uint x, uint y, short kind)
    {
        int index = 0;
        int base = 0;
        int size = 0;
        if (x > 399) {
            return;
        }
        if (y > 399) {
            return;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
            return;
        }
        this->buildingPlacementFail = FALSE;
        /* every wall kind has its own footprint size and first graphic */
        if (kind == 0) {
            size = 1;
            base = 0x211;
        } else if (kind == 1) {
            size = 1;
            base = 0x215;
        } else if (kind == 2) {
            size = 1;
            base = 0x219;
        } else if (kind == 3) {
            size = 1;
            base = 0x21d;
        } else if (kind == 4) {
            size = 2;
            base = 0x1d1;
        } else if (kind == 5) {
            size = 2;
            base = 0x1e1;
        } else if (kind == 6) {
            size = 2;
            base = 0x1f1;
        } else if (kind == 7) {
            size = 2;
            base = 0x201;
        } else if (kind == 8) {
            size = 3;
            base = 0x141;
        } else if (kind == 9) {
            size = 3;
            base = 0x165;
        } else if (kind == 0xa) {
            size = 3;
            base = 0x189;
        } else if (kind == 0xb) {
            size = 3;
            base = 0x1ad;
        } else {
            if (kind == 0xc) {
                base = 0x41;
            } else if (kind == 0xd) {
                base = 0x81;
            } else if (kind == 0xe) {
                base = 0xc1;
            } else if (kind == 0xf) {
                base = 0x101;
            }
            if (base != 0) {
                size = 4;
            }
        }

        int rotation = this->rockOrientation + this->mapOrientation;
        if (this->field80_0x554894 == 5) {
            rotation = this->mapOrientation;
        }
        if (rotation >= 8) {
            rotation = rotation - 8;
        }
        /* the rotation part of the graphic index does not change over the footprint */
        int variationStep = rotation / 2 * size * size;

        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, size);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + this->buildingX + x;
            uint logic = this->LogicLayer[tile];
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
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, size);
            this->ConstructionGFXLayer[DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y]
                                           .addXgetTile
                + this->buildingX + x]
                = (short)this->buildingRotationRelatedValue + (short)GMTotalPicturesProcessed::instance[0x38]
                + (short)variationStep + (short)base - 1;
            index++;
        } while (index < this->constructionTileCount);
    }

}
}
